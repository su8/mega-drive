#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <curl/curl.h>

#define CLOSE_FD2(fd, res) \
  if (-1 == (close(fd))) { \
    freeaddrinfo(res); \
    exit(-1); \
  }


static size_t read_temp_data_cb(char *, size_t size, size_t nmemb, char *);
/*
 * The data that we parse:
 * |/dev/sda|Corsair Force GT|24|C| */
static size_t
read_temp_data_cb(char *data, size_t size, size_t nmemb, char *str1) {
  char *ptr = data;
  size_t sz = size * nmemb, x = 0;
  static char a[200];
  static char *ptr2 = a;
  static int z = 0;

  for (; *ptr; ptr++, x++) {
    if ((x+2) < sz) {

      if ('|' == *ptr) {
        if (0 != (isdigit((unsigned char) *(ptr+1)))) {
          if (196 > z) {
            *ptr2++ = *(ptr+1);
            z++;
            if (0 != (isdigit((unsigned char) *(ptr+2)))) {
              *ptr2++ = *(ptr+2);
              z++;
            }
            *ptr2++ = 'C';
            *ptr2++ = ' ';
            z++;
            z++;
          }
        }
      }

    }
  }

  snprintf(str1, 199, "%s", a);

  return sz;
}

int main(void) {
  char str[200];
  char *str1 = str;

  const char *da_url = "http://127.0.0.1:8000";
  CURL *curl = NULL;

  snprintf(str, 199, "%s", "NULL");
  curl_global_init(CURL_GLOBAL_ALL);

  if (NULL == (curl = curl_easy_init())) {
    goto error;
  }

  curl_easy_setopt(curl, CURLOPT_URL, da_url);
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 5L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_temp_data_cb);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, str1);

  curl_easy_perform(curl);


error:
  if (NULL != curl) {
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  /* *(--str1) = '\0'; */
  str[strlen(str)-1] = '\0';
  printf("%s\n", str);

  return 0;
}
