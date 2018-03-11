/*
   Copyright 08/06/2016
   Aaron Caffrey https://github.com/wifiextender

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

#include "config.h"

#include "include/headers.h"
#include "prototypes/cpu.h"

#if defined(__FreeBSD__)
#include "include/freebzd.h"
#endif /* __FreeBSD__ */

#if defined(__linux__)
#define IDLE_NUM 3
#define LOOP_ITERZ 10

#else /* FreeBSD */
#define IDLE_NUM 4
#define LOOP_ITERZ 5
#endif /* __linux__ */

void 
get_cpu(char *str1) {
  static uintmax_t previous_total = 0, previous_idle = 0;
  uintmax_t x, percent, diff_total, diff_idle, cpu_active[LOOP_ITERZ];
  uintmax_t total = 0;

  memset(cpu_active, 0, sizeof(cpu_active));

#if defined(__FreeBSD__)
  size_t len = sizeof(cpu_active);
  SYSCTLVAL("kern.cp_time", &cpu_active);
#endif /* __FreeBSD__ */

#if defined(__linux__)
  FILE *fp = fopen("/proc/stat", "r");
  if (NULL == fp) {
    exit_with_err(CANNOT_OPEN, "/proc/stat");
  }

  /* Some kernels will produce 7, 8 and 9 columns
   * We rely on 10, refer to `man proc' for more details */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  if (fscanf(fp, "%*s " FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT,
    &cpu_active[0], &cpu_active[1], &cpu_active[2], &cpu_active[3],
    &cpu_active[4], &cpu_active[5], &cpu_active[6], &cpu_active[7],
    &cpu_active[8], &cpu_active[9]) == EOF) {
      fclose(fp);
      exit_with_err(ERR,"Upgrade to a newer kernel");
  }
#pragma GCC diagnostic pop
  fclose(fp);
#endif /* __linux__ */

  for (x = 0; x < LOOP_ITERZ; x++) {
    total += cpu_active[x];
  }

  diff_total     = total - previous_total;
  diff_idle      = cpu_active[IDLE_NUM] - previous_idle;

  previous_total = total;
  previous_idle  = cpu_active[IDLE_NUM];

  percent        = (TICKZ * (diff_total - diff_idle)) / diff_total;

  FILL_UINT_ARR(str1, percent);
}


