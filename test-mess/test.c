#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#ifndef TIOCGWINSZ
#include <termios.h>
#endif

int main(void) {
  /* int height = 0; */
  struct winsize w;
  
  ioctl(0, TIOCGWINSZ, &w);
  printf("%d\n", w.ws_row);

  return EXIT_SUCCESS;
}
