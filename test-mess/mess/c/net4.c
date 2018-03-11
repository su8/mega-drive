/* #include <unistd.h> */
/* #include <sys/socket.h> */
/* #include <sys/ioctl.h> */
/* #include <netinet/ip.h> */
/* #include <net/if.h> */
/* #include <linux/ethtool.h> */
/* #include <linux/sockios.h> */
/* #include <string.h> */
/* #include <errno.h> */
/* #include <stdio.h> */

/* int ethernet_interface(const char *const name, */
/*                        int *const index, int *const speed, int *const duplex) */
/* { */
/*     struct ifreq        ifr; */
/*     struct ethtool_cmd  cmd; */
/*     int                 fd, result; */

/*     if (!name || !*name) { */
/*         fprintf(stderr, "Error: NULL interface name.\n"); */
/*         fflush(stderr); */
/*         return errno = EINVAL; */
/*     } */

/*     if (index)  *index = -1; */
/*     if (speed)  *speed = -1; */
/*     if (duplex) *duplex = -1; */

/*     fd = socket(AF_INET, SOCK_STREAM, 0); */
/*     if (fd == -1) { */
/*         const int err = errno; */
/*         fprintf(stderr, "%s: Cannot create AF_INET socket: %s.\n", name, strerror(err)); */
/*         fflush(stderr); */
/*         return errno = err; */
/*     } */

/*     strncpy(ifr.ifr_name, name, sizeof ifr.ifr_name); */
/*     ifr.ifr_data = (void *)&cmd; */
/*     cmd.cmd = ETHTOOL_GSET; */
/*     if (ioctl(fd, SIOCETHTOOL, &ifr) < 0) { */
/*         const int err = errno; */
/*         do { */
/*             result = close(fd); */
/*         } while (result == -1 && errno == EINTR); */
/*         fprintf(stderr, "%s: SIOCETHTOOL ioctl: %s.\n", name, strerror(err)); */
/*         return errno = err; */
/*     } */

/*     if (speed) */
/*         *speed = ethtool_cmd_speed(&cmd); */

/*     if (duplex) */
/*         switch (cmd.duplex) { */
/*         case DUPLEX_HALF: *duplex = 0; break; */
/*         case DUPLEX_FULL: *duplex = 1; break; */
/*         default: */
/*             fprintf(stderr, "%s: Unknown mode (0x%x).\n", name, cmd.duplex); */
/*             fflush(stderr); */
/*             *duplex = -1; */
/*         } */

/*     if (index && ioctl(fd, SIOCGIFINDEX, &ifr) >= 0) */
/*         *index = ifr.ifr_ifindex; */

/*     do { */
/*         result = close(fd); */
/*     } while (result == -1 && errno == EINTR); */
/*     if (result == -1) { */
/*         const int err = errno; */
/*         fprintf(stderr, "%s: Error closing socket: %s.\n", name, strerror(err)); */
/*         return errno = err; */
/*     } */

/*     return 0; */
/* } */

/* int main(int argc, char *argv[]) */
/* { */
/*     int  arg, speed, index, duplex; */

/*     if (argc < 2 || !strcmp(argv[1], "-h") || !strcmp(argv[1], "--help")) { */
/*         fprintf(stderr, "\n"); */
/*         fprintf(stderr, "Usage: %s [ -h | --help ]\n", argv[0]); */
/*         fprintf(stderr, "       %s INTERFACE ...\n", argv[0]); */
/*         fprintf(stderr, "\n"); */
/*         return 0; */
/*     } */

/*     for (arg = 1; arg < argc; arg++) { */
/*         if (ethernet_interface(argv[arg], &index, &speed, &duplex)) */
/*             return 1; */

/*         if (index == -1) */
/*             printf("%s: (no interface index)", argv[arg]); */
/*         else */
/*             printf("%s: interface %d", argv[arg], index); */

/*         if (speed == -1) */
/*             printf(", unknown bandwidth"); */
/*         else */
/*             printf(", %d Mbps bandwidth", speed); */

/*         if (duplex == 0) */
/*             printf(", half duplex.\n"); */
/*         else if (duplex == 1) */
/*             printf(", full duplex.\n"); */
/*         else */
/*             printf(", unknown mode.\n"); */
/*     } */

/*     return 0; */
/* } */
#include <ifaddrs.h>
#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>
#include <string.h>

int main(void)
{
    struct ifaddrs *ifaddr, *ifa;
    int family, n;
    int sock;
    struct ifreq ifr;
    struct ethtool_cmd edata;
    struct ethtool_drvinfo drvinfo;
    int rc;

    if (getifaddrs(&ifaddr) == -1) {
        perror("getifaddrs");
        exit(EXIT_FAILURE);
    }

    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        perror("socket");
        exit(1);
    }

    for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) {
        if (ifa->ifa_addr == NULL)
            continue;

        family = ifa->ifa_addr->sa_family;

        /* For an AF_PACKET (and physical eth) interface, display the speed */

        if (family == AF_PACKET && ifa->ifa_data != NULL &&
            ((ifa->ifa_flags & (IFF_BROADCAST | IFF_MULTICAST)) ==
                              (IFF_BROADCAST | IFF_MULTICAST))) {

            strncpy(ifr.ifr_name, ifa->ifa_name, sizeof(ifr.ifr_name));
            ifr.ifr_data = (caddr_t)&drvinfo;
            /* edata.cmd = ETHTOOL_GSET; */
            drvinfo.cmd = ETHTOOL_GDRVINFO;
            rc = ioctl(sock, SIOCETHTOOL, &ifr);
            if (rc < 0) {
                perror("ioctl");
                exit(1);
            }
            printf("%s | %s | %s | %s\n", drvinfo.driver, drvinfo.version, drvinfo.fw_version);

            /* printf("%-8s (ifa_flags = %x)\n", */
            /*        ifa->ifa_name, ifa->ifa_flags); */

            /* switch (ethtool_cmd_speed(&edata)) { */
            /*     case SPEED_10: printf("10Mbps\n"); break; */
            /*     case SPEED_100: printf("100Mbps\n"); break; */
            /*     case SPEED_1000: printf("1Gbps\n"); break; */
            /*     case SPEED_2500: printf("2.5Gbps\n"); break; */
            /*     case SPEED_10000: printf("10Gbps\n"); break; */
            /*     default: printf("Speed returned is 0x%x\n", edata.speed); */
            /* } */
        }
    }

    freeifaddrs(ifaddr);
    exit(EXIT_SUCCESS);
}

        /* if (edata.supported & SUPPORTED_10000baseT_Full) */
        /*     printf("-> 10G supported\n"); */
        /* else */
        /*     printf("-> 10G NOT supported\n"); */
        /* if (edata.advertising & ADVERTISED_10000baseT_Full) */
        /*     printf("-> 10G advertised\n"); */
        /* else */
        /*     printf("-> 10G NOT advertised\n"); */
