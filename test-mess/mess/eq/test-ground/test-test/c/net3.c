/* http://man7.org/linux/man-pages/man3/getifaddrs.3.html */

 /* #include <arpa/inet.h> */
 /* #include <netdb.h> */
 #include <sys/socket.h>
 #include <ifaddrs.h>
 #include <stdio.h>
 #include <stdlib.h>
#include <string.h>
 #include <unistd.h>
 #include <linux/if_link.h>

 int main(void)
 {
     struct ifaddrs *ifaddr, *ifa;
     struct rtnl_link_stats *stats;
     int family;

     if (getifaddrs(&ifaddr) == -1) {
         perror("getifaddrs");
         exit(EXIT_FAILURE);
     }

     /* Walk through linked list, maintaining head pointer so we
        can free list later */

     for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
         if (ifa->ifa_addr == NULL)
             continue;

         family = ifa->ifa_addr->sa_family;

         /* Display interface name and family (including symbolic
            form of the latter for the common families) */

        if (family == AF_PACKET && ifa->ifa_data != NULL) {
             stats = ifa->ifa_data;
             if (!strcmp("eth0",ifa->ifa_name))
             printf("%-8s\n",ifa->ifa_name);

             printf("\t\ttx_bytes   = %10u; rx_bytes   = %10u\n",
                    stats->tx_bytes, stats->rx_bytes);
         }
     }

     freeifaddrs(ifaddr);
     exit(EXIT_SUCCESS);
 }
