#include <sys/param.h>
#include <sys/types.h>
#include <sys/sysctl.h>
#include <sys/swap.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#define BYTES_TO_MB(x) (x/2/1024) /* block bytes */

/*  $OpenBSD: swap.c,v 1.27 2015/08/20 22:32:42 deraadt Exp $  */

int main(void) {
  struct swapent *dev = NULL;
  int count = 0, stats = 0, x = 0;
  int total = 0, used = 0;

  count = swapctl(SWAP_NSWAP, 0, 0);
  if (-1 == count) {
    return 0;
  }

  dev = (struct swapent *)malloc(count * sizeof(struct swapent));
  if (NULL == dev) {
    return 0;
  }

  stats = swapctl(SWAP_STATS, dev, count);
  if (-1 == stats || stats != count) {
    goto error;
  }

  for (x = 0; x < count; x++) {
    total += dev->se_nblks;
    used  += dev->se_inuse;
  }
  printf("%d %d\n", BYTES_TO_MB(total), BYTES_TO_MB(used));

  /* switch(num) { */
  /*   case 1: */
  /*     FILL_ARR(str1, FMT_UINT" %s", ((total * pz) / MB), "MB"); */
  /*     break; */
  /*   case 2: */
  /*     FILL_ARR(str1, FMT_UINT" %s", */
  /*       (((total - used) * pz) / MB), "MB"); */
  /*     break; */
  /*   case 3: */
  /*     FILL_ARR(str1, FMT_UINT" %s", ((used * pz) / MB), "MB"); */
  /*     break; */
  /*   case 4: */
  /*     { */
  /*       if (0 != total) { */
  /*         FILL_ARR(str1, FMT_UINT"%%", (used * 100) / total); */
  /*       } else { */
  /*         FILL_STR_ARR(1, str1, "0 %"); */
  /*       } */
  /*     } */
  /*     break; */
  /* } */


error:
  if (NULL != dev) {
    free(dev);
  }
  return 0;
}
