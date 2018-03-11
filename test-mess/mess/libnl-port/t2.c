
/* Compile with:
 *  gcc -g -Wall -O0 -lnl test-libnl.c -o test-libnl
 */

#include <stdio.h>
#include <string.h>

#include <netlink/netlink.h>
#include <netlink/msg.h>

static struct nla_policy fubar_policy[IFLA_MAX+1] =
{
  [IFLA_IFNAME]   = { .type = NLA_STRING,
		      .maxlen = 256 },
  [IFLA_MTU]      = { .type = NLA_U32 },
  [IFLA_TXQLEN]   = { .type = NLA_U32 },
  [IFLA_LINK]     = { .type = NLA_U32 },
  [IFLA_WEIGHT]   = { .type = NLA_U32 },
  [IFLA_COST]     = { .type = NLA_U32 },
  [IFLA_PRIORITY] = { .type = NLA_U32 },
  [IFLA_PROTINFO] = { .type = NLA_U32 },
  [IFLA_MASTER]   = { .type = NLA_U32 },
  [IFLA_QDISC]    = { .type = NLA_STRING,
		      .maxlen = 256 },
  [IFLA_STATS]    = { .minlen = sizeof(struct rtnl_link_stats) },
  [IFLA_MAP]      = { .minlen = sizeof(struct rtnl_link_ifmap) },
};

int
main (int argc, char **argv)
{
  struct nl_handle *nl;
  struct nlmsghdr   hdr = { 0, };
  struct ifinfomsg  ifi = { 0, };
  struct nl_msg    *msg;
  const char       *ifname;
  int               retval;

  if (!(nl = nl_handle_alloc()))
    {
      fprintf (stderr, "Cannot allocate netlink handle: %s\n",
	       nl_geterror ());
      return 1;
    }

  retval = 0;
  msg = NULL;

  if (nl_connect(nl, NETLINK_ROUTE) < 0 )
    {
      fprintf (stderr, "Cannot connect netlink socket: %s\n",
	       nl_geterror ());
      retval = 1;
      goto error;
    }

  hdr.nlmsg_type = RTM_GETLINK;
  /* hdr.nlmsg_flags = NLM_F_REQUEST | NLM_F_MATCH | NLM_F_ATOMIC; */
  hdr.nlmsg_flags = NLM_F_REQUEST | NLM_F_DUMP;

  if (!(msg = nlmsg_build (&hdr)))
    {
      fprintf (stderr, "Cannot build netlink message: %s\n",
	       nl_geterror ());
      retval = 1;
      goto error;
    }

  ifi.ifi_index = 10;

  if (nlmsg_append (msg, &ifi, sizeof (struct ifinfomsg), 1) < 0)
    {
      fprintf (stderr, "Cannot append to netlink message: %s\n",
	       nl_geterror ());
      retval = 1;
      goto error;
    }

  ifname = "eth0";

  if (nla_put (msg, IFLA_IFNAME, strlen (ifname) + 1, ifname) < 0)
    {
      fprintf (stderr, "Failed to append ifname to netlink message: %s\n",
	       nl_geterror ());
      return 1;
    }

  if (nl_send_auto_complete (nl, nlmsg_hdr (msg)) < 0)
    {
      fprintf (stderr, "Failed to send netlink message: %s\n",
	       nl_geterror ());
      retval = 1;
      goto error;
    }

  do
    {
      int len;
      struct sockaddr_nl peer;
      unsigned char *msg;
      struct nlmsghdr *ret_hdr;

      msg = NULL;
      
      if ((len = nl_recv (nl, &peer, (void *)&msg)) < 0)
	{
	  fprintf (stderr, "Error receiving reply to netlink message: %s\n",
		   nl_geterror ());
	  retval = 1;
	  goto error;
	}

      printf ("len = %d, msg_len = %d, msg_type = %d\n", len, ret_hdr->nlmsg_len, ret_hdr->nlmsg_type);

      if (len == 0)
	{
	  fprintf (stderr, "No more messages\n");
	  free (msg);
	  break;
	}

      ret_hdr = (struct nlmsghdr *) msg;

      while (nlmsg_ok (ret_hdr, len))
	{
	  struct nl_attr *attrs[IFLA_MAX];
	  int i;

	  if (ret_hdr->nlmsg_type == NLMSG_ERROR)
	    {
	      struct nlmsgerr *e = nlmsg_data (ret_hdr);
	      fprintf (stderr, "Error reply returned: %s\n", strerror (-e->error));
	      ret_hdr = nlmsg_next (ret_hdr, &len);
	      continue;
	    }

	  if (ret_hdr->nlmsg_type != RTM_NEWLINK)
	    {
	      fprintf (stderr, "Unknown reply returned\n");
	      ret_hdr = nlmsg_next (ret_hdr, &len);
	      continue;
	    }

	  for (i = 0; i < IFLA_MAX; i++)
	    attrs[i] = NULL;

	  if (nlmsg_parse(ret_hdr, sizeof (struct ifinfomsg), (void *)attrs, IFLA_MAX, fubar_policy) < 0)
	    {
	      fprintf (stderr, "Failed to parse reply to netlink message: %s\n",
		       nl_geterror ());
	      ret_hdr = nlmsg_next (ret_hdr, &len);
	      continue;
	    }

	  if (attrs[IFLA_IFNAME] != NULL)
	    {
	      char name[256];

	      memcpy (name,
		      nla_data((void *) attrs[IFLA_IFNAME]),
		      nla_len((void *) attrs[IFLA_IFNAME]));

	      printf ("%s\n", name);
	    }

	  ret_hdr = nlmsg_next (ret_hdr, &len);
	}

      /* free (msg); */
    } while (1);

 error:
  if (msg != NULL)
    nlmsg_free (msg);
  nl_handle_destroy (nl);
  
  return retval;
}

