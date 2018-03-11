#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>

#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/param.h>
/* #include <sys/vmmeter.h> */
#include <sys/sensors.h>
/* #include <sys/swap.h> */

#include <unistd.h>
#include <sys/disk.h>

/* #include <err.h> */
/* #include <errno.h> */
/* #include <fcntl.h> */
/* #include <ifaddrs.h> */
/* #include <limits.h> */
/* #include <time.h> */
/* #include <unistd.h> */
/* #include <sys/types.h> */
/* #include <sys/ioctl.h> */
/* #include <sys/param.h> */
/* #include <sys/audioio.h> */
/* #include <sys/sched.h> */
/* #include <sys/resource.h> */
/* #include <sys/sensors.h> */
/* #include <sys/socket.h> */
/* #include <sys/sysctl.h> */
/* #include <sys/statvfs.h> */
/* #include <sys/utsname.h> */
/* #include <net/if.h> */
/* #include <machine/apmvar.h> */

// swap    ftp.stu.edu.tw/BSD/OpenBSD/src/usr.bin/systat/vmstat.c 
//  struct uvmexp 


#define KB 1024
#define MB 1048576     /* 1024 * 1024     */
#define GB 1073741824  /* MB * 1024       */
#define Mb 131072      /* 1024 * 1024 / 8 */
#define BYTES_TO_MB(x) (x/2/1024) /* block bytes */

#define FMT_UINT "%"PRIuMAX
#define FMT_UINTX "%"PRIxMAX
#define UFINT "%"PRIuFAST16
#define FUNC_FAILED(x) \
	printf("%s\n", x); \
	return EXIT_FAILURE;
#define VLA 200
#define exit_with_err(x) FUNC_FAILED(x)
/*
  if (0 != sysctl(mib, 2, &cpu_active, &len, NULL, 0)) {
    exit(EXIT_FAILURE);
  }
*/

// ftp.stu.edu.tw/BSD/OpenBSD/src/usr.bin/top/machine.c

// voltage


/* void get_sensor(int sens_type, uint8_t sens_num); */
/* int main(void) { */
/*   /1* get_sensor(SENSOR_TEMP, 0); *1/ */
/*   /1* get_sensor(SENSOR_FANRPM, 0); *1/ */
/*   get_sensor(SENSOR_VOLTS_DC, 0); */
/*   get_sensor(SENSOR_VOLTS_AC, 0); */
/*   return EXIT_SUCCESS; */
/* } */


/* void get_sensor(int sens_type, uint8_t sens_num) { */
/*   struct sensordev dev; */
/*   struct sensor sens; */
/*   int mib[] = { CTL_HW, HW_SENSORS, 0, sens_type, 0 }; */
/*   char buffer[VLA]; */
/*   char *all = buffer; */
/*   uint8_t x = 0; */
/*   uintmax_t temp = 0; */

/*   memset(&dev, 0, sizeof(struct sensordev)); */
/*   memset(&sens, 0, sizeof(struct sensor)); */

/*   size_t dev_len = sizeof(dev), sens_len = sizeof(sens); */
/*   if (0 != (sysctl(mib, 3, &dev, &dev_len, NULL, 0))) { */
/*     return; */
/*   } */

/*   for (mib[4] = 0; mib[4] < dev.maxnumt[sens_type]; mib[4]++) { */
/*     if (0 != (sysctl(mib, 5, &sens, &sens_len, NULL, 0))) { */
/*       break; */
/*     } */
/*     if (0 != sens_len && */
/*         !(sens.flags & (SENSOR_FINVALID | SENSOR_FUNKNOWN))) { */
/*       switch(sens_type) { */
/*         case SENSOR_VOLTS_AC: */
/*           printf("%d\n", (int)sens.value); */
/*           break; */
/*         case SENSOR_VOLTS_DC: */
/*           { */
/*         all += snprintf(all, 300, "%.2f ", */
/*             (float)((float)sens.value / 1000000.0)); */
/*           } */
/*           break; */

/*         case SENSOR_TEMP: */
/*           { */
/*             if (x == sens_num) { */
/*               temp = (uintmax_t)sens.value; */
/*             } */
/*             x++; */
/*           } */
/*           break; */

/*         case SENSOR_FANRPM: */
/*           all += snprintf(all, 300, "%d ", (int)sens.value); */
/*           break; */

