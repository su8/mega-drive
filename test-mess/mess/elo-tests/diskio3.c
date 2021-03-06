#elif defined(__OpenBSD__)
/*
 * OpenBSD support, taken from ports-tree cvs.
 * x11/xfce4/xfce4-diskperf/patches/patch-panel-plugin_devperf_c
 */

#include <sys/param.h>
#include <sys/sysctl.h>
#include <sys/disk.h>

int DevPerfInit ()
{
        return (0);
}

int DevCheckStatAvailability(char const **strptr)
{
        return (0);
}

int DevGetPerfData (const void *p_pvDevice, struct devperf_t *perf)
{
	int mib[3], diskn, x;
	size_t len;
	char *devname = (char *)p_pvDevice;
	struct diskstats *ds;
	struct timeval tv;

	mib[0] = CTL_HW;
	mib[1] = HW_DISKCOUNT;
	len = sizeof(diskn);

	if (sysctl(mib, 2, &diskn, &len, NULL, 0) < 0)
		return (-1);

	mib[0] = CTL_HW;
	mib[1] = HW_DISKSTATS;
	len = diskn * sizeof(struct diskstats);

	ds = malloc(len);
	if (ds == NULL)
		return (-1);

	if (sysctl(mib, 2, ds, &len, NULL, 0) < 0) {
		free(ds);
		return (-1);
	}

	for (x = 0; x < diskn; x++)
		if (!strcmp(ds[x].ds_name, devname))
			break;

	if (x == diskn) {
		free(ds);
		return (-1);
	}

	if (gettimeofday(&tv, NULL)) {
		free(ds);
		return (-1);
	}

	perf->timestamp_ns = (uint64_t)1000ull * 1000ull * 1000ull * tv.tv_sec
	    + 1000ull * tv.tv_usec; 
        perf->rbusy_ns = ((uint64_t)1000ull * 1000ull * 1000ull *
	    ds[x].ds_time.tv_sec + 1000ull * ds[x].ds_time.tv_usec) / 2ull;

	perf->wbusy_ns = perf->rbusy_ns / 2ull;
	perf->rbytes = ds[x].ds_rbytes;
	perf->wbytes = ds[x].ds_wbytes;
	perf->qlen = ds[x].ds_rxfer + ds[x].ds_wxfer;

	free(ds);

	return (0);
}
