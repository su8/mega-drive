#include <stdio.h>

#define cpuid(in, b) __asm__("cpuid": "=b" (b) : "a" (in))
#define AMD    0x68747541
#define INTEL  0x756e6547
#define VIA    0x746e6543

int main(void) {
  unsigned long int regizter;

  cpuid(0, regizter);
  switch(regizter) {
    case AMD:
      printf("%s\n", "Its AMD");
      break;

    case INTEL:
      printf("%s\n", "Its Intel");
      break;

    case VIA:
      printf("%s\n", "Its VIA");
      break;
  }

  return 0;
}
