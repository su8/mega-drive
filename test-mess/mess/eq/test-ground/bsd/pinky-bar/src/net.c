/*
   Copyright 08/06/2016
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
#include <ifaddrs.h>

#if !defined(__FreeBSD__)
#include <linux/if_link.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>
#include <linux/if.h>
#else
#include <net/if.h>
#include <net/if_dl.h>
#include <net/if_mib.h>
#include <net/if_media.h>
#include <net/if_var.h>

#include <sys/param.h>
#include <netinet/in.h>
#include <arpa/nameser.h>
#endif /* FreeBSD */

#endif /* WITH_NET */

#include "include/headers.h"
#include "prototypes/net.h"

/* Thanks to http://www.matisse.net/bitcalc/?source=print */
void
get_net(char *str1, char *str2, unsigned char num) {
#if WITH_NET == 1

  struct ifaddrs *ifaddr = NULL, *ifa = NULL;
  struct if_data *stats = NULL;
  static uintmax_t prev_recv = 0, prev_sent = 0;
  uintmax_t cur_recv, cur_sent;
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
          } else if (1 == num){ /* consumed internet so far */
    
            FILL_ARR(str1, "Down " FMT_UINT " MB, Up " FMT_UINT " MB",
              ((uintmax_t)stats->ifi_ibytes / MB),
              ((uintmax_t)stats->ifi_obytes / MB));
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
