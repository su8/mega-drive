/*
  Copyright (C) 2003, 2004, 2005, 2008, 2009, 2012
  Rocky Bernstein <rocky@gnu.org>
  
  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/* Simple program to show drivers installed and what the default
   CD-ROM drive is. See also corresponding C++ programs of similar
   names .*/
#include <stdio.h>
#include <stdlib.h>

#include <cdio/cdio.h>
#include <cdio/mmc.h>

/* rm test ; gcc -Wall -O2 -lcdio d.c -o test ; ./test

http://libcdio.sourcearchive.com/documentation/0.78.2plus-pdfsg1/lib_2driver_2device_8c-source.html#l00881
http://www.gnu.org/software/libcdio/libcdio.html


  */

/*
  CdIo_t *p_cdio = NULL;
  cdio_hwinfo_t hwinfo;
  driver_id_t driver_id = DRIVER_DEVICE;
  
  char ** device_list = cdio_get_devices_ret(&driver_id);
  char ** d = device_list;
  const char *psz_drive = "/dev/cd0";

  //if (argc > 1) psz_drive = argv[1];

    if (NULL != d) {
      for ( ; *d != NULL ; d++ ) {
        p_cdio = cdio_open (psz_drive, driver_id);
        if (mmc_get_hwinfo(p_cdio, &hwinfo)) {
          printf("%-8s: %s\n%-8s: %s\n",
                 "Vendor"  , hwinfo.psz_vendor,
                 "Model"   , hwinfo.psz_model);
        }
        if (NULL != p_cdio) {
          cdio_destroy(p_cdio);
        }
      }
    }
    cdio_free_device_list(device_list);
*/

int
main(int argc, const char *argv[])
{
  CdIo_t *p_cdio = cdio_open (NULL, DRIVER_DEVICE);
  cdio_hwinfo_t hwinfo;
  //driver_id_t *driver_id;

  if (NULL == p_cdio) {
    printf("-- Couldn't find CD\n");
    return -1;
  }
  if (mmc_get_hwinfo(p_cdio, &hwinfo)) {
          printf("%-8s: %s\n%-8s: %s\n",
                 "Vendor"  , hwinfo.psz_vendor,
                 "Model"   , hwinfo.psz_model);
  }

  if (NULL != p_cdio) {
    cdio_destroy(p_cdio);
  }


  return 0;
}
