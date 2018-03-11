/* #include <stdio.h> */

/* #include <netlink/netlink.h> */
/* #include <netlink/route/link.h> */
/* #include <unistd.h> */
/* int main(int argc, char*argv[]) */
/* { */
/* if (argc != 2) { */
/* printf("Usage %s interface\n", argv[0]); */
/* return -1; */
/* } */
/* int ret = 0; */
/* struct nl_handle *handle; */

/* // Allocate and initialize a new netlink handle */
/* // This is the first in using the library */
/* handle = nl_handle_alloc(); */
/* if (handle == 0) { */
/* printf("Failed to alloc netlink handle\n"); */
/* ret = -1; */
/* goto error_handle; */
/* } */

/* // Bind and connect the socket to a protocol, */
/* // NETLINK_ROUTE in our case. */
/* ret = nl_connect(handle, NETLINK_ROUTE); */
/* if (ret != 0) { */
/* printf("Failed to connect to kernel\n"); */
/* ret = -1; */
/* goto error_connect; */
/* } */


/* // Event notifications are typically sent to multicast */
/* // addresses which are represented by groups. */
/* // Join a group to receive link notifications. */
/* ret = nl_socket_add_membership(handle, RTNLGRP_LINK); */
/* if (ret != 0) { */
/* printf("Joining group failed\n"); */
/* ret = -1; */
/* goto error_connect; */
/* } */


/* // The first step is to retrieve a list of all available */
/* // interfaces within the kernel and put them into a cache. */
/* struct nl_cache *cache = rtnl_link_alloc_cache(handle); */
/* if (cache == 0) { */
/* printf("Error creating link cache\n"); */
/* ret = -1; */
/* goto error_connect; */
/* } */

/* // In a second step, a specific link may be looked up */
/* // by either interface index or interface name. */
/* struct rtnl_link *link = rtnl_link_get_by_name(cache, argv[1]); */
/* if (link == 0) { */
/* printf("No such interface %s\n", argv[1]); */
/* ret = -1; */
/* goto error_cache; */
/* } */

/* printf("Packets sent %llu\n", */
/* rtnl_link_get_stat(link, RTNL_LINK_TX_PACKETS)); */
/* printf("Packets received %llu\n", */
/* rtnl_link_get_stat(link, RTNL_LINK_RX_PACKETS)); */


/* // After successful usage, the object must be */
/* // given back to the cache */
/* rtnl_link_put(link); */
/* error_cache: */
/* // release the cache */
/* nl_cache_free(cache); */
/* error_connect: */
/* // close the handle */
/* nl_handle_destroy(handle); */
/* error_handle: */
/* return ret; */
/* } */

#include <sys/socket.h>
#include <linux/netlink.h>

#define MAX_PAYLOAD 1024  /* maximum payload size*/
struct sockaddr_nl src_addr, dest_addr;
struct nlmsghdr *nlh = NULL;
struct iovec iov;
int sock_fd;

void main() {
 sock_fd = socket(PF_NETLINK, SOCK_RAW,NETLINK_TEST);

 memset(&src_addr, 0, sizeof(src_addr));
 src__addr.nl_family = AF_NETLINK;
 src_addr.nl_pid = getpid();  /* self pid */
 src_addr.nl_groups = 0;  /* not in mcast groups */
 bind(sock_fd, (struct sockaddr*)&src_addr,
      sizeof(src_addr));

 memset(&dest_addr, 0, sizeof(dest_addr));
 dest_addr.nl_family = AF_NETLINK;
 dest_addr.nl_pid = 0;   /* For Linux Kernel */
 dest_addr.nl_groups = 0; /* unicast */

 nlh=(struct nlmsghdr *)malloc(
		         NLMSG_SPACE(MAX_PAYLOAD));
 /* Fill the netlink message header */
 nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
 nlh->nlmsg_pid = getpid();  /* self pid */
 nlh->nlmsg_flags = 0;
 /* Fill in the netlink message payload */
 strcpy(NLMSG_DATA(nlh), "Hello you!");

 iov.iov_base = (void *)nlh;
 iov.iov_len = nlh->nlmsg_len;
 msg.msg_name = (void *)&dest_addr;
 msg.msg_namelen = sizeof(dest_addr);
 msg.msg_iov = &iov;
 msg.msg_iovlen = 1;

 sendmsg(fd, &msg, 0);

 /* Read message from kernel */
 memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
 recvmsg(fd, &msg, 0);
 printf(" Received message payload: %s\n",
	NLMSG_DATA(nlh));

 /* Close Netlink Socket */
 close(sock_fd);
}

