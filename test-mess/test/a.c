#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define STREQ(x, z) (0 == (strcmp(x, z)))
#define CHECK_SSCANF(buf, x, z) \
  if (EOF == (sscanf(buf, x, z))) { \
   return -1; \
  }

/* int have_match(char *str1, char *str2); */

int main(void) {
  FILE *fp;
  char buf[100], temp[100], *ptr, *str1 = NULL;
  const char *tagz[] = { "artist", "title", "album", "date" };
  const char *idx_tagz = tagz[0];

  if (NULL == (fp = popen("cmus-remote -Q 2> /dev/null", "r"))) {
    return -1;
  }

  while (1) {
    if (NULL == (fgets(buf, 99, fp))) {
      break;
    }

      if ('s' == buf[0] && 't' == buf[1] && 'r' == buf[2]) {
        CHECK_SSCANF(buf, "%*s %[^\n]", temp);
        break;
      }
    if (6 == 7) {
      if (('f' == buf[0] && 'i' == buf[1] && 'l' == buf[2])) {
        CHECK_SSCANF(buf, "%*s %[^\n]", temp);
        if (NULL != (ptr = strrchr(temp, '/'))) {
          for (; *ptr; ptr++) {
            if ('/' != *ptr) {
              *str1++ = *ptr;
            }
          }
          *str1 = '\0';
        }
        break;
      }
    } else {
      if ('t' == buf[0] && 'a' == buf[1] && 'g' == buf[2]) {
        CHECK_SSCANF(buf, "%*s %s", temp);
        if (STREQ(idx_tagz, temp)) {
          CHECK_SSCANF(buf, "%*s %*s %[^\n]", str1);
          break;
        }
      }
    }
  }

  if (-1 == (pclose(fp))) {
    return -1;
  }

  if ('\0' != temp[0]) {
    printf("%s\n", temp);
  }

  return EXIT_SUCCESS;
}

/* int have_match(char *str1, char *str2) { */
/*   char *ptr = str1, temp[200]; */
/*   int x = 0, z = 0; */
/*   for (; *ptr; ptr++) { */
/*     if (isspace((unsigned char) *ptr)) { */
/*       if (0 != x) { */
/*         break; */
/*       } */
/*       x++; */
/*     } */
/*     temp[z++] = *ptr; */
/*   } */
/*   x = 0; */
/*   temp[z] = '\0'; */

/*   if (0 == (strcmp(str2, temp))) { */
/*     x = 1; */
/*   } */
/*   /1* printf("%s\n", temp); *1/ */

/*   return x; */
/* } */


    /* printf("%s\n", temp); */
      /* snprintf(temp, 10, "%*s %s", buf); */
      /* if (1 == have_match(buf, (char *)"tag artist")) { */
        /* printf("%s\n", buf); */
      /* } */
    /* snprintf(temp, 30, "%*s %s", buf); */
    /* printf("%s\n", " no sscanf eof"); */
    /* if (EOF == (sscanf(buf, "%*s %s", temp))) { */
    /* printf("%s\n", "sscanf eof"); */
    /*   break; */
    /* } */
    /* memset(temp, 0, sizeof(temp)); */
    /* for (ptr = buf, x = 0; *ptr; ptr++) { */
    /*   /1* if (isspace((unsigned char) *ptr)) { *1/ */
    /*   /1*   break; *1/ */
    /*   /1* } *1/ */
    /*   temp[x++] = *ptr; */
    /* } */
    /* if (0 == (strcmp(temp, "set"))) { */
    /*   /1* printf("%s\n", "FUCK YEAH2"); *1/ */
    /*   break; */
    /* } */
