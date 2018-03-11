
/* #include <stdio.h> */
/* #include <stdlib.h> */
/* #include <string.h> */
/* #include <net/if.h> */
/* #include <sys/ioctl.h> */
/* #include <sys/socket.h> */
/* #include <sys/types.h> */
/* #include <arpa/inet.h> */
/* #include <netdb.h> */
/* /1* #include <sys/types.h> *1/ */
/* #include <sys/socket.h> */
/* #include <ifaddrs.h> */
/* #include <linux/if_link.h> */
/* #include <netpacket/packet.h> */
/* #include <net/if.h> */
/* #include <sys/ioctl.h> */
/* #include <linux/sockios.h> */
/* #include <linux/ethtool.h> */
/* #include <linux/if.h> */
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <net/if_arp.h>
#include <linux/sockios.h>
#include <net/if.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

int main(void)
{
  /* int          address_index; */
  int          ioctl_result;
  int          local_socket;
  char temp[300];
  void *temp_void = NULL;

  struct ifreq ifr;
memset(&ifr, 0, sizeof(ifr));
  local_socket=socket(AF_INET,
                      SOCK_DGRAM,
                      0
                     );

  if(local_socket==-1)
  {
    perror("socket()");

    return -1;
  }

  strcpy(ifr.ifr_name,
         "eth0"
        );

  ifr.ifr_addr.sa_family = AF_INET;
  ioctl_result=ioctl(local_socket,
                     SIOCGIFADDR,
                     &ifr
                    );

  if(ioctl_result==-1)
  {
    perror("ioctl(SIOCGIFHWADDR)");
    return -1;
  }
temp_void = &ifr.ifr_dstaddr;
  /* ad = inet_ntoa(((struct sockaddr_in *))->sin_addr); */
inet_ntop(AF_INET, &(((struct sockaddr_in *)temp_void)->sin_addr),
              temp, INET_ADDRSTRLEN);

  printf("%s\n", temp);
  /* for(address_index=0; */
  /*     /1* no     address_index<sizeof(ifr.ifr_hwaddr.sa_data); *1/ */
  /*     /1* yes *1/ address_index<6; */
  /*     address_index++ */
  /*    ) */
  /* { */
  /*   if(address_index>0) */
  /*   { */
  /*     printf(":"); */
  /*   } */

  /*   /1* inet_ntoa(ifr.ifr.ifr_dstaddr) *1/ */
  /*   /1* printf("%02x", (ifr.ifr_hwaddr.sa_data[address_index])); *1/ */
  /* } */

  /* printf("\n"); */

  return 0;
}
