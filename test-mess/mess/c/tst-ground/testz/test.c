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

#define VLA 200
#define KB 1024
#define MB 1048576     /* 1024 * 1024     */
#define GB 1073741824  /* MB * 1024       */
#define Mb 131072      /* 1024 * 1024 / 8 */
#define BYTES_TO_MB(x) (x/2/1024) /* block bytes */

#define FMT_UINT "%"PRIuMAX
#define UFINT "%"PRIuFAST16

/* stay away from va_list */
#define FILL_ARR(x, z, ...) (snprintf(x, VLA, z, __VA_ARGS__))
#define FILL_UINT_ARR(x, z) (FILL_ARR(x, FMT_UINT, z))
#define FILL_STR_ARR(x, z, ...) (FILL_ARR(z, (1 == x ? "%s" : "%s %s"), __VA_ARGS__))

/* temperature sensors */
#define HWMON_DIR "/sys/class/hwmon/hwmon0"
#define TEMPERATURE(x) (HWMON_DIR"/temp"x"_input")
#define CPU_TEMP_FILE TEMPERATURE("1")
#define MOBO_TEMP_FILE TEMPERATURE("2")

/* motherboard model and vendor */
#define MOTHERBOARD(x) ("/sys/class/dmi/id/board_"x)
#define MOBO_NAME MOTHERBOARD("name")
#define MOBO_VENDOR MOTHERBOARD("vendor")

/* voltage and fans */
#define VOLTAGE_FILE(x) (HWMON_DIR"/in"x"_input")
#define FAN_FILE HWMON_DIR"/fan"UFINT"_input"

/* exit with error */
#define CANNOT_OPEN "Could not open"
#define ERR "Error:"
#define NOT_FOUND "Not found, "
#define MAX_CORES 65
static void exit_with_err(const char *, const char *);

static void
exit_with_err(const char *str1, const char *str2) {
  printf("%s %s\n", str1, str2);
  exit(EXIT_FAILURE);
}

void get_cpu(char *);

int main (void) {
  char test[20];
  get_cpu(test);

  return EXIT_SUCCESS;
}

void get_cpu(char *str1) {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  static uintmax_t previous_total[MAX_CORES] = {0}, previous_idle[MAX_CORES] = {0};
  uintmax_t percent[MAX_CORES] = {0}, diff_total[MAX_CORES] = {0};
  uintmax_t diff_idle[MAX_CORES] = {0}, total[MAX_CORES] = {0};
#pragma GCC diagnostic pop

  uintmax_t x = 0, y = 0, z = 0;
  uintmax_t core_active[MAX_CORES][10];
  char buf[VLA], temp[VLA];
  char *all = temp;

  FILE *fp = fopen("/proc/stat", "r");
  if (NULL == fp) {
    exit_with_err(CANNOT_OPEN, "/proc/stat");
  }

  if (NULL == fgets(buf, VLA, fp)) {
    fclose(fp);
    exit_with_err("Error:","reached EOF 1");
  }

  for (x = 0; x < MAX_CORES; x++) {
    if (NULL == fgets(buf, VLA, fp)) {
      fclose(fp);
      exit_with_err("Error:","reached EOF 2");
    }

    /* if (buf[0] != 'a' && buf[1] != 'b' && buf[2] != 'c') { */
    /*   break; */
    /* } */

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
    for (y = 0; y < 10; y++) {
      total[x] += core_active[x][y];
    }

    diff_total[x]     = total[x] - previous_total[x];
    diff_idle[x]      = core_active[x][3] - previous_idle[x];

    previous_total[x] = total[x];
    previous_idle[x]  = core_active[x][3];

    percent[x]        = (uintmax_t)sysconf(_SC_CLK_TCK) *
                      (diff_total[x] - diff_idle[x]) / diff_total[x];

    all += snprintf(all, VLA, FMT_UINT"%% ", percent[x]);
  }

  /* /1* get_temp(CPU_TEMP_FILE, str2); *1/ */
  printf("%s\n", temp);
  /* FILL_UINT_ARR(str1, percent); */

}
