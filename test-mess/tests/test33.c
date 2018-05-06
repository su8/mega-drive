/* Use libcurl to retrieve Gmail folders and labels via IMAP over SSL (IMAPS).
 
Usage: ShowGmailFolders <username> <password>
 
curl-library mailing list thread:
'Re: DL curl 7.35 mingw32'
http://curl.haxx.se/mail/lib-2015-05/0037.html
 
Note: When you attempt to login to Gmail via IMAP they sometimes require a
web login first for security reasons. In that case an error will be shown. Such
an error looks like "A002 NO [ALERT] Please log in via your web browser".
Also, GMail may block the attempt to login unless you authorize "less secure"
apps to have access to your account. All that means is apps have permission to
send your username and password directly to Gmail (instead of an auth token).
http://support.google.com/mail/accounts/bin/answer.py?answer=78754
https://www.google.com/settings/security/lesssecureapps
 
Copyright (C) 2015 Jay Satiro <raysatiro@yahoo.com>
http://curl.haxx.se/docs/copyright.html
 
https://gist.github.com/jay/a43724c98220de85d020
*/
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
/* http://curl.haxx.se/download.html */
#include <curl/curl.h>
 
 
#undef FALSE
#define FALSE 0
#undef TRUE
#define TRUE 1
 
#define MAX_GMAIL_USER_LEN 256
#define MAX_GMAIL_PASS_LEN 256
 
/* This struct is used by write_callback */
struct memobj {
  char *memory;
  size_t size, allocated;
};
 
int ShowGmailFolders(const char *username, const char *password);
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata);
 
int main(int argc, char *argv[])
{
  if(argc != 3) {
    fprintf(stderr, "Usage: ShowGmailFolders <username> <password>\n");
    return EXIT_FAILURE;
  }
 
  if(curl_global_init(CURL_GLOBAL_ALL)) {
    fprintf(stderr, "Fatal: The initialization of libcurl has failed.\n");
    return EXIT_FAILURE;
  }
 
  if(atexit(curl_global_cleanup)) {
    fprintf(stderr, "Fatal: atexit failed to register curl_global_cleanup.\n");
    curl_global_cleanup();
    return EXIT_FAILURE;
  }
 
  if(!ShowGmailFolders(argv[1], argv[2])) {
    fprintf(stderr, "Fatal: ShowGmailFolders failed.\n");
    return EXIT_FAILURE;
  }
 
  return EXIT_SUCCESS;
}
 
