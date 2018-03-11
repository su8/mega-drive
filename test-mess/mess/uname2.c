/*
    uname2.c -- my 'uname' implementation
    Compile with: gcc -Wall -O2 -o uname2 uname2.c
 
   Copyright 01/17/2015 Aaron Caffrey https://github.com/wifiextender
 
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.
 
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
 
   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.
*/

#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <argp.h>

#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>

/* inline int clock_gettime_int64(clock_t clk, uint64_t* res) { */
/*     struct timespec ts; */
/*     int ret = clock_gettime(clk, &ts); */
/*     if (ret == 0) */
/*       printf("%s\n", "meow"); */
/*       *res = (int64_t)ts.tv_sec * SECS + (int64_t)ts.tv_nsec; */
/*     return ret; */
/* } */
int main(void)
{
/* struct sysinfo s; */
/* sysinfo(&s); */
/*     printf("%.2f %.2f %.2f\n", (float)s.loads[0] / (float)USHRT_MAX, */
/*         (float)s.loads[1] / (float)USHRT_MAX, */
/*         (float)s.loads[2] / (float)USHRT_MAX); */

    /* double v[3]; */
    /* getloadavg(v, 3); */

    /* printf("%.2f %.2f %.2f\n", v[0], v[1], v[2]); */

    struct timespec tp = {0};

    clock_gettime(CLOCK_BOOTTIME, &tp);

    printf("%lu\n", (tp.tv_sec/3600) % 24);
/* uint64_t value; */
/*   clock_gettime_int64(CLOCK_BOOTTIME, &value); */
/*   printf("clock_gettime(BOOTTIME)    %" PRId64 "\n", value); */

    return EXIT_SUCCESS;
}
