#include <stdio.h>
#include <stdlib.h>
#include <cdio/cdio.h>
#include <cdio/mmc.h>
int main(void) {
  CdIo_t *p_cdio = cdio_open(NULL, DRIVER_DEVICE);
  cdio_hwinfo_t hwinfo;
  if (NULL == p_cdio) {
    return -1;
  }
  if (mmc_get_hwinfo(p_cdio, &hwinfo)) {
    printf("%s %s\n", hwinfo.psz_vendor, hwinfo.psz_model);
  }
  if (NULL != p_cdio) {
    cdio_destroy(p_cdio);
  }
  return 0;
}

