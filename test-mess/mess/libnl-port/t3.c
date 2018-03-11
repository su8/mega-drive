#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <errno.h>
#include <net/if.h>
#include <netlink/netlink.h>
#include <netlink/genl/genl.h>
#include <netlink/genl/ctrl.h>
#include <linux/nl80211.h>
/* #include <linux/if_ether.h> */

#define INTERFACE "wlp0s18f2u5"

// https://www.infradead.org/~tgr/libnl/doc/core.html 
//  https://www.infradead.org/~tgr/libnl/doc/api/group__send__recv.html 
// http://lists.shmoo.com/pipermail/hostap/2011-October/024315.html 

int call_back(struct nl_msg *, void *);

int call_back(struct nl_msg *msg, void *dummy) {
    struct genlmsghdr *gnlh = nlmsg_data(nlmsg_hdr(msg));
    struct nlattr *tb[NL80211_ATTR_MAX + 1];
    struct nlattr *bss[NL80211_BSS_MAX + 1];
    struct nla_policy bss_policy[NL80211_BSS_MAX + 1] = {
            [NL80211_BSS_BSSID] = {},
            [NL80211_BSS_INFORMATION_ELEMENTS] = {}
    };
    uint32_t len = 0, x = 0, z = 0;
    char elo = '\0', *ssid = NULL, buf[50];

    if (nla_parse(tb, NL80211_ATTR_MAX, genlmsg_attrdata(gnlh, 0), genlmsg_attrlen(gnlh, 0), NULL) < 0)
        return NL_SKIP;

    if (tb[NL80211_ATTR_BSS] == NULL)
        return NL_SKIP;

    if (nla_parse_nested(bss, NL80211_BSS_MAX, tb[NL80211_ATTR_BSS], bss_policy))
        return NL_SKIP;

    if (bss[NL80211_BSS_STATUS] == NULL)
        return NL_SKIP;

    switch(nla_get_u32(bss[NL80211_BSS_STATUS])) {
	    case NL80211_BSS_STATUS_ASSOCIATED:
	    case NL80211_BSS_STATUS_AUTHENTICATED:
	    case NL80211_BSS_STATUS_IBSS_JOINED:
		    break;
	    default:
		    return NL_SKIP;
    }

    if (bss[NL80211_BSS_BSSID] == NULL)
        return NL_SKIP;

    if (bss[NL80211_BSS_INFORMATION_ELEMENTS]) {
        ssid = (char *)(nla_data(bss[NL80211_BSS_INFORMATION_ELEMENTS]) + 2);
        len = (uint32_t) nla_len(bss[NL80211_BSS_INFORMATION_ELEMENTS]);

        if (NULL != ssid && 0 != len) {

	    for (x =0;x < len;x++) {
		    elo = ssid[x];
		    if (!(isprint((unsigned char)elo))) break;
		    buf[z++] = elo;
	    }
	    buf[z] = '\0';
	    printf("%s\n", buf);
        }
    }

    (void)dummy;
    return NL_SKIP;
}


int main(void) {
    struct nl_sock *sk = nl_socket_alloc();
    struct nl_msg *msg = NULL;
    int fam = 0;
    uint32_t val = 0;
    char *elo = "there";
    void *scan_ret = NULL;

    if (!sk) {return 0;}
    if (genl_connect(sk) != 0)
        goto error;

    if (0 != (nl_socket_modify_cb(sk, NL_CB_VALID, NL_CB_CUSTOM, call_back, elo))) {
      goto error;
    }

    fam = genl_ctrl_resolve(sk, "nl80211");
    if (0 > fam)
        goto error;

    val = if_nametoindex(INTERFACE);
    if (val == 0)
        goto error;

    if ((msg = nlmsg_alloc()) == NULL)
        goto error;

    scan_ret = genlmsg_put(msg, 0, 0, fam, 0, NLM_F_DUMP, NL80211_CMD_GET_SCAN, 0);
    if (NULL == (scan_ret) ||
        0 != (nla_put_u32(msg, NL80211_ATTR_IFINDEX, val)))
        goto error;

    if (nl_send_sync(sk, msg) != 0)
        goto error;

error:
    if (NULL != msg)
	    nlmsg_free(msg);
    if (NULL != sk) {
	    nl_socket_free(sk);
    }

  return 0;
}