void
get_cores_load(char *str1) {
  static uintmax_t previous_total[MAX_CORES], previous_idle[MAX_CORES];
  static uintmax_t test_flag = 0;
  uintmax_t x = 0, y = 0, z = 0;
  uintmax_t percent[MAX_CORES], diff_total[MAX_CORES], core_active[MAX_CORES][LOOP_ITERZ];
  uintmax_t diff_idle[MAX_CORES], total[MAX_CORES];
  char buf[VLA], temp[VLA];
  char *all = temp;

  memset(percent, 0, sizeof(percent));
  memset(diff_total, 0, sizeof(diff_total));
  memset(diff_idle, 0, sizeof(diff_idle));
  memset(total, 0, sizeof(total));
  memset(core_active, 0, sizeof(core_active));

  if (0 == test_flag) {
    memset(previous_idle, 0, sizeof(previous_idle));
    memset(previous_total, 0, sizeof(previous_total));
  }

#if defined(__FreeBSD__)
  size_t len = sizeof(core_active);
  SYSCTLVAL("kern.cp_times", &core_active);
#endif /* __FreeBSD__ */

#if defined(__linux__)
  FILE *fp = fopen("/proc/stat", "r");
  if (NULL == fp) {
    exit_with_err(CANNOT_OPEN, "/proc/stat");
  }

  if (NULL == fgets(buf, VLA, fp)) {
    fclose(fp);
    exit_with_err(ERR, "reached /proc/stat EOF");
  }

  for (x = 0; x < MAX_CORES; x++) {
    if (NULL == fgets(buf, VLA, fp)) {
      fclose(fp);
      exit_with_err(ERR, "reached /proc/stat EOF");
    }

    if (buf[0] != 'c' && buf[1] != 'p' && buf[2] != 'u') {
      break;
    }

    if (sscanf(buf, "%*s " FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT FMT_UINT,
      &core_active[x][0], &core_active[x][1], &core_active[x][2], &core_active[x][3],
      &core_active[x][4], &core_active[x][5], &core_active[x][6], &core_active[x][7],
      &core_active[x][8], &core_active[x][9]) == EOF) {
        fclose(fp);
        exit_with_err(ERR,"Upgrade to a newer kernel");
    }
  }
  fclose(fp);

  z = x;
  for (x = 0; x < z; x++) {

#else /* FreeBSD */
  for (x = 0; x < MAX_CORES; x++) {
    if (0 == core_active[x][0] && 0 ==
      core_active[x][1] && 0 ==
      core_active[x][2]) {
	    break;
    }
#endif /* __linux__ */

    for (y = 0; y < LOOP_ITERZ; y++) {
      total[x] += core_active[x][y];
    }

    diff_total[x]     = total[x] - previous_total[x];
    diff_idle[x]      = core_active[x][IDLE_NUM] - previous_idle[x];

    previous_total[x] = total[x];
    previous_idle[x]  = core_active[x][IDLE_NUM];

    percent[x]        = (TICKZ * (diff_total[x] - diff_idle[x]))
                            / diff_total[x];

    GLUE2(all, FMT_UINT"%% ", percent[x]);
  }

  test_flag = 1;

  FILL_STR_ARR(1, str1, temp);
}


#if defined(__linux__)
void
get_cpu_temp(char *str1) {
  get_temp(CPU_TEMP_FILE, str1);
}

#else /* FreeBSD */


/*
  Go figure which one to blame.

  the "aibs" module temps:
  dev.aibs.0.temp.0: 39.0C

  the "amdtemp" module temps:
  dev.cpu.0.temperature: 28.5C

  In linux the "aibs" temps are matching
  my idle temps.
*/
void
get_cpu_temp(char *str1) {
  u_int temp = 0;
  uintmax_t temp2 = 0;
  size_t len = sizeof(temp);

  SYSCTLVAL("dev.cpu.0.temperature", &temp);
  temp2 = (uintmax_t)temp;

  if (9999 < temp2) { /* > 99C */
	  FILL_UINT_ARR(str1, temp2 / 1000);
  } else {
    FILL_UINT_ARR(str1, ((999 < temp2) ?
      temp2 / 100 : temp2/10)); /* > 9C || < 9C */
  }
}

#endif /* __linux__ */


/*  Taken from the gcc documentation
 *  https://gcc.gnu.org/onlinedocs/gcc/Machine-Constraints.html
 *
 *  other useful resources:
 *  http://www.felixcloutier.com/x86/RDTSC.html 
 *  http://ref.x86asm.net/coder32.html#x0F31 
*/

/* Not going to test for i486 and i586 */
#if defined(__i386__) || defined(__i686__)
static __inline__ uintmax_t 
rdtsc(void) {
  uintmax_t x;
  __asm__ __volatile__ (".byte 0x0f, 0x31" : "=A" (x));
  return x;
}

void
get_cpu_clock_speed(char *str1) {
  uintmax_t x, y, z[2];

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  struct timespec start = {0}, stop = {0}, tc = {0};
#pragma GCC diagnostic pop

  tc.tv_nsec = TICKZ * 1000000L;

  x = rdtsc();
  if (-1 == (clock_gettime(CLOCK_MONOTONIC, &start))) {
    FUNC_FAILED("clock_gettime()");
  }
  z[0] = (uintmax_t)(start.tv_nsec - start.tv_sec);

  if (-1 == (nanosleep(&tc, NULL))) {
    FUNC_FAILED("nanosleep()");
  }

  y = rdtsc();
  if (-1 == (clock_gettime(CLOCK_MONOTONIC, &stop))) {
    FUNC_FAILED("clock_gettime()");
  }
  z[1] = (uintmax_t)(stop.tv_nsec - stop.tv_sec);

  FILL_ARR(str1, FMT_UINT " MHz",
    (1000 * (y - x) / (z[1] - z[0])));
}


#elif defined(__x86_64__)
static __inline__ uintmax_t 
rdtsc(void) {
  unsigned int tickhi, ticklo;
  __asm__ __volatile__ ("rdtsc" : "=a"(ticklo), "=d"(tickhi));
  return (((uintmax_t)tickhi << 32) | (uintmax_t)ticklo);
}

void
get_cpu_clock_speed(char *str1) {
  uintmax_t x, z;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  struct timespec tc = {0};
#pragma GCC diagnostic pop

  tc.tv_nsec = TICKZ * 1000000L;

  x = rdtsc();
  if (-1 == (nanosleep(&tc, NULL))) {
    FUNC_FAILED("nanosleep()");
  }
  z = rdtsc();

  FILL_ARR(str1, FMT_UINT " MHz", ((z - x) / 100000));
}
#endif


#if defined(__i386__) || defined(__i686__) || defined(__x86_64__)
void
get_cpu_info(char *str1) {
  char buffer[VLA], vend_id[13];
  char *all = buffer;
  uintmax_t vend = 0, num = 0, vend_str = 0, x = 0, z = 0;
  uintmax_t eax = 0, ecx = 0, edx = 0, ebx = 0, eax_old = 0;

  CPU_VENDOR(0, vend);
  if (0 == vend) {
    FILL_STR_ARR(1, str1, "Null");
    return;
  }
  CPU_FEATURE(1, eax_old);

  switch(vend) {
    case AmD:
      num = 0;
      break;

    case InteL:
      num = 1;
      break;
  }

  /* Dont have intel cpu to verify the following code
     It works fine on both of my primary amd systems.
     I'm also aware of linking against assembly object file,
     wanted to learn more assembly by back porting it to C */
  if (0 == num) {
    CPU_FEATURE(0x80000000, vend_str);                /* movl $0x80000000, %eax */
    if (0 != vend_str) {

      for (x = 0x80000002; x <= 0x80000004; x++) {    /* movl $0x80000002, %esi */
        CPU_STR2(x, eax, ebx, ecx, edx);              /* cmpl $0x80000004, %eax */
        char vend_chars[17]; /* 12 + 4 */

        for (z = 0; z < 4; z++) {
          vend_chars[z] = (char)(eax >> (z * 8));     /* movl %eax */
          vend_chars[z+4] = (char)(ebx >> (z * 8));   /* movl %ebx, 4 */
          vend_chars[z+8] = (char)(ecx >> (z * 8));   /* movl %ecx, 8 */
          vend_chars[z+12] = (char)(edx >> (z * 8));  /* movl %edx, 12 */
        }
        vend_chars[16] = '\0';
        GLUE2(all, "%s", vend_chars);
      }

      CPU_ID_STR(0, ebx, ecx, edx);                   /* mov $0, %eax */
      for (z = 0; z < 4; z++) {
        vend_id[z] = (char)(ebx >> (z * 8));          /* movl %ebx, 0 */
        vend_id[z+4] = (char)(edx >> (z * 8));        /* movl %edx, 4 */
        vend_id[z+8] = (char)(ecx >> (z * 8));        /* movl %ecx, 8 */
      }
      vend_id[12] = '\0';

      FILL_ARR(str1, "%s ID %s Stepping " FMT_UINT " Family " FMT_UINT " Model " FMT_UINT,
        buffer, vend_id, BIT_SHIFT(eax_old),
        BIT_SHIFT(eax_old >> 8), BIT_SHIFT(eax_old >> 4));
      return;
    }
  }

  FILL_ARR(str1, "%s Stepping " FMT_UINT " Family " FMT_UINT " Model " FMT_UINT,
    (0 == num ? "AMD" : "Intel"), BIT_SHIFT(eax_old),
    BIT_SHIFT(eax_old >> 8), BIT_SHIFT(eax_old >> 4));
}
#endif
