/*
* main.c
* 
* This simple example shows:
* How to execute the cpuid instruction. 
* How to call a function in an assembled file, utils.asm. 
* 
* This builds and runs on a x86_64 Linux.
* Minor changes are needed for a 32bit x86 Linux.
*
* gcc -Wall -g -c -o main.o main.c
* nasm -Wall -g -f elf64 -o utils.o utils.asm
* gcc -Wall -g -o cpuid main.o utils.o
* 
*/

/* #include <stdio.h> */

/* /1* Defined in utils.asm *1/ */
/* extern void GetCpuID(void); */
/* extern char vendor_id[12]; */
/* /1* extern unsigned version; *1/ */
/* /1* extern unsigned features; *1/ */

/* int main(void) */ 
/* { */
/* GetCpuID(); */
/* printf("\nvendor_id is %s", vendor_id); */
/* /1* printf("\nversion is 0x%04X", version); *1/ */
/* /1* printf("\nfeatures are 0x%04X\n\n", features); *1/ */
/* return 0; */
/* } */
#include <stdio.h>

int main(void)
{
	int id;
	int eax = 0;

	__asm__("mov %1, %%eax; "	/* eax into EAX */
		"cpuid;"
		"mov %%eax, %0;"	/* EAX into id */
		:"=r"(id)
		:"r"(eax)
		:"%eax");

	printf("Vendor ID: %d\n", id);

	return 0;
}
