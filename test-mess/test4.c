#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

extern	char *__progname;

static void usage(void);

int
main(int argc, char *argv[])
{
	int ch, sflag;
	char *p, hostname[HOST_NAME_MAX+1];

	sflag = 0;
	while ((ch = getopt(argc, argv, "s")) != -1)
		switch (ch) {
		case 's':
			sflag = 1;
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (argc > 1)
		usage();

	if (*argv) {
		if (sethostname(*argv, strlen(*argv)))
			err(1, "sethostname");
	} else {
		if (gethostname(hostname, sizeof(hostname)))
			err(1, "gethostname");
		if (sflag && (p = strchr(hostname, '.')))
			*p = '\0';
		(void)printf("%s\n", hostname);
	}
	return(0);
}

static void 
usage(void)
{
	(void)fprintf(stderr, "usage: %s [-s] [name-of-host]\n", __progname);
	exit(1);
}
