/* 
   iflist.c : retrieve network interface information thru netlink sockets

   (c) Jean Lorchat @ Internet Initiative Japan - Innovation Institute

   v1.0 : initial version - Feb 19th 2010

   This file was obtained at the following address :
   http://www.iijlab.net/~jean/iflist.c

   Find out more on the blog post :
   http://iijean.blogspot.com/2010/03/howto-get-list-of-network-interfaces-in.html
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/sysinfo.h>
#include <sys/statvfs.h>

#define IFLIST_REPLY_BUFFER	8192

#define MB 1048576
#define GB 1073741824

int main(void) {
  unsigned long int total = 0;
  struct statvfs ssd;
  statvfs("/", &ssd);
  // f_blocks - total , f_bfree , f_bavail
  total   = (ssd.f_bavail * ssd.f_bsize);
  /* used    = (mem.totalram - mem.freeram - */
  /*                  mem.bufferram - mem.sharedram) / MB; */
  /* percent = (used * 100) / total; */
  printf("%lu\n", total/GB);

  return EXIT_SUCCESS;
}

/* 
   define the message structure : 
     . a netlink message
     . a "general form of address family dependent" message, 
       i.e. how to tell which AF we are interested in
*/

/* typedef struct nl_req_s nl_req_t; */  

/* struct nl_req_s { */
/*   struct nlmsghdr hdr; */
/*   struct rtgenmsg gen; */
/* }; */

/* rtnl_print_route(struct nlmsghdr *nlh) */
/* { */
/*     struct  rtmsg *route_entry;  /1* This struct represent a route entry \ */
/*                                     in the routing table *1/ */
/*     struct  rtattr *route_attribute; /1* This struct contain route \ */
/*                                             attributes (route type) *1/ */
/*     int     route_attribute_len = 0; */
/*     unsigned char    route_netmask = 0; */
/*     unsigned char    route_protocol = 0; */
/*     char    destination_address[32]; */
/*     char    gateway_address[32]; */

/* 	printf("here we are\n"); */
/* 	route_entry = (struct rtmsg *) NLMSG_DATA(nlh); */

/* 	if (route_entry->rtm_table != RT_TABLE_MAIN) */
/* 		return; */

/* 	route_netmask = route_entry->rtm_dst_len; */
/* 	route_protocol = route_entry->rtm_protocol; */
/*     route_attribute = (struct rtattr *) RTM_RTA(route_entry); */
/*     /1* Get the route atttibutes len *1/ */
/*     route_attribute_len = RTM_PAYLOAD(nlh); */
/*     /1* Loop through all attributes *1/ */
/*     for ( ; RTA_OK(route_attribute, route_attribute_len); \ */
/*         route_attribute = RTA_NEXT(route_attribute, route_attribute_len)) */
/*     { */
/* 		printf("route attribute type: %d\n", route_attribute->rta_type); */
/*         /1* Get the destination address *1/ */
/*         if (route_attribute->rta_type == RTA_DST) */
/*         { */
/*             inet_ntop(AF_INET, RTA_DATA(route_attribute), \ */
/*                     destination_address, sizeof(destination_address)); */
/*         } */
/*         /1* Get the gateway (Next hop) *1/ */
/*         if (route_attribute->rta_type == RTA_GATEWAY) */
/*         { */
/*             inet_ntop(AF_INET, RTA_DATA(route_attribute), \ */
/*                     gateway_address, sizeof(gateway_address)); */
/*         } */
/*     } */
/* 	printf("route to destination --> %s/%d proto %d and gateway %s\n", \ */
/*          destination_address, route_netmask, route_protocol, gateway_address); */

/* } */

/* int */
/* main(int argc, char **argv) */
/* { */
/*   int fd; */
/*   struct sockaddr_nl local;  /1* our local (user space) side of the communication *1/ */
/*   struct sockaddr_nl kernel; /1* the remote (kernel space) side of the communication *1/ */
 
/*   struct msghdr rtnl_msg;    /1* generic msghdr struct for use with sendmsg *1/ */
/*   struct iovec io;	     /1* IO vector for sendmsg *1/ */

/*   nl_req_t req;              /1* structure that describes the rtnetlink packet itself *1/ */
/*   char reply[IFLIST_REPLY_BUFFER]; /1* a large buffer to receive lots of link information *1/ */

