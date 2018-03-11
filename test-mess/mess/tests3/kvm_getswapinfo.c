#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>


#include <sys/param.h>
#include <sys/stat.h>
#include <sys/sysctl.h>
#include <vm/vm_param.h>


/* 
http://cpansearch.perl.org/src/SCRESTO/Sys-MemInfo-0.98/arch/freebsd.xs
swapinfo -k
Device          1K-blocks     Used    Avail Capacity
/dev/md99           65536        0    65536     0%

*/

int main(void) {

		struct xswdev xsw;
		int mib[20];
		unsigned long long used = 0, total = 0;
        int pagesize = 4096;
        memset(mib, 0, sizeof(mib));
		size_t mibsize = sizeof(mib) / sizeof(mib[0]);
		size_t size = sizeof(struct xswdev);
		
		

		if (0 == sysctlnametomib("vm.swap_info", mib, &mibsize)) {

				if (-1 == sysctl(mib, mibsize+1, &xsw, &size, NULL, 0))
					return -1;
  
				if (xsw.xsw_version != XSWDEV_VERSION)
					return -1;
  		total = (unsigned long long) xsw.xsw_nblks;


  		used = (unsigned long long) xsw.xsw_used;
//printf("%llu\n", total);
//printf("%llu\n", used);
		}
		
		used = (total - used) *  (unsigned long long)pagesize / (1024*1024);
		
		printf("%llu\n", used);
  
  return 0;
}
