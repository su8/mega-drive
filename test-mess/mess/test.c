#include <stdio.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <ctype.h>

#include <sys/statvfs.h>
#include <sys/sysinfo.h>
#include <sys/utsname.h>
#include <glob.h>
#include <unistd.h>
#define FILL_ARR(x, z, ...) (snprintf(x, 300, z, __VA_ARGS__))

/* #define cpuid(in, b) __asm__("cpuid": "=b" (b) : "a" (in)) */
/* #define cpuuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in)) */
/* #define CPU_FEATURE(in, a) __asm__("cpuid": "=a" (a) : "a" (in)) */
#define CPU_VENDOR(x, z) __asm__("cpuid": "=b" (z) : "a" (x))
#define CPU_FEATURE(x, z) __asm__("cpuid": "=a" (z) : "a" (x))
#define CPU_STR2(regizter, a, b, c, d) __asm__( \
  "cpuid": \
    "=a" (a), \
    "=b" (b), \
    "=c" (c), \
    "=d" (d) \
    : "a" (regizter) \
)
#define CPU_ID_STR(regizter, b, c, d) __asm__( \
  "cpuid": \
    "=b" (b), \
    "=c" (c), \
    "=d" (d) \
    : "a" (regizter) \
)

#define BIT_SHIFT(x) ((x) & 0xf)
#define AmD    0x68747541
#define InteL  0x756e6547

#define VLA 200

/* #define AMD    0x68747541 */
/* #define INTEL  0x756e6547 */
/* #define BIT_SHIFT(x) ((x) & 0xf) */
#define FMT_UINT "%"PRIuMAX

/* void printregs(unsigned long int eax, unsigned long int ebx, unsigned long int ecx, unsigned long int edx) { */
/* 	int j; */
/* 	char string[250]; */
/* 	string[249] = '\0'; */
/* 	for(j = 0; j < 4; j++) { */
/* 		string[j] = (char)(eax >> (8 * j)); */
/* 		string[j + 4] = (char)(ebx >> (8 * j)); */
/* 		string[j + 8] = (char)(ecx >> (8 * j)); */
/* 		string[j + 12] = (char)(edx >> (8 * j)); */
/* 	} */
/* 	printf("%s", string); */
/* } */