/*       } */
/*     } */
/*   } */
/*   /1* printf("%s\n", buffer); *1/ */
/*   /1*   if (999999999 < temp) { /2* > 99C *2/ *1/ */
/*   /1*     printf(FMT_UINT"\n", temp / 100000000); *1/ */
/*   /1*   } else { *1/ */
/*   /1*     printf(FMT_UINT"\n", ((99999999 < temp) ? *1/ */
/*   /1*       temp / 10000000 : temp / 1000000)); /2* > 9C || < 9C *2/ *1/ */
/*   /1*   } *1/ */
/* } */


// vendor

/* void get_mobo(char *str1); */
/* int main(void) { */
/*   char vendor[200]; */

/*   get_mobo(vendor); */

/*   return EXIT_SUCCESS; */
/* } */

/* void get_mobo(char *str1) { */

/*   int mib[] = { CTL_HW, HW_VENDOR }; */
/*   int mib2[] = { CTL_HW, HW_PRODUCT }; */
/*   char vendor[100], model[100]; */
/*   char *ptr = vendor, *ptr2 = model; */
/*   size_t len = sizeof(vendor); */

/*   if (0 != (sysctl(mib, 2, &vendor, &len, NULL, 0))) { */
/*     return -1; */
/*   } */

/*   if (0 != (sysctl(mib2, 2, &model, &len, NULL, 0))) { */
/*     return -1; */
/*   } */
/*   for (; *ptr; ptr++) { */
/*     if ((isspace((unsigned char) *ptr))) { */
/*       *ptr = '\0'; */
/*       break; */
/*     } */
/*   } */
/*   for (; *ptr2; ptr2++) { */
/*     if ((isspace((unsigned char) *ptr2))) { */
/*       *ptr2 = '\0'; */
/*       break; */
/*     } */
/*   } */

/*   printf("%s %s\n", vendor, model); */
/* } */


// ram
/* int main(void) { */

  /* uintmax_t memmax = (uintmax_t)sysconf(_SC_PHYS_PAGES) * (uintmax_t)sysconf(_SC_PAGESIZE); */
  /* uintmax_t pz = (uintmax_t)sysconf(_SC_PAGESIZE); */

  /* int mib[] = { CTL_HW, HW_PHYSMEM64 }; */
  /* uintmax_t to = 0; */
  /* size_t len = sizeof(to); */
  /* if (0 != (sysctl(mib, 2, &to, &len, NULL, 0))) { */
  /*   return -1; */
  /* } */

  /* printf(FMT_UINT" "FMT_UINT"\n", to, pz); */
  /* printf(FMT_UINT" \n", pz); */


  /* struct vmtotal tot; */
  /* int mib[] = { CTL_VM, VM_METER }; */
  /* memset(&tot, 0, sizeof(struct vmtotal)); */
  /* size_t len = sizeof(tot); */
  /* /1* size_t len; *1/ */

  /* if (0 != (sysctl(mib, 2, &tot, &len, NULL, 0))) { */
  /*   return -1; */
  /* } */
  /* printf(FMT_UINT"\n", (tot.t_free*pz)/MB); */
  /* printf("%u\n", ((unsigned int)vmtotal.t_rm * pz) / MB); */
  /* printf("%d\n", (int)vmtotal.t_rm); */
  /* printf("%d\n", sysconf(_SC_PAGESIZE)); */

  /* struct vmtotal to; */
  /* int num = 1; */
  /* int mib[] = { CTL_VM, VM_METER }; */
  /* uintmax_t total = 0, freeram = 0, pz = 0; */
  /* to.t_ [free,rm,arm,avm] */

  /* memset(&to, 0, sizeof(struct vmtotal)); */
  /* size_t len = sizeof(to); */
  /* if (0 != sysctl(mib, 2, &to, &len, NULL, 0)) */
  /*   return -1; */

  /* pz      = (uintmax_t)sysconf(_SC_PAGESIZE); */
  /* total   = ((uintmax_t)sysconf(_SC_PHYS_PAGES) * pz) / MB; */
  /* freeram = ((uintmax_t)sysconf(_SC_AVPHYS_PAGES) *pz ) / MB; */
  /* freeram = ((uintmax_t)to.t_free * pz) / MB; */
  /* used    = ((uintmax_t)to.t_rm * pz - (uintmax_t)to.t_free * pz) / MB; */
  /* used = total - freeram; */

  /* printf(FMT_UINT"\n",((uintmax_t)to.t_avm*pz)/MB); */
  /* printf(FMT_UINT"\n", used); */
  /* switch(5) { */
  /*   case 1: */
  /*     /1* FILL_ARR(str1, FMT_UINT "%s", total, "MB"); *1/ */
  /*     printf(FMT_UINT"\n", total); */
  /*     break; */
  /*   case 2: */
  /*     printf(FMT_UINT"\n", freeram); */
  /*     /1* FILL_ARR(str1, FMT_UINT "%s", freeram, "MB"); *1/ */
  /*     break; */
  /*   case 5: */
  /*     printf(FMT_UINT"\n", ((total - freeram) * 100) / total); */
  /*     break; */
  /* } */

  /* return 0; */