/*   pid_t pid = getpid();	     /1* our process ID to build the correct netlink address *1/ */
/*   int end = 0;		     /1* some flag to end loop parsing *1/ */

/*   /1* */ 
/*      prepare netlink socket for kernel/userland communication */ 
/*      we are interested in the ROUTE flavor. */ 

/*      There are others like XFRM, but to deal with links, addresses and obviously routes, */
/*      you have to use NETLINK_ROUTE. */
     
/*    *1/ */

/*   fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_ROUTE); */

/*   memset(&local, 0, sizeof(local)); /1* fill-in local address information *1/ */
/*   local.nl_family = AF_NETLINK; */
/*   local.nl_pid = pid; */
/*   local.nl_groups = 0; */
/*   //local.nl_groups = RTMGRP_IPV4_ROUTE; */

/*   if (bind(fd, (struct sockaddr *) &local, sizeof(local)) < 0) */
/*     { */
/*       perror("cannot bind, are you root ? if yes, check netlink/rtnetlink kernel support"); */
/*       return -1; */
/*     } */

/*   /1* RTNL socket is ready for use, prepare and send request *1/ */

/*   memset(&rtnl_msg, 0, sizeof(rtnl_msg)); */
/*   memset(&kernel, 0, sizeof(kernel)); */
/*   memset(&req, 0, sizeof(req)); */

/*   kernel.nl_family = AF_NETLINK; /1* fill-in kernel address (destination of our message) *1/ */
/*   kernel.nl_groups = 0; */

/*   req.hdr.nlmsg_len = NLMSG_LENGTH(sizeof(struct rtgenmsg)); */
/*   req.hdr.nlmsg_type = RTM_GETROUTE; */
/*   req.hdr.nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP; */ 
/*   req.hdr.nlmsg_seq = 1; */
/*   req.hdr.nlmsg_pid = pid; */
/*   //req.gen.rtgen_family = AF_PACKET; /1*  no preferred AF, we will get *all* interfaces *1/ */
/*   req.gen.rtgen_family = AF_INET; */ 

/*   io.iov_base = &req; */
/*   io.iov_len = req.hdr.nlmsg_len; */
/*   rtnl_msg.msg_iov = &io; */
/*   rtnl_msg.msg_iovlen = 1; */
/*   rtnl_msg.msg_name = &kernel; */
/*   rtnl_msg.msg_namelen = sizeof(kernel); */

/*   sendmsg(fd, (struct msghdr *) &rtnl_msg, 0); */

/*   /1* parse reply *1/ */

/*   while (!end) */
/*     { */
/*       int len; */
/*       struct nlmsghdr *msg_ptr;	/1* pointer to current message part *1/ */

/*       struct msghdr rtnl_reply;	/1* generic msghdr structure for use with recvmsg *1/ */
/*       struct iovec io_reply; */

/*       memset(&io_reply, 0, sizeof(io_reply)); */
/*       memset(&rtnl_reply, 0, sizeof(rtnl_reply)); */

/*       io.iov_base = reply; */
/*       io.iov_len = IFLIST_REPLY_BUFFER; */
/*       rtnl_reply.msg_iov = &io; */
/*       rtnl_reply.msg_iovlen = 1; */
/*       rtnl_reply.msg_name = &kernel; */
/*       rtnl_reply.msg_namelen = sizeof(kernel); */

/*       len = recvmsg(fd, &rtnl_reply, 0); /1* read as much data as fits in the receive buffer *1/ */
/*       if (len) */
/* 	{ */
/* 	  for (msg_ptr = (struct nlmsghdr *) reply; NLMSG_OK(msg_ptr, len); msg_ptr = NLMSG_NEXT(msg_ptr, len)) */
/* 	    { */
/* 	      switch(msg_ptr->nlmsg_type) */
/* 		{ */
/* 		case 3:		/1* this is the special meaning NLMSG_DONE message we asked for by using NLM_F_DUMP flag *1/ */
/* 		  end++; */
/* 		  break; */
/* 		case 24: */
/* 		  rtnl_print_route(msg_ptr); */
/* 		  break; */
/* 		} */
/* 	    } */
/* 	} */
      
/*     } */

/*   /1* clean up and finish properly *1/ */

/*   close(fd); */

/*   return 0; */
/* } */
