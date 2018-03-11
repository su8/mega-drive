#include <stdio.h>
#include <pci/pci.h>
#define VLA 200
int main(void) {
  struct pci_access *pacc= NULL;
  char temp[VLA];
  pacc = pci_alloc();
  pci_init(pacc);
    pci_lookup_name(pacc, temp, VLA, 
                    PCI_LOOKUP_VENDOR | PCI_LOOKUP_DEVICE,
                    4332, 33128);
        printf("PCI Name: %s\n", temp);
  if (NULL != pacc) {
    pci_cleanup(pacc);
  }
  return 0;
}
