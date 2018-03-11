/*
    Author: Kevin Devine <wyse101 0x40 gmail.com>
    WWW:    http://weiss.u40.hosting.digiweb.ie/
    Date:   April 2008

    example input: CP0615JT109
    
    this is 1 other key generation algorithm 

 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int u32;
typedef unsigned char u8;

u8 secret[]="ViveLaFrance!\0";

int main(int argc, char **argv)
{
    u8 key[26+1];
    u8 serialNumber[8]={0};
    u8 *out = key;
    u8 x,y;
    u32 i;

    if( argc == 2 && strlen(argv[1]) == 11) {

      serialNumber[0] = argv[1][4];
      serialNumber[1] = argv[1][5];
      serialNumber[2] = argv[1][8];
      serialNumber[3] = argv[1][9];
      serialNumber[4] = argv[1][10];

      fprintf(stdout,"\nProcessing %s\n",serialNumber);

      for(i = 0;i < 13;i++) {

        x = (secret[i] ^ serialNumber[i % 5]);

        y = (x & 0x0f);
        x = (x & 0xf0) >> 4;

        *out++ = (x >= 10) ? (x + '7') : (x + '0');
        *out++ = (y >= 10) ? (y + '7') : (y + '0');
      }
      
      fprintf(stdout,"Key = %s\n\n",key);

   } else fprintf(stdout,"\nUsage:%s <SERIAL NUMBER>\n\n",argv[0]);
}
