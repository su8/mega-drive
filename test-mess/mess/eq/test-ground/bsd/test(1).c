#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

#include <sys/statvfs.h>
//#include <sys/sysinfo.h>
#include <sys/utsname.h>

//freebsd
#include <sys/stat.h>
#include <sys/sysctl.h>
#include <sys/time.h>



#include <unistd.h>


#define KB 1024
#define MB 1048576     /* 1024 * 1024     */
#define GB 1073741824  /* MB * 1024       */
#define Mb 131072      /* 1024 * 1024 / 8 */
#define BYTES_TO_MB(x) (x/2/1024) /* block bytes */

#define FMT_UINT "%"PRIuMAX
#define FMT_UINTX "%"PRIxMAX
#define UFINT "%"PRIuFAST16
#define FUNC_FAILED(x) \
	printf("%s", x); \
	return EXIT_FAILURE;
#define VLA 200
#define exit_with_err(x) FUNC_FAILED(x)

// needs libsysinfo
// -lsysinfo -L/usr/local/lib

// load
/*int main(void) {
  struct sysinfo up;
  if (-1 == (sysinfo(&up))) {
    printf("%s", "Error: sysinfo() failed");
return EXIT_FAILURE;
  }
  printf("%.2f %.2f %.2f",
    (float)up.loads[0] / 65535.0,
    (float)up.loads[1] / 65535.0,
(float)up.loads[2] / 65535.0); // 0.27 0.28 0.30

return EXIT_SUCCESS;
}*/

#define FILL_ARR(x, z, ...) (printf(z, __VA_ARGS__))
#define FILL_STR_ARR(x,z, ...) (printf((x == 1 ? "%s" : "%s%s"), __VA_ARGS__));
#define GETSYSCTL(x, y) \
if (0 != sysctlbyname(x, y, &len, NULL, 0)) { \
  exit(EXIT_FAILURE); \
}

// uptime
/*int main(void) {
	int mib[2] = { CTL_KERN, KERN_BOOTTIME };
	struct timespec boottime = {0};
	time_t now;
	size_t size = sizeof(boottime);

	if ((sysctl(mib, 2, &boottime, &size, NULL, 0) == -1)
			&& (boottime.tv_sec != 0))
		return EXIT_FAILURE;
time(&now);
printf("%ld", (now - boottime.tv_sec)); // 4304
return EXIT_SUCCESS;
}*/

// taim
/*int main(void) {

  char time_str[VLA];
  time_t t;
  struct tm *taim;

  if (-1 == (t = time(NULL)) || 
      NULL == (taim = localtime(&t)) ||
      0 == (strftime(time_str, VLA, "%I:%M %p", taim))) {
    exit_with_err("time() or localtime() or strftime() failed");
}
printf("%s\n", time_str); // 04:57 PM

return EXIT_SUCCESS;
}*/

// kernel
/*int main(void) {
  unsigned char num = 6;
  struct utsname KerneL;
  if (-1 == (uname(&KerneL))) {
    FUNC_FAILED("uname()");
  }

  switch(num) {
    case 1:
      FILL_STR_ARR(1, str1, KerneL.sysname); // FreeBSD
      break;
    case 2:
      FILL_STR_ARR(1, str1, KerneL.nodename);
      break;
    case 3:
      FILL_STR_ARR(1, str1, KerneL.release); // 10.3
      break;
    case 4:
      FILL_STR_ARR(1, str1, KerneL.version); // FreeBSD 10.3-RELEASE #0 r297264: Fri Mar 25 02:10:02 UTC 2016     root@releng1.nyi.freebsd.org:/usr/obj/usr/src/sys/GENERIC
      break;
    case 5:
      FILL_STR_ARR(1, str1, KerneL.machine); // amd64
      break;
    case 6:
      FILL_STR_ARR(2, str1, KerneL.sysname, KerneL.release); FreeBSD 10.3-RELEASE
      break;
}
return EXIT_SUCCESS;
}*/

