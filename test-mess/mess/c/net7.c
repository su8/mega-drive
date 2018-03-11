
/*        #define _GNU_SOURCE     /1* To get defns of NI_MAXSERV and NI_MAXHOST *1/ */
/*        #include <arpa/inet.h> */
/*        #include <sys/socket.h> */
/*        #include <netdb.h> */
/*        #include <ifaddrs.h> */
/*        #include <stdio.h> */
/*        #include <stdlib.h> */
/*        #include <unistd.h> */
/*        #include <linux/if_link.h> */

/*        int main(void) */
/*        { */
/*            struct ifaddrs *ifaddr, *ifa; */
/*            int family, s, n; */
/*            char host[NI_MAXHOST]; */

/*            if (getifaddrs(&ifaddr) == -1) { */
/*                perror("getifaddrs"); */
/*                exit(EXIT_FAILURE); */
/*            } */

/*            /1* Walk through linked list, maintaining head pointer so we */
/*               can free list later *1/ */

/*            for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) { */
/*                if (ifa->ifa_addr == NULL) */
/*                    continue; */

/*                family = ifa->ifa_addr->sa_family; */

/*                /1* Display interface name and family (including symbolic */
/*                   form of the latter for the common families) *1/ */

/*                printf("%-8s %s (%d)\n", */
/*                       ifa->ifa_name, */
/*                       (family == AF_PACKET) ? "AF_PACKET" : */
/*                       (family == AF_INET) ? "AF_INET" : */
/*                       (family == AF_INET6) ? "AF_INET6" : "???", */
/*                       family); */

/*                /1* For an AF_INET* interface address, display the address *1/ */

/*                if (family == AF_INET || family == AF_INET6) { */
/*                    s = getnameinfo(ifa->ifa_addr, */
/*                            (family == AF_INET) ? sizeof(struct sockaddr_in) : */
/*                                                  sizeof(struct sockaddr_in6), */
/*                            host, NI_MAXHOST, */
/*                            NULL, 0, NI_NUMERICHOST); */
/*                    if (s != 0) { */
/*                        printf("getnameinfo() failed: %s\n", gai_strerror(s)); */
/*                        exit(EXIT_FAILURE); */
/*                    } */

/*                    printf("\t\taddress: <%s>\n", host); */

/*                } else if (family == AF_PACKET && ifa->ifa_data != NULL) { */
/*                    struct rtnl_link_stats *stats = ifa->ifa_data; */

/*                    printf("\t\ttx_packets = %10u; rx_packets = %10u\n" */
/*                           "\t\ttx_bytes   = %10u; rx_bytes   = %10u\n", */
/*                           stats->tx_packets, stats->rx_packets, */
/*                           stats->tx_bytes, stats->rx_bytes); */
/*                } */
/*            } */

/*            freeifaddrs(ifaddr); */
/*            exit(EXIT_SUCCESS); */
/*        } */
#include <stdio.h>
#include <stdlib.h>
/* #include <unistd.h> */
#include <string.h>
/* #include <netdb.h> */
/* #include <ifaddrs.h> */
/* #include <arpa/inet.h> */
/* #include <sys/types.h> */
/* #include <sys/socket.h> */
/* /1* #include <sys/socket.h> *1/ */
/* #include <netdb.h> */
/* #include <net/if.h> */
/* #include <linux/if_link.h> */
/* #include <net/if_dl.h> */
/* #include <netinet/in.h> */
/* #include <arpa/inet.h> */
/* #include <net/if_types.h> */
#include <netdb.h>
/* #include <sys/types.h> */
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <linux/if_link.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>
#include <linux/if.h>

int main(void)
{   
    /* const char* ifname = "eth0"; */  
    /* struct ifaddrs *ifaddr, *ifa; */

    /* /1* if(argc > 1){ *1/ */
    /* /1*     ifname = argv[1]; *1/ */  
    /* /1* }else{ *1/ */
    /* /1*     printf("Usage:\n\t%s <eth?>\n", argv[0]); *1/ */
    /* /1*     exit(0); *1/ */
    /* /1* } *1/ */

    /* if (getifaddrs(&ifaddr) == -1) { */
    /*     /1* perror("getifaddrs"); *1/ */
    /*     exit(EXIT_FAILURE); */
    /* } */

    /* for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) { */
    /*     if((ifa->ifa_addr != NULL) && */
    /*        (strcmp(ifa->ifa_name, ifname) == 0) && */  
    /*        (ifa->ifa_addr->sa_family == AF_INET)) { */
    /*             /1* struct sockaddr_dl* sdl = (struct sockaddr_dl *)ifa->ifa_addr; *1/ */
    /*             /1* memcpy(mac_addr, LLADDR(sdl), sdl->sdl_alen); *1/ */
/* /1* ifu_broadaddr *1/ */
    /*         /1* printf("\tInterface: <%s>\n", ifa->ifa_broadaddr); *1/ */ 
    /*         printf("\tAddress: <%s>\n", inet_ntoa(((struct sockaddr_in *)ifa->ifa_addr)->sin_addr)); */
    /*         break; */
    /*     } */
    /* } */

    /* freeifaddrs(ifaddr); */
    /* exit(EXIT_SUCCESS); */
  
     /* assert(buflen >= 16); */

    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    /* assert(sock != -1); */
    size_t buflen = 50;
    char buffer[50] = "eth0";

    const char* kGoogleDnsIp = "8.8.8.8";
    uint16_t kDnsPort = 53;
    struct sockaddr_in serv;
    memset(&serv, 0, sizeof(serv));
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(kGoogleDnsIp);
    serv.sin_port = htons(kDnsPort);

    int err = connect(sock, (struct sockaddr*) &serv, sizeof(serv));
    /* assert(err != -1); */

    struct sockaddr_in name;
    socklen_t namelen = sizeof(name);
    err = getsockname(sock, (struct sockaddr*) &name, &namelen);
    /* assert(err != -1); */

    const char* p = inet_ntop(AF_INET, &name.sin_addr, buffer, buflen);
    /* assert(p); */
    printf("%s\n", p);

    close(sock); 
  
  return 0;
}
