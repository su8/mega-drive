/* 
 * getaddrinfo.c - Simple example of using getaddrinfo(3) function.
 * 
 * Michal Ludvig <michal@logix.cz> (c) 2002, 2003
 * http://www.logix.cz/michal/devel/
 *
 * License: public domain.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
/* #include <sys/types.h> */
#include <sys/socket.h>
#include <arpa/inet.h>

int lookup_host(char *);
int
lookup_host (char *host)
{
  struct addrinfo *rp = NULL, *result = NULL;
  struct addrinfo hints;
  int errcode;
  char addrstr[100];
  void *ptr = NULL;

  memset (&hints, 0, sizeof (hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_DGRAM;
  hints.ai_flags = 0;
  hints.ai_protocol = 0;

  errcode = getaddrinfo (host, NULL, &hints, &result);
  if (errcode != 0)
    {

    printf("%s\n", "err dude!");
      /* perror ("getaddrinfo"); */
      return -1;
    }

  for (rp = result; NULL != rp; rp = rp->ai_next) {
    if (NULL == rp->ai_addr) {
      continue;
    }

    if (NULL != rp->ai_addr->sa_data && rp->ai_family == AF_INET) {
      ptr = &((struct sockaddr_in *) rp->ai_addr)->sin_addr;
      inet_ntop (AF_INET, ptr, addrstr, 100);
      printf ("IPv%d addrps: %s\n", 4, addrstr);
    }
  }

  if ('\0' == addrstr[0]) {
    printf("%s\n", "empty dude!");
  }

  if (NULL != result)
    freeaddrinfo(result);

  return 0;
}

int
main (void)
{
  /* if (argc < 2) */
  /*   exit (1); */
  return lookup_host ((char *)"google.com");
}
