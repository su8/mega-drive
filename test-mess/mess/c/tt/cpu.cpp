#include "CPUID.h"

#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  CPUID cpuID(0); // Get CPU vendor

  string vendor;
  vendor += string((const char *)&cpuID.EBX(), 4);
  vendor += string((const char *)&cpuID.EDX(), 4);
  vendor += string((const char *)&cpuID.ECX(), 4);

  cout << "CPU vendor = " << vendor << endl;

  return 0;
}