/* } */


// cpu
/* void get_cpu(void); */
/* void get_cores_load(void); */
/* int main(void) { */

/* get_cores_load(); */
/* sleep(1); */
/* get_cores_load(); */
/* return EXIT_SUCCESS; */
/* } */

// overall load
/* void get_cpu(void) { */

/*   int mib[] = { CTL_KERN, KERN_CPTIME }; */
/*   static uintmax_t previous_total = 0, previous_idle = 0; */
/*   uintmax_t x, percent, diff_total, diff_idle, cpu_active[5]; */
/*   uintmax_t total = 0; */
/*   size_t len = sizeof(cpu_active); */

/*   memset(cpu_active, 0, sizeof(cpu_active)); */

/*   /1* GETSYSCTL("kern.cp_time", &cpu_active); *1/ */
/*   if (0 != (sysctl(mib, 2, &cpu_active, &len, NULL, 0))) { */
/*     return; */
/*   } */

/*   /1* printf(FMT_UINT"\n", (sizeof(cpu_active)/sizeof(cpu_active[0]))); *1/ */

/*   for (x = 0; x < 5; x++) */
/*     total += cpu_active[x]; */

/*   diff_total     = total - previous_total; */
/*   diff_idle      = cpu_active[4] - previous_idle; */

/*   previous_total = total; */
/*   previous_idle  = cpu_active[4]; */

/*   percent        = 100 * (diff_total - diff_idle) / diff_total; */

/*   printf(FMT_UINT"\n", percent); */
/* } */

// per core load
/* #define MAX_CORES 40 */
/* void */
/* get_cores_load(void) { */
/*   static uintmax_t previous_total[MAX_CORES], previous_idle[MAX_CORES]; */
/*   static uintmax_t test_flag = 0; */
/*   uintmax_t x = 0, z = 0; */
/*   uintmax_t percent[MAX_CORES], diff_total[MAX_CORES], core_active[MAX_CORES][5]; */
/*   uintmax_t diff_idle[MAX_CORES], total[MAX_CORES]; */
/*   int mib[] = { CTL_KERN, KERN_CPTIME2,0 }; */
/*   int mib2[] = { CTL_HW, HW_NCPU }; */
/*   unsigned int ncpu = 0; */

/*   memset(percent, 0, sizeof(percent)); */
/*   memset(diff_total, 0, sizeof(diff_total)); */
/*   memset(diff_idle, 0, sizeof(diff_idle)); */
/*   memset(total, 0, sizeof(total)); */
/*   memset(core_active, 0, sizeof(core_active)); */

/*   if (0 == test_flag) { */
/*     memset(previous_idle, 0, sizeof(previous_idle)); */
/*     memset(previous_total, 0, sizeof(previous_total)); */
/*   } */

/*   size_t len = sizeof(core_active), len2 = sizeof(ncpu); */


/*   if (0 != (sysctl(mib2, 2, &ncpu, &len2, NULL, 0))) { */
/*     return; */
/*   } */
/*   for (x = 0; x < ncpu; x++) { */
/*     if (0 != (sysctl(mib, 3, &core_active[x], &len, NULL, 0))) { */
/*       break; */
/*     } */
/*   } */

/*   for (x = 0; x < MAX_CORES; x++) { */
/*     if (0 == core_active[x][0] && 0 == */
/*       core_active[x][1] && 0 == */
/*       core_active[x][2]) { */
/* 	    break; */
/*     } */

/*     for (z = 0; z < 5; z++) */
/*       total[x] += core_active[x][z]; */

/*     diff_total[x]     = total[x] - previous_total[x]; */
/*     diff_idle[x]      = core_active[x][4] - previous_idle[x]; */

/*     previous_total[x] = total[x]; */
/*     previous_idle[x]  = core_active[x][4]; */

/*     percent[x] = 0; */
/*     if (0 != diff_total[x]) { */
/*       percent[x]        = 100 * (diff_total[x] - diff_idle[x]) */ 
/* 					/ diff_total[x]; */
/*     } */

/*     printf(FMT_UINT"%%\n", percent[x]); */
/*   } */

/*   test_flag = 1; */

/* } */

/* int main(void) { */

