/*
   Copyright 08/16/2016
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

/* The pragma directives are here
 * to mute the gcc twisted vision,
 * and clangs inabillity to distinguish
 * C from C++
 *
 * https://llvm.org/bugs/show_bug.cgi?id=21689 
 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=66425
 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=25509
 *
 * Do not add any -Wno flags just to mute the compilers snafus
 * */

#include "config.h" /* Auto-generated */

#if defined (HAVE_X11_XLIB_H)
#include <X11/Xlib.h>
#endif

#include "include/headers.h"

#include <sys/statvfs.h>
#include <sys/utsname.h>
#include <sys/stat.h>
#include <sys/time.h>

#include "include/freebzd.h"

void 
get_ram(char *str1, unsigned char num) {
  u_int total = 0, freeram = 0, inactive = 0;
  u_int cache = 0, bufferram = 0, pz = 0, dummy = 0;
  uintmax_t utotal = 0, used = 0;
  size_t len = sizeof(dummy);

  SYSCTLVAL("vm.stats.vm.v_page_size", &pz);
  SYSCTLVAL("vm.stats.vm.v_page_count", &total);
  SYSCTLVAL("vm.stats.vm.v_inactive_count", &inactive);
  SYSCTLVAL("vm.stats.vm.v_free_count", &freeram);
  SYSCTLVAL("vm.stats.vm.v_cache_count", &cache);
  SYSCTLVAL("vfs.bufspace", &bufferram);

  used = ((uintmax_t)total * pz - (uintmax_t)freeram * pz
          - (uintmax_t)inactive * pz
          - (uintmax_t)cache * pz - (uintmax_t)bufferram) / MB;
  utotal = ((uintmax_t)total * pz) / MB;

  switch(num) {
    case 1:
      FILL_ARR(str1, FMT_UINT "%s", utotal, "MB");
      break;
    case 2:
      FILL_ARR(str1, FMT_UINT "%s",
        ((uintmax_t)freeram * pz) / MB, "MB");
      break;
    case 3:
      FILL_ARR(str1, FMT_UINT "%s",
        ((uintmax_t)inactive * pz) / MB, "MB");
      break;
    case 4:
      FILL_ARR(str1, FMT_UINT "%s",
        (uintmax_t)bufferram / MB, "MB");
      break;
    case 5:
      FILL_UINT_ARR(str1, (used * 100) / utotal);
      break;
  }

}


void 
get_ssd(char *str1, unsigned char num) {
  uintmax_t val = 0;
  struct statvfs ssd;

  if (-1 == (statvfs(getenv("HOME"), &ssd))) {
    FUNC_FAILED("statvfs()");
  }

  switch(num) {
    case 1:
      FILL_ARR(str1, FMT_UINT "%s",
        (uintmax_t)(ssd.f_blocks * ssd.f_bsize) / GB, "GB");
      break;
    case 2:
      FILL_ARR(str1, FMT_UINT "%s",
        (uintmax_t)(ssd.f_bfree * ssd.f_bsize) / GB, "GB");
      break;
    case 3:
      FILL_ARR(str1, FMT_UINT "%s",
        (uintmax_t)(ssd.f_bavail * ssd.f_bsize) / GB, "GB");
      break;
    case 4:
      {
        val = (uintmax_t)((
          ssd.f_blocks - ssd.f_bfree) * ssd.f_bsize) / GB;
        FILL_UINT_ARR(str1, val);
      }
      break;
  }

}


void 
get_packs(char *str1) {
  uint_fast16_t packages = 0;
  FILE *pkgs_file = popen("pkg info | wc -l", "r");

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-result"
  fscanf(pkgs_file, "%"SCNuFAST16, &packages);
#pragma GCC diagnostic pop

  pclose(pkgs_file);

  FILL_ARR(str1, "%"PRIuFAST16, packages);
}


void 
get_kernel(char *str1, unsigned char num) {
  struct utsname KerneL;
  if (-1 == (uname(&KerneL))) {
    FUNC_FAILED("uname()");
  }

  switch(num) {
    case 1:
      FILL_STR_ARR(1, str1, KerneL.sysname);
      break;
    case 2:
      FILL_STR_ARR(1, str1, KerneL.nodename);
      break;
    case 3:
      FILL_STR_ARR(1, str1, KerneL.release);
      break;
    case 4:
      FILL_STR_ARR(1, str1, KerneL.version);
      break;
    case 5:
      FILL_STR_ARR(1, str1, KerneL.machine);
      break;
    case 6:
      FILL_STR_ARR(2, str1, KerneL.sysname, KerneL.release);
      break;
  }

}


void
get_loadavg(char *str1) {
  double up[3];
  if (-1 == getloadavg(up, 3)) {
  	FUNC_FAILED("getloadavg()");
  }
  FILL_ARR(str1, "%.2f %.2f %.2f",
    (float)up[0], (float)up[1], (float)up[2]);
}


void
get_uptime(char *str1) {

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wmissing-field-initializers"
  struct timespec tc = {0};
#pragma GCC diagnostic pop

  int mib[2] = { CTL_KERN, KERN_BOOTTIME };
  time_t t;
  uintmax_t now = 0;
  size_t len = sizeof(tc);

  if (0 != sysctl(mib, 2, &tc, &len, NULL, 0)) {
    FUNC_FAILED("sysctl()");
  }

  if (-1 == (t = time(NULL))) {
    FUNC_FAILED("time()");
  }

  now = (uintmax_t)t - (uintmax_t)tc.tv_sec;
  if ((0 != (now / 86400))) { /* days */
    FILL_ARR(str1, FMT_UINT "d " FMT_UINT "h " FMT_UINT "m",
      (now / 86400),
      ((now / 3600) % 24),
      ((now / 60) % 60));
    return;
  }
  if (59 < (now / 60)) { /* hours */
    FILL_ARR(str1, FMT_UINT "h " FMT_UINT "m",
      ((now / 3600) % 24),
      ((now / 60) % 60));
    return;
  }

  FILL_ARR(str1, FMT_UINT "m", ((now / 60) % 60));
}


/* The `strftime' man page showed potential bugs */
void 
get_taim(char *str1) {
  char time_str[VLA];
  time_t t;
  struct tm *taim;

  if (-1 == (t = time(NULL)) || 
      NULL == (taim = localtime(&t)) ||
      0 == (strftime(time_str, VLA, "%I:%M %p", taim))) {
    exit_with_err(ERR, "time() or localtime() or strftime() failed");
  }
  FILL_STR_ARR(1, str1, time_str);
}


#if defined (HAVE_X11_XLIB_H)
void 
set_status(const char *str1) {
  Display *display = XOpenDisplay(NULL);

  if (display) {
    XStoreName(display, DefaultRootWindow(display), str1);
    XSync(display, 0);
    XCloseDisplay(display);

  } else {
    exit_with_err(CANNOT_OPEN, "X server");
  }
}
#endif