int main(void) {
  /* char buffer[VLA]; */
  /* char str1[VLA]; */
  /* char str2[VLA]; */
  /* char ex[2]; */
  /* char *all = buffer; */
  /* uintmax_t eax = 0, vend = 0, num = 0, vend_str = 0, z = 0, num2 = 0; */
  uintmax_t ebx = 0, ecx = 0, eax = 0, edx= 0,x=0;
  /* , edx = 0, dummy = 0, x = 0, eax_old = 0; */

  /* CPU_VENDOR(0, vend); */
  /* if (0 == vend) { */
  /*   FILL_STR_ARR(1, str1, "Null"); */
  /*   return; */
  /* } */
  /* int eaxx = 0; */
  /* CPU_FEATURE(0x00000001, eaxx); */
  /* printf("elo %02x\n", (int)eaxx); */
	CPU_STR2(0x80000001, eax, ebx, ecx, edx); /* movl $0x80000000, %eax */
  /* if (edx & (1<<19)) */
  /* for (x=0;x<7;x++) */
  (void)x;
  /* x=(edx >> 27) & 0xff */
  /* if (edx & (1 << 27)) */
    printf(FMT_UINT"\n",(edx & (1 << 29)));

  /* switch(vend) { */
  /*   case AmD: */
  /*     num = 0; */
  /*     break; */

  /*   case InteL: */
  /*     num = 1; */
  /*     break; */
  /* } */

  /* Dont have intel cpu to verify the following code */
  /* if (0 == num && 0 != vend_str) { */
    /* for (x = 0x80000002; x <= 0x80000004; x++) {    /1* movl $0x80000002, %esi *1/ */
      /* CPU_STR2(4, eax, ebx, ecx, edx);               /1* cmpl $0x80000004, %eax *1/ */
      /* CPU_STR(0x80000005, eax, ebx, ecx, edx); */
      /* int x = 0; */
      /* printf("%"PRIuMAX, eax); */
      /* for (x = 0; x < 1; x++) { */
      /* printf("%c\n",(char)(eax >> (5 * 8))); */
      /* printf("%c\n",(char)(ebx >> (x * 8))); */
      /* a= ecx >> (12) & 0xff; */
      /* if (a) */
      /*   a = 1 << a; */
      /* else */
      /*   a = (int)(ecx & 0xff) + 1; */
      /* printf("%u \n",(unsigned int)((eax >> 26) & 0x3f )); */
      /* printf("%c\n",(char)(edx >> (x * 8))); */
      /* printf("%d\n",x); */
      /* } */
      /* char vend_chars[13]; */
      /* uintmax_t ff=0, meow; */
      /* ff|=((edx >> 0) &1); */
      /*   printf(FMT_UINT"\n", ff); */
      /* ff|=(((edx >>26) &1)); */
      /*   printf(FMT_UINT"\n", ff); */
      /* ff|=(((edx >>3) &1)); */
      /*   printf(FMT_UINT"\n", ff); */
      /* ff|=(((edx >>26) &1)); */
      /* CPU_VENDOR(0, eax); */
      /* vend_chars[49] = '\0'; */
      /* for (z = 0; z < 4; z++) { */
        /* vend_chars[z] = (char)(ebx >> (z * 8));     /1* movl %eax *1/ */
        /* vend_chars[24+z] = (char)(ebx >> (z * 8));   /1* movl %ebx, 4 *1/ */
        /* vend_chars[4+z] = (char)(edx >> (z * 8));   /1* movl %ecx, 8 *1/ */
        /* vend_chars[8+z] = (char)(ecx >> (z * 8));  /1* movl %edx, 12 *1/ */
        /* printf(FMT_UINT"\n", ff); */
        /* putchar((char)(edx >> (z*8))); */
        /* putchar((char)(ecx >> (z*8))); */
        /* putchar((char)(edx >> (z))); */
      /* } */
      /* vend_chars[5] = ' '; */
      /* vend_chars[12] = '\0'; */
      /* vend_chars[16] = ' '; */
        /* printf("%s", vend_chars); */
      /* all += snprintf(all, VLA, "%s", vend_chars); */
    /* } */
  /* } */

  /* size_t len = strlen(buffer); */
  /* char allowed[] = "()ACDEFGHIJKLMNOPQRSTUVWXYZ1234567890ac defghijklmnopqrstuvwxyz"; */

  /* printf("%d", '&'); */

  /* for (z=0;z<len;z++) { */
  /*     /1* putchar(buffer[z]); *1/ */
  /*     /1* if (buffer[z] == 'e')printf("%d %d", buffer[z], buffer[z+1]); *1/ */
  /*     /1* switch(buffer[z]) { *1/ */
  /*     /1*   case (char)38: *1/ */
  /*     /1*   /2* case (char)73: *2/ *1/ */
  /*     /1*   /2* case (char)98: *2/ *1/ */
  /*     /1*   case (char)176: *1/ */
  /*     /1*     continue; *1/ */
  /*     /1* } *1/ */
  /*   /1* if (isprint((unsigned char) buffer[z])) { *1/ */
  /*     /1* if (buffer[z] != '?' && buffer[z] != '&') *1/ */
  /*     str1[num2++] = buffer[z]; */
  /*     /1* putchar(str1[num2--]); *1/ */
  /*   /1* } *1/ */
  /* } */
  /* str1[num2]='\0'; */
  /* snprintf(str1, VLA, "%s", buffer); */
  /* printf("%s\n", str1); */



  /* uintmax_t eax = 0, regizter = 0, idx = 0, extended = 0, unused = 0, ebx = 0, ecx = 0, edx = 0; */
  /* uintmax_t vend = 0, num = 0, vend_str = 0, z = 0; */
  /* uintmax_t dummy = 0, x = 0, eax_old = 0; */
            /* ebx, ecx, edx, */ 
	/* unsigned long extended, eax, ebx, ecx, edx, unused; */

  /* char str1[500]; */

  /* cpuid(0, regizter); */
	/* CPU_FEATURE(1, eax); */
	/* cpuuid(0x80000000, extended); */
	/* cpuuid(1, eax, unused, unused, unused); */
	/* cpuuid(0x80000000, extended, unused, unused, unused); */
	/* if(extended == 0) { */
	/* 	return 0; */
	/* } */
	/* if(extended >= 0x80000002) { */
	/* 	unsigned int j; */
	/* 	printf("Detected Processor Name: "); */
	/* 	for(j = 0x80000002; j <= 0x80000004; j++) { */
	/* 		cpuuid(j, eax, ebx, ecx, edx); */
	/* 		printregs(eax, ebx, ecx, edx); */
	/* 	} */
	/* 	printf("\n"); */
	/* } */

	/* cpuid(1, eax, unused, unused, unused); */

  /* switch(regizter) { */
  /*   case INTEL: */
  /*     idx = 1; */
  /*     break; */

  /*   case AMD: */
  /*     idx = 0; */
  /*     break; */
  /* } */
  /* if (extended >= 0x80000002) { */
  /*   printf("%s\n", "yes"); */
  /* } */
  /* FILL_ARR(str1, "%s Stepping " FMT_UINT " Family " FMT_UINT " Model " FMT_UINT, */
  /*   (0 == idx ? "AMD" : "Intel"), BIT_SHIFT(eax), BIT_SHIFT(eax >> 8), */
  /*   BIT_SHIFT(eax >> 4)); */

  /* printf("%s\n", str1); */
  return 0;
}
