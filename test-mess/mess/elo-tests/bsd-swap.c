#include <sys/swap.h>

/*
 * Based on:
 *  $OpenBSD: swap.c,v 1.27 2015/08/20 22:32:42 deraadt Exp $
*/
void
get_swapp(char *str1, uint8_t num) {
  struct swapent *dev = NULL;
  int count = 0, stats = 0, x = 0;
  uintmax_t total = 0, used = 0;

  FILL_STR_ARR(1, str1, "0 MB");

  count = swapctl(SWAP_NSWAP, 0, 0);
  if (-1 == count) {
    return;
  }

  dev = (struct swapent *)malloc(
      (unsigned long)count * sizeof(struct swapent));
  if (NULL == dev) {
    return;
  }

  stats = swapctl(SWAP_STATS, dev, count);
  if (-1 == stats || stats != count) {
    goto error;
  }

  for (x = 0; x < count; x++) {
    total += (uintmax_t)dev->se_nblks;
    used  += (uintmax_t)dev->se_inuse;
  }

  switch(num) {
    case 1:
      FILL_ARR(str1, FMT_UINT" %s", BYTES_TO_MB(total), "MB");
      break;
    case 2:
      FILL_ARR(str1, FMT_UINT" %s",
        BYTES_TO_MB((total - used)), "MB");
      break;
    case 3:
      FILL_ARR(str1, FMT_UINT" %s", BYTES_TO_MB(used), "MB");
      break;
    case 4:
      {
        if (0 != total) {
          FILL_ARR(str1, FMT_UINT"%%", (used * 100) / total);
        } else {
          FILL_STR_ARR(1, str1, "0 %");
        }
      }
      break;
  }

error:
  if (NULL != dev) {
    free(dev);
  }
  return;
}
