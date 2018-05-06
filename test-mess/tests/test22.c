/* #include <stdio.h> */
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
/* #include <string.h> */
/* #include <stdlib.h> */

char buf[200];
char *
make_message(const char *fmt, ...);
/* static const char *FMT = "%s"; */
/* #define FMT2 msg, " eq empty" */
int main(void) {
char *msg1= make_message("eq empty %s", "elo");
/* char *msg = make_message("#[fg=%s]", msg1); */
  /* printf("%s %s\n", FMT2); */
printf("%s\n", msg1);
  /* free(msg); */
  /* free(msg1); */
  return EXIT_SUCCESS;
}



char *
make_message(const char *fmt, ...)
{
   char *p = buf;
   va_list ap;

   /* Determine required size */

   va_start(ap, fmt);
   vsnprintf(p, 199, fmt, ap);
   va_end(ap);

   return p;
}
