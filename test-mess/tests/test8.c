#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <curl/curl.h>

static size_t read_gmail_data_cb(char *, size_t , size_t , char *);

static size_t
read_gmail_data_cb(char *data, size_t size, size_t nmemb, char *str1) {
  char *ptr = data;
  static size_t z = 0;
  static char one_run = 0;
  size_t sz = nmemb * size, x = 0;

  if (0 == one_run) {
    for (; *ptr; ptr++, x++) {
      if ('.' == *ptr) {
        break;
      }
      if ('\n' == *ptr) {
        if ('\n' == *(ptr+1)) {
          break;
        }
        z++;
      }
    }
    /* printf("%s\n", data); */

    snprintf(str1, 199, "%zu", z);
    one_run = 1;
  }
  return sz;
}

int main(void) {
  char str1[200];
  const char *const da_url = "pop3s://pop.aol.com";

  CURL *curl = NULL;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_ALL);

  if (NULL == (curl = curl_easy_init())) {
    goto error;
  }

  curl_easy_setopt(curl, CURLOPT_USERNAME, "");
  curl_easy_setopt(curl, CURLOPT_PASSWORD, "");
  curl_easy_setopt(curl, CURLOPT_URL, da_url);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
  curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL); 
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
  /* curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTPS); */
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_gmail_data_cb);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, str1);

  res = curl_easy_perform(curl);
  if (CURLE_OK != res) {
    goto error;
  }
  printf("%s\n", str1);
error:
  if (NULL != curl) {
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();
  return EXIT_SUCCESS;
}
