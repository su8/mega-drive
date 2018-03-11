/* #include <stdio.h> */

/* int main(void) { */
/*     int i; */
/*     unsigned int index = 0; */
/*     unsigned int regs[4]; */
/*     /1* int sum; *1/ */
/*     __asm__ __volatile__( */
/* /1* #if defined(__x86_64__) || defined(_M_AMD64) || defined (_M_X64) *1/ */
/* /1*         "pushq %%rbx     \n\t" /2* save %rbx *2/ *1/ */
/* /1* #else *1/ */
/* /1*         "pushl %%ebx     \n\t" /2* save %ebx *2/ *1/ */
/* /1* #endif *1/ */
/* /1*         "cpuid            \n\t" *1/ */
/* /1*         "movl %%ebx ,%[ebx]  \n\t" /2* write the result into output var *2/ *1/ */
/* /1* #if defined(__x86_64__) || defined(_M_AMD64) || defined (_M_X64) *1/ */
/* /1*         "popq %%rbx \n\t" *1/ */
/* /1* #else *1/ */
/* /1*         "popl %%ebx \n\t" *1/ */
/* /1* #endif *1/ */
/*         "cpuid" */
/*         : "=a"(regs[0]), [ebx] "=r"(regs[1]), "=c"(regs[2]), "=d"(regs[3]) */
/*         : "a"(index)); */
/*     for (i=4; i<8; i++) { */
/*         printf("%c" ,((char *)regs)[i]); */
/*     } */
/*     for (i=12; i<16; i++) { */
/*         printf("%c" ,((char *)regs)[i]); */
/*     } */
/*     for (i=8; i<12; i++) { */
/*         printf("%c" ,((char *)regs)[i]); */
/*     } */
/*     printf("\n"); */

/*     return 0; */
/* } */
static inline void native_cpuid(unsigned int *eax, unsigned int *ebx,
                                unsigned int *ecx, unsigned int *edx)
{
        /* ecx is often an input as well as an output. */
        __asm__ __volatile__("cpuid"
            : "=a" (*eax),
              "=b" (*ebx),
              "=c" (*ecx),
              "=d" (*edx)
            : "0" (*eax), "2" (*ecx));
}

#include <stdio.h>

int main(void)
{
  unsigned eax, ebx, ecx, edx;

  eax = 1; /* processor info and feature bits */
  native_cpuid(&eax, &ebx, &ecx, &edx);

  printf("stepping %d\n", eax & 0xF);
  printf("model %d\n", (eax >> 4) & 0xF);
  printf("family %d\n", (eax >> 8) & 0xF);
  printf("processor type %d\n", (eax >> 12) & 0x3);
  printf("extended model %d\n", (eax >> 16) & 0xF);
  printf("extended family %d\n", (eax >> 20) & 0xFF);

  /* EDIT */
  /* eax = 3; /1* processor serial number *1/ */
  /* native_cpuid(&eax, &ebx, &ecx, &edx); */

  /** see the CPUID Wikipedia article on which models return the serial 
      number in which registers. The example here is for 
      Pentium III */
  /* printf("serial number 0x%08x%08x\n", edx, ecx); */
  return 0;
}