size_t write_callback(char *ptr, size_t size, size_t nmemb, void *userdata)
{
  size_t realsize = size * nmemb;
  struct memobj *mem = (struct memobj *)userdata;
 
  if(!realsize)
    return 0;
 
  /*
  Reallocating to an amount of memory larger than what's required may have a
  performance benefit if it stops excessive reallocations, or it may just be a
  waste of memory, depending on your application and operating system.
 
  Also, though it's acceptable in this case to return 0 on error that's not
  true of all write functions, specifically those that need to return an error
  when realsize is 0. In those cases you can return (size_t)-1 on error.
  */
  if((mem->size + realsize + 1) > mem->allocated) {
    size_t bytes = 65536 + mem->size + realsize + 1;
    char *temp = (char *)realloc(mem->memory, bytes);
    if(!temp) {
      fprintf(stderr, "Error: Out of memory, realloc returned NULL.");
      return 0;
    }
    mem->memory = temp;
    mem->allocated = bytes;
  }
 
  memcpy(&(mem->memory[mem->size]), ptr, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
 
/* LIST GMail folders via imaps protocol.
Returns TRUE on success, FALSE on failure.
*/
int ShowGmailFolders(const char *username, const char *password)
{
  int retcode = FALSE;
  CURL *curl = NULL;
  CURLcode res = CURLE_FAILED_INIT;
  char errbuf[CURL_ERROR_SIZE] = { 0, };
  struct memobj body = { 0, };
  struct memobj headers = { 0, };
  const char *const sep = "---------------------------------------------------"
                          "----------------------------";
 
  if(!username || !*username) {
    fprintf(stderr, "Error: Missing username.\n");
    goto cleanup;
  }
  else if(!memchr(username, 0, MAX_GMAIL_USER_LEN)) {
    fprintf(stderr, "Error: Username is greater than %d characters.\n",
            MAX_GMAIL_USER_LEN);
    goto cleanup;
  }
  else if(!password || !*password) {
    fprintf(stderr, "Error: Missing password.\n");
    goto cleanup;
  }
  else if(!memchr(password, 0, MAX_GMAIL_PASS_LEN)) {
    fprintf(stderr, "Error: Password is greater than %d characters.\n",
            MAX_GMAIL_PASS_LEN);
    goto cleanup;
  }
 
  curl = curl_easy_init();
  if(!curl)  {
    fprintf(stderr, "Error: curl_easy_init failed.\n");
    goto cleanup;
  }
 
  /* CURLOPT_CAINFO
  To verify SSL sites you may need to load a bundle of certificates.
 
  You can download the default bundle here:
  https://raw.githubusercontent.com/bagder/ca-bundle/master/ca-bundle.crt
 
  However your SSL backend might use a database in addition to or instead of
  the bundle.
  http://curl.haxx.se/docs/ssl-compared.html
  */
  /* curl_easy_setopt(curl, CURLOPT_CAINFO, "curl-ca-bundle.crt"); */
 
  /* Only allow IMAPS, we do not want this to work when unencrypted. */
  curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_IMAPS);
 
  /* Send all data to the write_callback */
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&body);
  curl_easy_setopt(curl, CURLOPT_HEADERDATA, (void *)&headers);
 
  curl_easy_setopt(curl, CURLOPT_USERNAME, username);
  curl_easy_setopt(curl, CURLOPT_PASSWORD, password);
  curl_easy_setopt(curl, CURLOPT_URL, "imaps://imap.gmail.com:993");
 
  /* When no custom request is set the request that will be issued depends on
  the path of the IMAP URL. For example:
 
  imaps://imap.gmail.com:993/ => LIST "" *
  imaps://imap.gmail.com:993/INBOX => LIST "INBOX" *
  imaps://imap.gmail.com:993/INBOX/;UID=13/;SECTION=TEXT => FETCH 13 BODY[TEXT]
  imaps://imap.gmail.com:993/INBOX?SUBJECT%20test => SEARCH SUBJECT test
 
  For more on the IMAP URL scheme refer to https://tools.ietf.org/html/rfc5092
 
  Note for the last example that due to a bug in libcurl IMAP SEARCH will
  truncate and possibly return incorrect output if it receives a large number
  of results. For more refer to http://sourceforge.net/p/curl/bugs/1366/
 
  If there is some request you're unable to express through the IMAP URL scheme
  then you can use CURLOPT_CUSTOMREQUEST to specify it as a custom command.
  You will likely have to parse the result and it may be written to the header
  but not the body, depending on the command. For multiple custom commands
  you'll need to call curl_easy_perform multiple times, leaving the URL the
  same but changing the CURLOPT_CUSTOMREQUEST before each call.
 
  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "LIST \"\" *");
  */
 
  curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
  curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, errbuf);
 
  res = curl_easy_perform(curl);
  if(res != CURLE_OK) {
    size_t len = strlen(errbuf);
    fprintf(stderr, "\nlibcurl: (%d) ", res);
    if(len)
      fprintf(stderr, "%s%s", errbuf, ((errbuf[len - 1] != '\n') ? "\n" : ""));
    fprintf(stderr, "%s\n\n", curl_easy_strerror(res));
    goto cleanup;
  }
 
  printf("\n\n%s\n", sep);
  printf("Headers:\n\n%s", headers.memory ? headers.memory : "");
  printf("\n%s\n", sep);
 
  printf("\n\n%s\n", sep);
  printf("Body:\n\n%s", body.memory ? body.memory : "");
  printf("\n%s\n", sep);
 
  retcode = TRUE;
cleanup:
  free(body.memory);
  free(headers.memory);
  curl_easy_cleanup(curl);
  return retcode;
}