// ssd
/*int main(void) {

  uintmax_t val = 0;
  struct statvfs ssd;
  unsigned char num = 4;

  if (-1 == (statvfs(getenv("HOME"), &ssd))) {
    FUNC_FAILED("statvfs()");
  }

  switch(num) {
    case 1:
      printf(FMT_UINT "%s\n",
        (uintmax_t)(ssd.f_blocks * ssd.f_bsize) / GB, "GB"); // 122GB
      break;
    case 2:
      printf(FMT_UINT "%s\n",
        (uintmax_t)(ssd.f_bfree * ssd.f_bsize) / GB, "GB"); // 25GB
      break;
    case 3:
      printf(FMT_UINT "%s\n",
        (uintmax_t)(ssd.f_bavail * ssd.f_bsize) / GB, "GB"); // 23GB
      break;
    case 4:
      {
        val = (uintmax_t)((
          ssd.f_blocks - ssd.f_bfree) * ssd.f_bsize) / GB; // 96
        printf(FMT_UINT"\n", val);
      }
      break;
}

return EXIT_SUCCESS;
}*/

// ram
/*int main(void){


  //sysconf(_SC_PAGE_SIZE) // 4096
// sysctl -n vm.stats.vm.v_page_size // 4096
// sysctl -n hw.physmem // 8294191104
// sysctl -n vm.stats.vm.v_inactive_count // 659051
// 659051*4096 = 2699472896 / MB = 2574
// sysctl -n vm.stats.vm.v_cache_count // 210
// sysctl -n vm.stats.vm.v_free_count // 983917
// 983917 * 4096 = 4030124032 / MB = 3843

/1* 
SYSTEM MEMORY INFORMATION:
mem_wire:        1070764032 (   1021MB) [ 13%] Wired: disabled for paging out
mem_active:  +    253775872 (    242MB) [  3%] Active: recently referenced
mem_inactive:+   2697711616 (   2572MB) [ 33%] Inactive: recently not referenced
mem_cache:   +       860160 (      0MB) [  0%] Cached: almost avail. for allocation
mem_free:    +   4038414336 (   3851MB) [ 50%] Free: fully available for allocation
mem_gap_vm:  +        16384 (      0MB) [  0%] Memory gap: UNKNOWN
-------------- ------------ ----------- ------
mem_all:     =   8061542400 (   7688MB) [100%] Total real memory managed
mem_gap_sys: +    232648704 (    221MB)        Memory gap: Kernel?!
-------------- ------------ -----------
mem_phys:    =   8294191104 (   7909MB)        Total real memory available
mem_gap_hw:  +    295743488 (    282MB)        Memory gap: Segment Mappings?!
-------------- ------------ -----------
mem_hw:      =   8589934592 (   8192MB)        Total real memory installed

SYSTEM MEMORY SUMMARY:
mem_used:        1852948480 (   1767MB) [ 21%] Logically used memory
mem_avail:   +   6736986112 (   6424MB) [ 78%] Logically available memory
-------------- ------------ ----------- ------
mem_total:   =   8589934592 (   8192MB) [100%] Logically total memory


*1/

  u_int total = 0, freeram = 0, inactive = 0;
  u_int cache = 0, bufferram = 0, pz = 0, dummy = 0;
  uintmax_t utotal = 0, used = 0;
size_t len = sizeof(dummy);

unsigned char num = 1;
GETSYSCTL("vm.stats.vm.v_page_size", &pz);
GETSYSCTL("vm.stats.vm.v_page_count", &total);
GETSYSCTL("vm.stats.vm.v_inactive_count", &inactive);
GETSYSCTL("vm.stats.vm.v_free_count", &freeram);
GETSYSCTL("vm.stats.vm.v_cache_count", &cache);
GETSYSCTL("vfs.bufspace", &bufferram);

  used = ((uintmax_t)total * pz - (uintmax_t)freeram * pz
          - (uintmax_t)inactive * pz
          - (uintmax_t)cache * pz - (uintmax_t)bufferram) / MB;
  utotal = ((uintmax_t)total * pz) / MB;


  switch(num) {
    case 1:
      FILL_ARR(str1, FMT_UINT "%s\n", utotal, "MB");
      break;
    case 2:
      FILL_ARR(str1, FMT_UINT "%s\n",
        ((uintmax_t)freeram * pz) / MB, "MB");
      break;
    case 3:
      FILL_ARR(str1, FMT_UINT "%s\n",
        ((uintmax_t)inactive * pz) / MB, "MB");
      break;
    case 4:
      FILL_ARR(str1, FMT_UINT "%s\n",
        (uintmax_t)bufferram / MB, "MB");
      break;
    case 5:
      printf(FMT_UINT"\n", ((uintmax_t)used * 100) / utotal);
      break;
  }

return EXIT_SUCCESS;
}*/


