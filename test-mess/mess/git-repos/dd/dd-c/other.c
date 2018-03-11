/*
    Author: Kevin Devine <wyse101 0x40 gmail.com>
    WWW:    http://weiss.u40.hosting.digiweb.ie/
    Date:   April 2008

    example input: CP0615JT109
    
    it wasn't possible to debug the binary and see what input was
    requested, so i can't say what input it requests for certain.

 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef linux
 #include <openssl/sha.h>
 #define SHA1_Final(x,y) SHA1_Final(y,x)
#else
 #include "sha1.h"

 #define SHA1_Init SHA1Reset
 #define SHA1_Update SHA1Input
 #define SHA1_Final SHA1Result
 #define SHA_CTX SHA1Context
#endif

typedef unsigned int u32;
typedef unsigned char u8;

int main(int argc, char **argv)
{
    u8 key[32]={0};
    SHA_CTX sha1_ctx;
    u8 sha1_digest[32];
    u32 i;

    if( argc == 2 && strlen(argv[1]) == 11 ) {

      SHA1_Init(&sha1_ctx);

      /* set the context to zero */

      ((u32*)&sha1_ctx)[0] = 0;
      ((u32*)&sha1_ctx)[1] = 0;
      ((u32*)&sha1_ctx)[2] = 0;
      ((u32*)&sha1_ctx)[3] = 0;
      ((u32*)&sha1_ctx)[4] = 0;

      SHA1_Update(&sha1_ctx,argv[1],strlen(argv[1]));
      SHA1_Final(&sha1_ctx,sha1_digest);

      /* format 26 bytes */
      for(i = 0;i < 13;i++)
        sprintf(&key[i*2],"%.2X",sha1_digest[i]);

      fprintf(stdout,"\nKey = %s\n\n",key);

   } else fprintf(stdout,"\nUsage:%s <SERIAL NUMBER>\n\n",argv[0]);
}
