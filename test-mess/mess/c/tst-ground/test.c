#define _POSIX_SOURCE     /* To get defns of NI_MAXSERV and NI_MAXHOST */
#include <stdio.h>
#include <pci/pci.h>
#define VLA 200
/* PCI IDs are contained in /sys filesystem. */
/* unsigned long read_sysfs_uint(const char* ifa_name, const char* info) { */
/*     char path[PATH_MAX]; */
/*     char buf[12]; */
/*     int fd; */

/*     snprintf(path, PATH_MAX, "/sys/class/net/%s/device/%s", ifa_name, info); */

/*     fd = open(path, O_RDONLY); */
/*     if(fd == -1) */
/*         return 0; */

/*     if(read(fd, buf, 12) == -1) { */
/*         close(fd); */
/*         return 0; */
/*     } */

/*     close(fd); */
/*     return strtoul(buf, NULL, 16); */
/* } */

/* Try to get PCI IDs and get PCI device name for it.
   XXX: doesn't check for subsystem's numbers */
/* void print_pci_ids(const char* ifa_name) { */
/*   printf("%s\n", ifa_name); */
/*     /1* int vendor = (int) read_sysfs_uint(ifa_name, "vendor"); *1/ */
/*     /1* int device = (int) read_sysfs_uint(ifa_name, "device"); *1/ */
/*     /1* int subsystem_vendor = (int) read_sysfs_uint(ifa_name, "subsystem_vendor"); *1/ */
/*     /1* int subsystem_device = (int) read_sysfs_uint(ifa_name, "subsystem_device"); *1/ */

/*     /1* printf("%d %d\n",vendor, device); *1/ */
/* } */

int main(void)
{
    /* struct ifaddrs *ifaddr, *ifa; */
    /* struct in_addr* ifa_inaddr; */
    /* struct in_addr addr; */
    /* int family, s, n; */
    /* s = 0x8168; */

    /* if(argc != 2) { */
    /*     fprintf(stderr, "Usage: getifaddr <IP>\n"); */
    /*     return EXIT_FAILURE; */
    /* } */

    /* if (inet_aton(argv[1], &addr) == 0) { */
    /*     perror("inet_aton"); */
    /*     return EXIT_FAILURE; */
    /* } */

    /* if (getifaddrs(&ifaddr) == -1) { */
    /*     perror("getifaddrs"); */
    /*     return EXIT_FAILURE; */
    /* } */

    /* Walk through linked list, maintaining head pointer so we
        can free list later */

/*     for (ifa = ifaddr, n = 0; ifa != NULL; ifa = ifa->ifa_next, n++) { */
/*         if (ifa->ifa_addr == NULL) */
/*             continue; */

        /* We seek only for IPv4 addresses */
        /* if(ifa->ifa_addr->sa_family != AF_INET) */
        /*     continue; */

        /* ifa_inaddr = &(((struct sockaddr_in*) ifa->ifa_addr)->sin_addr); */
        /* if(memcmp(ifa_inaddr, &addr, sizeof(struct in_addr)) == 0) { */
            /* printf("Interface: %s\n", ifa->ifa_name); */
            /* print_pci_ids((char *)"eth0"); */
        /* } */
    /* } */
    struct pci_access *pacc= NULL;
    
    char namebuf[256] = "/sys/class/net/eth0/device/device";

    /* printf("PCI IDs: %x %x %x %x\n", vendor, device, subsystem_device, subsystem_vendor); */

    pacc = pci_alloc();
    pci_init(pacc);
    pci_scan_bus(pacc);

    pci_lookup_name(pacc, namebuf, VLA, 
                    PCI_LOOKUP_VENDOR | PCI_LOOKUP_DEVICE,
                    (unsigned long long)4332, (unsigned long long)33128);
        printf("PCI Name: %s\n", namebuf);

    pci_cleanup(pacc);

    /* freeifaddrs(ifaddr); */
    return 0;
}
/*
 *	The PCI Library -- Example of use (simplistic lister of PCI devices)
 *
 *	Written by Martin Mares and put to public domain. You can do
 *	with it anything you want, but I don't give you any warranty.
 */

/* int main(void) */
/* { */
/*   struct pci_access *pacc; */
/*   struct pci_dev *dev; */
/*   unsigned int c; */
/*   char namebuf[1024], *name; */

/*   pacc = pci_alloc();		/1* Get the pci_access structure *1/ */
/*   /1* Set all options you want -- here we stick with the defaults *1/ */
/*   pci_init(pacc);		/1* Initialize the PCI library *1/ */
/*   pci_scan_bus(pacc);		/1* We want to get the list of devices *1/ */
/*   for (dev=pacc->devices; dev; dev=dev->next)	/1* Iterate over all devices *1/ */
/*     { */
/*       pci_fill_info(dev, PCI_FILL_IDENT | PCI_FILL_BASES | PCI_FILL_CLASS);	/1* Fill in header info we need *1/ */
/*       c = pci_read_byte(dev, PCI_INTERRUPT_PIN);				/1* Read config register directly *1/ */
/*       printf("%04x:%02x:%02x.%d vendor=%04x device=%04x class=%04x irq=%d (pin %d) base0=%lx", */
/* 	     dev->domain, dev->bus, dev->dev, dev->func, dev->vendor_id, dev->device_id, */
/* 	     dev->device_class, dev->irq, c, (long) dev->base_addr[0]); */

/*       /1* Look up and print the full name of the device *1/ */
/*       name = pci_lookup_name(pacc, namebuf, sizeof(namebuf), PCI_LOOKUP_DEVICE, dev->vendor_id, dev->device_id); */
/*       printf(" (%s)\n", name); */
/*     } */
/*   pci_cleanup(pacc);		/1* Close everything *1/ */
/*   return 0; */
/* } */
