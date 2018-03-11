#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>

#if defined(__linux__)
# include <ifaddrs.h>
# include <linux/if_link.h>
# include <netpacket/packet.h>
# include <net/if.h>
# include <linux/sockios.h>
# include <linux/ethtool.h>

#elif defined(__FreeBSD__) || defined(__OpenBSD__)
# include <arpa/nameser.h>
# include <ifaddrs.h>
# include <net/if.h>
# include <net/if_dl.h>
# include <net/route.h>
# include <netinet/in.h>

#else
# error: Unsupported OS, choose between Linux, FreeBSD or OpenBSD
#endif /* __linux__ */

#define VLA 100

#if defined(__linux__)
# define NETFAM AF_PACKET
# define RECVBYTS rx_bytes
# define SENTBYTS tx_bytes
#else
# define NETFAM AF_LINK
# define RECVBYTS ifi_ibytes
# define SENTBYTS ifi_obytes
#endif /* __linux__ */

static char *addr_to_str(void *to_convert);

int main(void) {

#if defined(__linux__)
  struct rtnl_link_stats *stats = NULL;
  struct sockaddr_ll *mac       = NULL;
#else
  struct if_data *stats   = NULL;
  struct sockaddr_dl *mac = NULL;
  unsigned char *umac = NULL;
#endif /* __linux__ */

  struct ifaddrs *ifaddr = NULL, *ifa = NULL;

  if (-1 == (getifaddrs(&ifaddr))) {
    fprintf(stderr, "%s\n", "getifaddrs() failed");
    return EXIT_FAILURE;
  }

  for (ifa = ifaddr; NULL != ifa; ifa = ifa->ifa_next) {
    if ((IFF_UP | IFF_BROADCAST) != (ifa->ifa_flags & (
      IFF_UP | IFF_BROADCAST | IFF_POINTOPOINT | IFF_LOOPBACK | IFF_NOARP))) {
      continue;
    }
    if (NULL == ifa->ifa_addr) {
      continue;
    }
    if (AF_INET == ifa->ifa_addr->sa_family) {
      printf("NIC: %s\n", ifa->ifa_name);
      printf("IP: %s\n", addr_to_str((void *)ifa->ifa_addr));
      printf("NetMask: %s\n", addr_to_str((void *)ifa->ifa_netmask));
      printf("Broadcast address: %s\n", addr_to_str((void *)ifa->ifa_broadaddr));
    }

    if (NETFAM == ifa->ifa_addr->sa_family && NULL != ifa->ifa_data) {
#if defined(__linux__)
      stats = ifa->ifa_data;
#else
      stats = (struct if_data *)ifa->ifa_data;
#endif /* __linux__ */
      printf("RX = %llu, TX = %llu\n",(unsigned long long)stats->RECVBYTS,
        (unsigned long long)stats->SENTBYTS);

#if defined(__linux__)
      mac = (struct sockaddr_ll *)(void *)ifa->ifa_addr;
      if (6 != mac->sll_halen) {
        break;
      }
      printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
        mac->sll_addr[0], mac->sll_addr[1],
        mac->sll_addr[2], mac->sll_addr[3],
        mac->sll_addr[4], mac->sll_addr[5]);
#else
      mac = (struct sockaddr_dl)(void *)ifa->ifa_addr;
      if (6 != mac->sdl_alen) {
        break;
      }
      umac = (unsigned char *)LLADDR(mac);
      printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n",
        *umac, *(umac + 1), *(umac + 2),
        *(umac + 3), *(umac + 4), *(umac + 5));
#endif /* __linux__ */
    }
  }

  if (NULL != ifaddr) {
    freeifaddrs(ifaddr);
  }

  return EXIT_SUCCESS;
}

static char *
addr_to_str(void *to_convert) {
  char temp[VLA];
  char *to_ret = temp;

  inet_ntop(AF_INET, &(((struct sockaddr_in *)to_convert)->sin_addr), temp, INET_ADDRSTRLEN);

  return to_ret;
}
