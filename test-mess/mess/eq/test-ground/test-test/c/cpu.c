/* # include <gnu/stubs-32.h> */


#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <glob.h>
#include <unistd.h>
/* #include <arpa/inet.h> */
/* #include <netdb.h> */
#include <sys/socket.h>
#include <ifaddrs.h>
#include <linux/if_link.h>
/* #include <sys/time.h> */

static __inline__ unsigned long int rdtsc(void) {
	unsigned long int x;
	__asm__ volatile ("rdtsc":"=A" (x));
	return x;
}

int main (void) {

  /* struct timespec tc = {0}; */
  /* tc.tv_nsec = sysconf(_SC_CLK_TCK) * 1000000L; */
  /* nanosleep(&tc, NULL); */
	/* struct timezone tz; */
	/* struct timeval tvstart, tvstop; */
	struct timespec start = {0}, stop = {0};
	/* struct timespec stop = {0}; */
	unsigned long y;	/* gotta be 64 bit */
	unsigned long x;	/* gotta be 64 bit */
	unsigned long int z[2];	/* total time taken */
	/* clock_t start, end; */

	/* memset(&tz, 0, sizeof(tz)); */

	/* get this function in cached memory */
	/* gettimeofday(&tvstart, NULL); */
	 x = rdtsc();
	 clock_gettime(CLOCK_MONOTONIC, &start);
   z[0] = (unsigned long)(start.tv_nsec - start.tv_sec);
	 /* clock_gettime(CLOCK_MONOTONIC, &stop); */
	/* gettimeofday(&tvstart, NULL); */
   /* clock_t start = clock(); */
/* start = clock( ); */
	usleep(100);
   /* end = clock(); */
   /* double time_elapsed_in_seconds = (end - start); */
	/* we don't trust that this is any specific length of time */

/* char buffer[30]; */
/*   struct timeval tv; */

/*   time_t curtime; */


 /* gettimeofday(&tv, NULL); */ 
 /* curtime=tv.tv_sec; */

 /* strftime(buffer,30,"%m-%d-%Y  %T.",localtime(&curtime)); */
 /* printf("%s%ld\n",buffer,tv.tv_usec); */

	/* gettimeofday(&tvstop, NULL); */
	y = rdtsc();
	 clock_gettime(CLOCK_MONOTONIC, &stop);
	z[1] = (unsigned long)(stop.tv_nsec - stop.tv_sec);
	/* unsigned long delay = (z[1]-z[0]); */
	/* printf("%lld\n",z[0]); */
	/* printf("%lld\n",z[1]); */
	/* printf("%lld\n",delay/1000); */
	/* printf("%ld\n",stop.tv_sec); */
	/* z = (unsigned long)(stop.tv_sec+stop.tv_nsec)-(unsigned long)((start.tv_sec*+start.tv_nsec)); */

	/* printf("%d\n", (int)end-start); */
/* printf("%lld\n",(cycles[1]-cycles[0])/((unsigned long int)end -   (unsigned long int)start)*10/100); */
/* printf("%d\n",(int)(stop.tv_sec),(int)start.tv_sec)); */
	printf("%ldMHz\n", (1000* (y - x)/(z[1]-z[0])));
	/* printf("%lldMHz\n", delay); */


  /* printf ("CPU clock speed: %lld MHz\n", get_cpu_clock_speed ()); */
  return 0;
}


