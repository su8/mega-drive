/*
 * Copyright (c) 2006-2007 -  http://brynet.biz.tm - <brynet@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* You need to include a file with fairly(ish) compliant printf prototype, Decimal and String support like %s and %d and this is truely all you need! */
#include <stdio.h> /* for printf(); */

/* Required Declarations */
int do_intel(void);
int do_amd(void);
/* void printregs(int eax, int ebx, int ecx, int edx); */

#define cpuid(in, a, b, c, d) __asm__("cpuid": "=a" (a), "=b" (b), "=c" (c), "=d" (d) : "a" (in));

/* Simply call this function detect_cpu(); */
int detect_cpu(void) { /* or main() if your trying to port this as an independant application */
	unsigned long ebx, unused;
	cpuid(0, unused, ebx, unused, unused);
	switch(ebx) {
		case 0x68747541: /* AMD Magic Code */
		do_amd();
		break;
		default:
		printf("Unknown x86 CPU Detected\n");
		break;
	}
	return 0;
}

/* Print Registers */
void printregs(unsigned long int eax, unsigned long int ebx, unsigned long int ecx, unsigned long int edx) {
	int j;
	char string[250];
	string[249] = '\0';
	for(j = 0; j < 13; j++) {
		string[j] = (char)(eax >> (8 * j));
		string[j + 4] = (char)(ebx >> (8 * j));
		string[j + 8] = (char)(ecx >> (8 * j));
		string[j + 12] = (char)(edx >> (8 * j));
	}
	printf("%s", string);
}

/* AMD-specific information */
int do_amd(void) {
	/* printf("AMD Specific Features:\n"); */
	unsigned long extended, eax, ebx, ecx, edx, unused;
	int family, model, stepping, reserved;
	/* cpuid(1, eax, unused, unused, unused); */
	/* model = (eax >> 4) & 0xf; */
	/* family = (eax >> 8) & 0xf; */
	/* stepping = eax & 0xf; */
	/* /1* reserved = eax >> 12; *1/ */
	/* printf("Family: %d Model: %d [", family, model); */
	/* printf("]\n"); */
	/* cpuid(0x80000000, extended, unused, unused, unused); */
	/* if(extended == 0) { */
	/* 	return 0; */
	/* } */
	/* if(extended >= 0x80000002) { */
	/* 	unsigned int j; */
	/* 	printf("Detected Processor Name: "); */
	/* 	for(j = 0x80000002; j <= 0x80000004; j++) { */
	/* 		cpuid(j, eax, ebx, ecx, edx); */
	/* 		printregs(eax, ebx, ecx, edx); */
	/* 	} */
	/* 	printf("\n"); */
	/* } */
  cpuid(0x80000000, eax, ebx, ecx, edx);
  /* putchar((char)(ecx >> (8))); */
  printregs(eax, ebx, ecx, edx);
	/* if(extended >= 0x80000007) { */
	/* 	cpuid(0x80000007, unused, unused, unused, edx); */
	/* 	if(edx & 1) { */
	/* 		printf("Temperature Sensing Diode Detected!\n"); */
	/* 	} */
	/* } */
	/* printf("Stepping: %d Reserved: %d\n", stepping, reserved); */
	return 0;
}


int main(void) {
  detect_cpu();
  return 0;
}