// cpu
/*void get_cpu(void);
void get_cores_load(void);
int main(void) {

get_cores_load();
sleep(1);
get_cores_load();
return EXIT_SUCCESS;
}*/

// overall load
/*void get_cpu(void) {

  static uintmax_t previous_total = 0, previous_idle = 0;
  uintmax_t x, percent, diff_total, diff_idle, cpu_active[5];
  uintmax_t total = 0;
  size_t len = sizeof(cpu_active);

  memset(cpu_active, 0, sizeof(cpu_active));

  GETSYSCTL("kern.cp_time", &cpu_active);

  printf(FMT_UINT"\n", (sizeof(cpu_active)/sizeof(cpu_active[0])));

  for (x = 0; x < 5; x++)
    total += cpu_active[x];

  diff_total     = total - previous_total;
  diff_idle      = cpu_active[4] - previous_idle;

  previous_total = total;
  previous_idle  = cpu_active[4];

  percent        = 100 * (diff_total - diff_idle) / diff_total;

  printf(FMT_UINT"\n", percent);
}*/

// per core load
/*#define MAX_CORES 40
void
get_cores_load(void) {
  static uintmax_t previous_total[MAX_CORES], previous_idle[MAX_CORES];
  static uintmax_t test_flag = 0;
  uintmax_t x = 0, z = 0;
  uintmax_t percent[MAX_CORES], diff_total[MAX_CORES], core_active[MAX_CORES][5];
  uintmax_t diff_idle[MAX_CORES], total[MAX_CORES];
  //char buf[VLA], temp[VLA];
  //char *all = temp;
  size_t len = sizeof(core_active);

  memset(percent, 0, sizeof(percent));
  memset(diff_total, 0, sizeof(diff_total));
  memset(diff_idle, 0, sizeof(diff_idle));
  memset(total, 0, sizeof(total));
  memset(core_active, 0, sizeof(core_active));

  if (0 == test_flag) {
    memset(previous_idle, 0, sizeof(previous_idle));
    memset(previous_total, 0, sizeof(previous_total));
  }

  GETSYSCTL("kern.cp_times", &core_active);

  for (x = 0; x < MAX_CORES; x++) {
    if (0 == core_active[x][0] && 0 ==
      core_active[x][1] && 0 ==
      core_active[x][2]) {
	    break;
    }

    for (z = 0; z < 5; z++)
      total[x] += core_active[x][z];

    diff_total[x]     = total[x] - previous_total[x];
    diff_idle[x]      = core_active[x][4] - previous_idle[x];

    previous_total[x] = total[x];
    previous_idle[x]  = core_active[x][4];

    percent[x]        = 100 * (diff_total[x] - diff_idle[x]) 
					/ diff_total[x];

    printf(FMT_UINT"%%\n", percent[x]);
  }

  test_flag = 1;

  //FILL_STR_ARR(1, str1, temp);
}*/

// load
/*
int main(void) {

double v[3];
getloadavg(v, 3);
printf("%.2f %.2f %.2f\n",
(float)v[0], (float)v[1], (float)v[2]);

return EXIT_SUCCESS;
}*/


// cpu temp
/*int main(void) {
  uintmax_t temp = 0;
  size_t len = sizeof(temp);

  GETSYSCTL("dev.cpu.0.temperature", &temp);

  if (9999 < temp) { // > 99C
	printf(FMT_UINT"\n", temp/1000);
  } else {
    printf(FMT_UINT"\n", ((999 < temp) ?
      temp/100 : temp/10)); // < 9C || > 9C
  }

  return EXIT_SUCCESS;
}*/




