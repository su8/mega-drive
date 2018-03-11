
#include <stdio.h>
#include <stdint.h>
#include <string.h>
/* #include <sys/ioctl.h> */
/* #include <sys/stat.h> */
/* #include <net/if.h> */
/* #include <linux/sockios.h> */
/* #include <linux/ethtool.h> */

/* #include <ctype.h> */
#include <arpa/inet.h>
/* #include <netdb.h> */
#include <sys/socket.h>
#include <ifaddrs.h>
#include <netpacket/packet.h>
#include <net/if.h>
#include <linux/if_link.h>
#include <sys/ioctl.h>
#include <linux/sockios.h>
#include <linux/ethtool.h>

int refresh_net_dev_ioctl_speed_duplex(void);

int refresh_net_dev_ioctl_speed_duplex(void)
{        
    struct ethtool_cmd ecmd;
    struct ifreq ifr;
    int fd;

    fd = socket(AF_INET, SOCK_DGRAM, 0);         
    if (fd < 0)
      return -1;

    ecmd.cmd = ETHTOOL_GSET;
    ifr.ifr_data = (char *)&ecmd;

    /* strncpy(ifr.ifr_name, name, IF_NAMESIZE); */
    snprintf(ifr.ifr_name, IF_NAMESIZE, "%s", "eth0");
    /* ifr.ifr_name[IF_NAMESIZE-1] = '\0'; */
    if (!(ioctl(fd, SIOCETHTOOL, &ifr) < 0)) {
        fprintf(stderr, "speed ioctl val %d %s\n", ecmd.speed, (999 > ecmd.speed ? "Mbps" : "Gbps"));
        return 1;
    }    
    return -1;
}        

int main(void) {
	refresh_net_dev_ioctl_speed_duplex();	
	return 0;
}
