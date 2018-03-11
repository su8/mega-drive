#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/syscall.h>
#include <linux/perf_event.h>
#include <asm/unistd.h>

// There is currently no glibc wrapper, so you have to call it as syscall
static long
perf_event_open(struct perf_event_attr *hw_event, pid_t pid,
                int cpu, int group_fd, unsigned long flags)
{
    int ret;

    ret = syscall(__NR_perf_event_open, hw_event, pid, cpu,
                   group_fd, flags);
    return ret;
}



int main(int argc, char* argv[])
{
    int i, err;
    struct perf_event_attr attr;
    int *perf_fds;
    int nr_cpus = sysconf(_SC_NPROCESSORS_ONLN);
    long long result = 0;

    perf_fds = (int*) malloc(nr_cpus * sizeof(int));
    if (!perf_fds)
    {
        fprintf(stderr, "Not enough memory\n");
        return 1;
    }

    // Configure th event
    // see http://man7.org/linux/man-pages/man2/perf_event_open.2.html for details
    memset(&attr, 0, sizeof(struct perf_event_attr));
    attr.type = PERF_TYPE_HARDWARE;
    attr.size = sizeof(struct perf_event_attr);
    attr.config = PERF_COUNT_HW_INSTRUCTIONS;
    attr.inherit = 1;

    for (i = 0; i < nr_cpus; i++)
    {
        // This measures the calling process/thread on any CPU.
        // Due to the setting of attr.inherit, it will also count all child
        // processes of the current process
        // see http://man7.org/linux/man-pages/man2/perf_event_open.2.html for details
        perf_fds[i] = perf_event_open(&attr, 0, -1, -1, 0);
        if (perf_fds[i] < 0)
        {
            fprintf(stderr, "Failed to start counter for CPU %d\n", i);
        }
        // Resetting counter to zero
        ioctl(perf_fds[i], PERF_EVENT_IOC_RESET, 0);
    }
    for (i = 0; i < nr_cpus; i++)
    {
        // Start counters
        ioctl(perf_fds[i], PERF_EVENT_IOC_ENABLE, 0);
    }

    // Do what you want. Execute another application or perform some calculations
    sleep(2);

    for (i = 0; i < nr_cpus; i++)
    {
        // Stop counter
        ioctl(perf_fds[i], PERF_EVENT_IOC_DISABLE, 0);
        // Read result
        err = read(perf_fds[i], &result, sizeof(long long));
        if (err != sizeof(long long))
        {
            fprintf(stderr, "Failed to read counter at CPU %d\n", i);
            continue;
        }
        printf("CPU %d executed %lu instructions\n", i, result);
        close(perf_fds[i]);
    }
    free(perf_fds);
    return 0;
}