/* 

/1*
 *  First stab at support for metrics in FreeBSD 
 *  by Preston Smith <psmith@physics.purdue.edu>
 *  Wed Feb 27 14:55:33 EST 2002
 *
 *1/

#include <kvm.h>
#include <fcntl.h>
#include <sys/param.h> 
#include <sys/sysctl.h>
#include <sys/user.h>
#include <sys/dkstat.h>
#include <unistd.h>
#include "ganglia.h"
#include "metric_typedefs.h"

/1* Function prototypes *1/
long percentages(int cnt, int *out, register long *new,
                          register long *old, long *diffs);
 
/1*
 * This function is called only once by the gmond.  Use to 
 * initialize data structures, etc or just return SYNAPSE_SUCCESS;
 *1/
g_val_t
metric_init(void)
{
   g_val_t val;
   val.int32 = SYNAPSE_SUCCESS;
   return val;
}

g_val_t
cpu_num_func ( void )
{
   g_val_t val;
   int ncpu;
   size_t len = sizeof (int);
   if (sysctlbyname("hw.ncpu", &ncpu, &len, NULL, 0) == -1 || !len)
        ncpu = 1;

   val.uint16 = ncpu;
   return val;
}

g_val_t
cpu_speed_func ( void )
{
   g_val_t val;
   int cpu_speed;
   size_t len = sizeof(cpu_speed);
   if (sysctlbyname("machdep.tsc_freq", &cpu_speed, &len, NULL, 0) == -1)
     val.uint16 = 0;

   /1* machdep.tsc_freq doesn't seem to always be present. At least on
      my FreeBSD 4 systems. The experts say it gives cpu speed, tho. *1/
   val.uint16 = cpu_speed /= 1000000;
   return val;
}

g_val_t
mem_total_func ( void )
{
   g_val_t val;
   size_t len;
   int total;
   int mib[2];

   mib[0] = CTL_HW;
   mib[1] = HW_PHYSMEM;
   len = sizeof (total);

   sysctl(mib, 2, &total, &len, NULL, 0);
   total /= 1024;
   val.uint32 = total;
   return val;
}

g_val_t
swap_total_func ( void )
{
   g_val_t val;

   struct kvm_swap swap[1];
   kvm_t *kd;
   int totswap, n;

   kd = kvm_open(NULL, NULL, NULL, O_RDONLY, "kvm_open"); 
   n = kvm_getswapinfo(kd, swap, 1, 0);
   if (n < 0 || swap[0].ksw_total == 0) { 
       val.uint32 = 0;
   }
   totswap = swap[0].ksw_total;
   totswap *= getpagesize() / 1024;
   val.uint32 = totswap;
   kvm_close(kd);

   return val;
}

g_val_t
boottime_func ( void )
{
   g_val_t val;
   struct timeval  boottime;
   int mib[2];
   size_t size;

   mib[0] = CTL_KERN;
   mib[1] = KERN_BOOTTIME;
   size = sizeof(boottime);
   if (sysctl(mib, 2, &boottime, &size, NULL, 0) == -1)
       val.uint32 = 0;

   val.uint32 = boottime.tv_sec;

   return val;
}

g_val_t
sys_clock_func ( void )
{
   g_val_t val;

   val.uint32 = time(NULL);
   return val;
}

g_val_t
machine_type_func ( void )
{
   g_val_t val;
   char machine_type[MAX_G_STRING_SIZE];
   size_t len = MAX_G_STRING_SIZE;
   if (sysctlbyname("hw.machine", &machine_type, &len, NULL, 0) == -1 || !len)
        strncpy( val.str, "x86", MAX_G_STRING_SIZE );

   strncpy( val.str, machine_type, MAX_G_STRING_SIZE );
   return val;
}

g_val_t
os_name_func ( void )
{
   g_val_t val;
   char osname[MAX_G_STRING_SIZE];
   size_t len = MAX_G_STRING_SIZE;
   if (sysctlbyname("kern.ostype", &osname, &len, NULL, 0) == -1 || !len)
        strncpy( val.str, "FreeBSD", MAX_G_STRING_SIZE );

   strncpy( val.str, osname, MAX_G_STRING_SIZE );
 
   return val;
}        

g_val_t
os_release_func ( void )
{
   g_val_t val;
   int mib[2];
   size_t len;
   char *prefix, buf[1024];

   prefix = "";

   mib[0] = CTL_KERN;
   mib[1] = KERN_OSRELEASE;
   len = sizeof(buf);
   if (sysctl(mib, 2, &buf, &len, NULL, 0) == -1)
        strncpy( val.str, "Unknown", MAX_G_STRING_SIZE );

   strncpy( val.str, buf, MAX_G_STRING_SIZE );

   return val;
}        

/1* Get the CPU state given by index, from kern.cp_time
 * Use the constants in <sys/dkstat.h>
 * CP_USER=0, CP_NICE=1, CP_SYS=2, CP_INTR=3, CP_IDLE=4
 *1/
int cpu_state(int which) {

   static long cp_time[CPUSTATES];
   static long cp_old[CPUSTATES];
   static long cp_diff[CPUSTATES];
   static int cpu_states[CPUSTATES];
   static long tot;
   size_t len = sizeof(cp_time);

   /1* Copy the last cp_time into cp_old *1/
   memcpy(&cp_old, &cp_time, CPUSTATES*sizeof(long));
   /1* puts kern.cp_time array into cp_time *1/
   if (sysctlbyname("kern.cp_time", &cp_time, &len, NULL, 0) == -1 || !len)
      return 0.0;
   /1* Use percentages function lifted from top(1) to figure percentages *1/
   tot = percentages(CPUSTATES, cpu_states, cp_time, cp_old, cp_diff);

   return cpu_states[which];
}

g_val_t
cpu_user_func ( void )
{
   g_val_t val;
   int res;

   res = cpu_state(CP_USER); 
   val.f = (float)res/10;
   return val;
}

g_val_t
cpu_nice_func ( void )
{
   g_val_t val;
   int res;

   res = cpu_state(CP_NICE); 
   val.f = (float)res/10;

   return val;
}

g_val_t 
cpu_system_func ( void )
{
   g_val_t val;
   int res;

   res = cpu_state(CP_SYS); 
   val.f = (float)res/10;

   return val;
}

g_val_t 
cpu_idle_func ( void )
{
   g_val_t val;
   int res;

   res = cpu_state(CP_IDLE); 
   val.f = (float)res/10;

   return val;
}

g_val_t 
cpu_aidle_func ( void )
{
   g_val_t val;
   
   val.f = 0.0;
   return val;
}

g_val_t
load_one_func ( void )
{
   g_val_t val;
   double load[3];

   getloadavg(load, 3);
   val.f = load[0];
   return val;
}

g_val_t
load_five_func ( void )
{
   g_val_t val;
   double load[3];

   getloadavg(load, 3);
 
   val.f = load[1];
   return val;
}

g_val_t
load_fifteen_func ( void )
{
   g_val_t val;
   double load[3];

   getloadavg(load, 3);
   val.f = load[2];
   return val;
}

g_val_t
proc_total_func ( void )
{
   g_val_t val;
   int mib[3];
   size_t len;

   mib[0] = CTL_KERN;
   mib[1] = KERN_PROC;
   mib[2] = KERN_PROC_ALL;

   sysctl(mib, 3, NULL, &len, NULL, 0);

   val.uint32 = (len / sizeof (struct kinfo_proc)); 

   return val;
}


/1* 
 * Don't know how to do this yet..
 *1/
g_val_t
proc_run_func( void )
{
   g_val_t val;

   val.uint32 = 0;
   return val;
}

g_val_t
mem_free_func ( void )
{
   g_val_t val;
   size_t len; 
   int free_pages;

   len = sizeof (free_pages);
   if((sysctlbyname("vm.stats.vm.v_free_count", &free_pages, &len, NULL, 0) 
	== -1) || !len) free_pages = 0; 
   free_pages *= getpagesize() / 1024;

   val.uint32 = free_pages;
   return val;
}

g_val_t
mem_shared_func ( void )
{
   g_val_t val;

   val.uint32 = 0;
   return val;
}

g_val_t
mem_buffers_func ( void )
{
   g_val_t val;
   size_t len;
   int buffers;

   len = sizeof (buffers);
   if((sysctlbyname("vfs.bufspace", &buffers, &len, NULL, 0) == -1) || !len)
		buffers = 0; 
   buffers /= 1024;

   val.uint32 = buffers;
   return val;
}

g_val_t
mem_cached_func ( void )
{
   g_val_t val;
   size_t len;
   int cache;

   len = sizeof (cache);
   if((sysctlbyname("vm.stats.vm.v_cache_count", &cache, &len, NULL, 0) == -1) 
	|| !len)
      cache = 0; 

   cache *= getpagesize() / 1024;

   val.uint32 = cache;
   return val;
}

g_val_t
swap_free_func ( void )
{
   g_val_t val;
   struct kvm_swap swap[1];
   kvm_t *kd;
   int totswap, usedswap, freeswap, n;

   kd = kvm_open(NULL, NULL, NULL, O_RDONLY, "kvm_open");
   n = kvm_getswapinfo(kd, swap, 1, 0);
   if (n < 0 || swap[0].ksw_total == 0) {
       val.uint32 = 0;
   }
   totswap = swap[0].ksw_total;
   usedswap = swap[0].ksw_used;
   kvm_close(kd);

   freeswap = totswap-usedswap;
   freeswap *= getpagesize() / 1024;

   val.uint32 = freeswap;
   return val;
}

#include "dnet.h"

static int
find_mtu(const struct intf_entry *entry, void *arg)
{ 
   unsigned int mtu;
   unsigned int *min = (unsigned int *) arg;

   /1* Only consider interfaces that are up. *1/
   if (! entry->intf_flags & INTF_FLAG_UP)
      return 0;

   mtu=entry->intf_mtu;
   if ( !*min || *min>mtu)
      *min=mtu;

   return 0;
}

g_val_t
mtu_func ( void )
{
   /1* We want to find the minimum MTU (Max packet size) over all UP interfaces.
*1/
   unsigned int min=0;
   g_val_t val;

   intf_t *intf;
   intf = intf_open();
   intf_loop(intf, find_mtu, &min);
   intf_close(intf);
   val.uint32 = min;

   /1* A val of 0 means there are no UP interfaces. Shouldn't happen. *1/
   return val;
}


/1*
 * Function to get cpu percentages.
 * Might be changed ever so slightly, but is still mostly:
 * AUTHOR:  Christos Zoulas <christos@ee.cornell.edu>
 *          Steven Wallace  <swallace@freebsd.org>
 *          Wolfram Schneider <wosch@FreeBSD.org>
 *
 * $FreeBSD: src/usr.bin/top/machine.c,v 1.29.2.2 2001/07/31 20:27:05 tmm Exp $
 *1/

long percentages(int cnt, int *out, register long *new, 
                          register long *old, long *diffs)  {

    register int i;
    register long change;
    register long total_change;
    register long *dp;
    long half_total;

    /1* initialization *1/
    total_change = 0;
    dp = diffs;

    /1* calculate changes for each state and the overall change *1/
    for (i = 0; i < cnt; i++) {
        if ((change = *new - *old) < 0) {
            /1* this only happens when the counter wraps *1/
            change = (int)
                ((unsigned long)*new-(unsigned long)*old);
        }
        total_change += (*dp++ = change);
        *old++ = *new++;
    }
    /1* avoid divide by zero potential *1/
    if (total_change == 0) { total_change = 1; }

    /1* calculate percentages based on overall change, rounding up *1/
    half_total = total_change / 2l;

    /1* Do not divide by 0. Causes Floating point exception *1/
    if(total_change) {
        for (i = 0; i < cnt; i++) {
          *out++ = (int)((*diffs++ * 1000 + half_total) / total_change);
        }
    }

    /1* return the total in case the caller wants to use it *1/
    return(total_change);
}



*/