/* double v[3]; */
/* getloadavg(v, 3); */
/* printf("%.2f %.2f %.2f\n", */
/* (float)v[0], (float)v[1], (float)v[2]); */

/* return EXIT_SUCCESS; */
/* } */


/* int main(void) { */
/* 	int mib[] = { CTL_HW, HW_DISKSTATS, sizeof(struct diskstats) }; */
/* 	int diskn, x; */
/* 	size_t len = 0, dkn_size =0; */
/* 	const char *dev = "sd0"; */
/* 	/1* char t[100]; *1/ */
/* 	(void)dkn_size; */
	
/* 	struct diskstats *ds; */
/* 	printf("%d\n", 1); */

/* 	if (sysctl(mib, 2, NULL, &len, NULL, 0) < 0) */
/* 		return (-1); */

/* 	printf("%d\n", 2); */
/*   diskn = len / sizeof(*ds); */
/*   if (0 == diskn) { */
/*     return -1; */
/*   } */
/* 	printf("%d %d\n", 3, diskn); */

/* 	ds = (struct diskstats *)malloc(diskn * sizeof(char *)); */
/* 	if (ds == NULL) */
/* 		return (-1); */

/* 	printf("%d\n", 4); */
/* 	/1* mib[0] = CTL_HW; *1/ */
/* 	/1* mib[1] = HW_DISKNAMES; *1/ */
/* 	/1* if (sysctl(mib, 2, NULL, &dkn_size, NULL, 0) < 0) { *1/ */
/* 	/1* 	free(ds); *1/ */
/* 	/1* 	return (-1); *1/ */
/* 	/1* } *1/ */

/* 	printf("%d\n", 5); */
/* 	/1* t = malloc(dkn_size); *1/ */
/* 	/1* if (NULL == t) { *1/ */
/* 	/1*   free(ds); *1/ */
/* 	/1*   return -1; *1/ */
/*   /1* } *1/ */
/* 	/1* if (sysctl(mib, 2, t, &dkn_size, NULL, 0) < 0) { *1/ */
/* 	/1*   /2* free(t); *2/ *1/ */
/* 	/1* 	free(ds); *1/ */
/* 	/1* 	return (-1); *1/ */
/* 	/1* } *1/ */

/* 	printf("%d\n", 6); */
/*   mib[0] = CTL_HW; */
/*   mib[1] = HW_DISKSTATS; */
/* 	if (sysctl(mib, 2, ds, &len, NULL, 0) < 0) { */
/* 	  /1* free(t); *1/ */
/* 		free(ds); */
/* 		return (-1); */
/* 	} */

/* 	printf("%d\n", 7); */
/* 	for (x = 0; x < diskn; x++) { */
/* 	  printf("%s\n", ds[x].ds_name); */
/* 		if (!strcmp(ds[x].ds_name, dev)) */
/*     { */
/*       /1* printf("%s\n", t); *1/ */
/* 			break; */
/*     } */
/*   } */

/* 	printf("%d\n", 8); */
/* 	printf("%d %d\n", (int)ds[x].ds_rbytes, */
/* 	  (int)ds[x].ds_wbytes); */
/* 	  /1* (int)ds[x].ds_rxfer, *1/ */
/* 	  /1* (int)ds[x].ds_wxfer); *1/ */

/*   /1* free(t); *1/ */

/* error: */
/*   if (NULL != ds) { */
/*     free(ds); */
/*   } */

/* 	return (0); */
/* } */




int main(void) {
	struct diskstats *ds = NULL;
	int mib[] = { CTL_HW, HW_DISKSTATS, sizeof(struct diskstats) };
	uint_least16_t diskn = 0, x = 0;
	size_t len = 0;
	const char *dev = "sd0";

	if (sysctl(mib, 2, NULL, &len, NULL, 0) < 0) {
		return (-1);
  }
  if (0 == (diskn = (uint_least16_t)(len / sizeof(*ds)))) {
      return -1;
  }

	ds = (struct diskstats *)malloc(diskn * sizeof(char *));
	if (ds == NULL) {
		return (-1);
  }
	if (sysctl(mib, 2, ds, &len, NULL, 0) < 0) {
	  goto error;
	}

	for (x = 0; x < diskn; x++) {
		if (!strcmp(ds[x].ds_name, dev))
			break;
  }

	printf("%d %d\n", (int)ds[x].ds_rbytes / (1024*1024),
	  (int)ds[x].ds_wbytes / (1024*1024));

error:
  if (NULL != ds) {
    free(ds);
  }

	return (0);
}
