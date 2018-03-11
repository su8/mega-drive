/*
    Author: Kevin Devine <wyse101 0x40 gmail.com>
    WWW:    http://weiss.u40.hosting.digiweb.ie/
    Date:   April 2008

    used to calculate checksum byte of serial number for Thomson router
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int u32;
typedef unsigned char u8;

u8 numTable[256+1];

void createTable(u8 initVal)
{
    u32 i,j;
    u8 x,y;

    if(numTable[256] != initVal) {

      numTable[256] = initVal;

      for(i = 0;i < 256;i++) {

        x = i;

        for(j = 0;j < 8;j++) {

          y = (x >> 7);
          x <<= 1;

          if( y & y )
              x ^= numTable[256];
        }
        numTable[i] = x;
      }
    }
}

int main(int argc, char **argv)
{
    u8 sumCode = 0,*p;

    if(--argc && (strlen(argv[1])) == 9) {
      createTable(7);

      for(p = argv[1];*p = toupper(*p);p++)
        sumCode = numTable[ (sumCode ^ *p) ] ^ (sumCode << 8);

        /* note: this is more like a checksum than configuration code */
      fprintf(stdout,"\nSpeedTouch [C]hecksum [C]ode: ( %.2x )\n\n",sumCode);
    } else 
      fprintf(stdout,"\n%s <SERIAL NUMBER>\n\n",argv[0]);
    return(0);
}
