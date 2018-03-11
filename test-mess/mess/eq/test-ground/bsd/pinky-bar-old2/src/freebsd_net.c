/*
   Copyright 08/16/2016
   Aaron Caffrey https://github.com/wifiextender

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.
*/

#include "config.h"

#if WITH_NET == 1

#include <netdb.h>
/* #include <sys/types.h> */
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <ifaddrs.h>

#include <net/if.h>
#include <net/if_dl.h>
#include <net/route.h>
#include <netinet/in.h>

#endif /* WITH_NET */

#include "include/headers.h"
#include "prototypes/net.h"
#include "include/freebzd.h"

/* Thanks to http://www.matisse.net/bitcalc/?source=print */
void
get_net(char *str1, char *str2, unsigned char num) {
#if WITH_NET == 1

  struct ifaddrs *ifaddr = NULL, *ifa = NULL;
  struct if_data *stats = NULL;
  struct sockaddr_dl *mac = NULL; 
  static uintmax_t prev_recv = 0, prev_sent = 0;
  uintmax_t cur_recv = 0, cur_sent = 0;
  unsigned char *umac = NULL;
  void *temp_void = NULL;
  char temp[VLA];

  if (-1 == getifaddrs(&ifaddr)) {
    FUNC_FAILED("getifaddrs()");
  }
  FILL_STR_ARR(1, str1, "Null");

  for (ifa = ifaddr; NULL != ifa; ifa = ifa->ifa_next) {
    if (NULL == ifa->ifa_addr) {
      continue;
    }
    if (3 == num || 5 == num || 6 == num) { /* ip | netmask | broadcast */
      if (ifa->ifa_addr->sa_family == AF_INET) {
        if (0 == (strcmp(str2, ifa->ifa_name))) {
          switch(num) {
            case 3:
              temp_void = ifa->ifa_addr;
              break;
            case 5:
              temp_void = ifa->ifa_netmask;
              break;
            case 6:
              temp_void = ifa->ifa_broadaddr;
              break;
          }
          inet_ntop(AF_INET, &(((struct sockaddr_in *)temp_void)->sin_addr),
              temp, INET_ADDRSTRLEN);
          FILL_STR_ARR(1, str1, temp);
          break;
        }
      }
    } else if (ifa->ifa_addr->sa_family == AF_LINK &&
        NULL != ifa->ifa_data) {
        if (0 == (strcmp(str2, ifa->ifa_name))) {
          stats = (struct if_data *)ifa->ifa_data;

          if (2 == num) { /* upload and download speeds */
            cur_recv = (uintmax_t)stats->ifi_ibytes - prev_recv;
            cur_sent = (uintmax_t)stats->ifi_obytes - prev_sent;

            FILL_ARR(str1, "Down " FMT_UINT " KB, Up " FMT_UINT " KB",
              (cur_recv / KB), (cur_sent / KB));

            prev_recv = cur_recv;
            prev_sent = cur_sent;
          } else if (1 == num) { /* consumed internet so far */
    
            FILL_ARR(str1, "Down " FMT_UINT " MB, Up " FMT_UINT " MB",
              ((uintmax_t)stats->ifi_ibytes / MB),
              ((uintmax_t)stats->ifi_obytes / MB));
          } else if (4 == num) { /* mac address */
            temp_void = ifa->ifa_addr;
            mac = (struct sockaddr_dl *)temp_void;
            /*
              6 == ether
              20 == infiniband
            */
            if (6 != mac->sdl_alen) {
              break;
            }
			umac = (unsigned char *)LLADDR(mac);
            FILL_ARR(str1, "%02x:%02x:%02x:%02x:%02x:%02x",
                *umac, *(umac + 1), *(umac + 2),
                *(umac + 3), *(umac + 4), *(umac + 5));
          }
          break;
        }
    }
  }
  if (NULL != ifaddr) {
    freeifaddrs(ifaddr);
  }

#else
  RECOMPILE_WITH("net");
#endif /* WITH_NET */
}


void
get_ip_lookup(char *str1, char *str2) {
#if WITH_NET == 1

  struct addrinfo *rp = NULL, *result = NULL;
  struct addrinfo hints;
  void *temp_void = NULL;
  char temp[VLA];
  int err = 0;

  memset(&hints, 0, sizeof(hints));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0; /* udp | tcp */

  err = getaddrinfo(str2, NULL, &hints, &result);
  if (0 != err) {
    FUNC_FAILED("getaddrinfo()");
  }

  for (rp = result; NULL != rp; rp = rp->ai_next) {
    if (NULL == rp->ai_addr) {
      continue;
    }
    /* check ipv4 again, despite the "hints" */
    if (rp->ai_family == AF_INET) {
      temp_void = rp->ai_addr;

      inet_ntop(AF_INET, &(((struct sockaddr_in *)temp_void)->sin_addr),
        temp, INET_ADDRSTRLEN);
      FILL_STR_ARR(1, str1, temp);

      break;
    }
  }
  if ('\0' == str1[0]) {
    FILL_STR_ARR(1, str1, "Null");
  }
  if (NULL != result) {
    freeaddrinfo(result);
  }

#else
  RECOMPILE_WITH("net");
#endif /* WITH_NET */
}


/* It's so nice that the kernel
   does all the heavy lifting for us.
   In Linux you get only the hex numbers.

sysctl -a | grep 'dev.re.0'

dev.re.0.wake: 0
dev.re.0.int_rx_mod: 65
dev.re.0.stats: -1
dev.re.0.%parent: pci2
dev.re.0.%pnpinfo: vendor=0x10ec device=0x8168 subvendor=0x1043 subdevice=0x8432 class=0x020000
dev.re.0.%location: pci0:2:0:0 handle=\_SB_.PCI0.PCE4.RLAN
dev.re.0.%driver: re
dev.re.0.%desc: RealTek 8168/8111 B/C/CP/D/DP/E/F/G PCIe Gigabit Ethernet */
