#include <stdio.h>
#include <curl/curl.h>
 
/* This is a simple example showing how to list the folders within an IMAP
 * mailbox.
 *
 * Note that this example requires libcurl 7.30.0 or above.
 */ 
static size_t read_ip_data_cb(char *data, size_t size, size_t nmemb, char *str1) {
  /* printf("%s\n", data); */
  return (nmemb * size);
}
 
int main(void)
{
  CURL *curl;
  CURLcode res = CURLE_OK;
 
  curl = curl_easy_init();
  if(curl) {
    /* Set username and password */ 
    curl_easy_setopt(curl, CURLOPT_USERNAME, "");
    curl_easy_setopt(curl, CURLOPT_PASSWORD, "");
   struct curl_slist *chunk = NULL;
 
    /* Remove a header curl would otherwise add by itself */ 
    /* chunk = curl_slist_append(chunk, "Accept:"); */
 
    /* /1* Add a custom header *1/ */ 
    /* chunk = curl_slist_append(chunk, "Another: yes"); */
 
    /* /1* Modify a header curl otherwise adds differently *1/ */ 
    /* chunk = curl_slist_append(chunk, "Host: example.com"); */
 
    /* Add a header with "blank" contents to the right of the colon. Note that
       we're then using a semicolon in the string we pass to curl! */ 
    chunk = curl_slist_append(chunk, "SEARCH UNSEEN");
 
    /* set our custom set of headers */ 
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk); 
    /* This will list the folders within the user's mailbox. If you want to
     * list the folders within a specific folder, for example the inbox, then
     * specify the folder as a path in the URL such as /INBOX */ 
    curl_easy_setopt(curl, CURLOPT_URL, "imaps://imap.gmail.com:993/INBOX");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, read_ip_data_cb);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "gzip");
    curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL); 
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 20L);
 
    /* Perform the list */ 
    res = curl_easy_perform(curl);
 
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* Always cleanup */ 
    curl_easy_cleanup(curl);
  }
 
  return (int)res;
}
