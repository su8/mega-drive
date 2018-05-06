/*
   04/05/2018 https://github.com/su8/query-github

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
   MA 02110-1301, USA.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <curl/curl.h>

#define GITHUB_TOKEN "empty"

static size_t read_github_data_cb(char *, size_t, size_t, char *);

static size_t
read_github_data_cb(char *data, size_t size, size_t nmemb, char *str1) {

  return nmemb * size;
}
/*   char *ptr = data; */
/*   size_t sz = nmemb * size,z = 0; */
/*   static size_t x = 0; */

/*   for (; *ptr; ptr++,z++) { */
/*     if ((z+7) < sz) { /1* Verifying up to *(ptr+7) *1/ */

/*       if ('n' == *ptr) { /1* "new": true *1/ */
/*         if ('e' == *(ptr+1) && 'w' == *(ptr+2) && 't' == *(ptr+6)) { */
/*           ++x; */
/*         } */
/*       } */

/*     } */
/*   } */
/*   snprintf(str1, 49, "%zu", x); */

/*   return sz; */
/* } */


int main(void) {
  /* char str[50]; */
  const char *const github_url = "https://google.com";
  double total = 0.0;

  CURL *curl = NULL;
  CURLcode res;

  curl_global_init(CURL_GLOBAL_ALL);

  if (NULL == (curl = curl_easy_init())) {
    goto error;
  }

  curl_easy_setopt(curl, CURLOPT_URL, github_url);
  curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
  curl_easy_setopt(curl, CURLOPT_USERAGENT, "query-github/1.0");
  curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL); 
  curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_github_data_cb);
  /* curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); */

/* curl_easy_setopt(curl, CURLOPT_RETURNTRANSFER, 0L); */
  /* curl_easy_setopt(curl, CURLOPT_WRITEDATA, str); */
  res = curl_easy_perform(curl);
  if (CURLE_OK != res) {
    goto error;
  }

  res = curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD, &total);
  if (CURLE_OK != res) {
    goto error;
  }

  printf("%0.3f\n", total/1024);

error:
  if (NULL != curl) {
    curl_easy_cleanup(curl);
  }
  curl_global_cleanup();

  return EXIT_SUCCESS;
}
