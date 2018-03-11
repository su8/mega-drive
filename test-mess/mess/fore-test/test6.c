#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include <curl/curl.h>
/* char *str = "MEOW"; */
/* size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) */
/* size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata); */
/* size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata); */
static size_t read_callback(char *data, size_t size, size_t nmemb, void *uuze) {
  char *ptr = NULL, *str = (char *)uuze;
  size_t sz = nmemb * size;
  unsigned long x = 0;

  for (ptr = data; *ptr; ptr++, x++) {
    if (*ptr == 't') {
      if ((x+1) < sz && (x+2) < sz && (x+3) < sz) {
        if (*(ptr+1) == 'e' && *(ptr+2) == 'm' && *(ptr+3) == 'p') {
          if ((x+6) < sz && (x+7) < sz) {
            if (isdigit((unsigned char) *(ptr+6)) &&
             isdigit((unsigned char) *(ptr+7))) {
              *str++ = *(ptr+6);
              *str++ = *(ptr+7);
            }
          }
          *str = '\0';
          break;
        }
      }
    }
  }

  return sz;
}

int main(void) {
/*
  API docs - http://openweathermap.org/current
  Register yourself, create a new API key:
   https://home.openweathermap.org/api_keys
  add it after APPID=
*/
  const char *url_template = "http://api.openweathermap.org/data/2.5/weather?q=London,uk&units=metric&APPID=28459ae16e4b3a7e5628ff21f4907b6f";
  
  CURL *curl = NULL;
  CURLcode res;
  char str[300];

  curl_global_init(CURL_GLOBAL_ALL);
  curl = curl_easy_init();

  if (NULL == curl) {
    goto seeya;
  }

  curl_easy_setopt(curl, CURLOPT_URL, url_template);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &str);

  res = curl_easy_perform(curl);
  if (CURLE_OK != res) {
    goto seeya;
  }
  printf("last: %s\n", str);

seeya:
  if (NULL != curl) {
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();

  return 0;

}
