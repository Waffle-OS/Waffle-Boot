#include "stage2.h"

#define KERNEL_PHYS_LOC 0x00100000
#define KERNEL_VIRT_LOC 0xC0100000

void __cdecl main(uint16_t boot_drive) 
{
    /* INITIALISATION */
    vgaClear();
    printf("WAFFLE-BOOT PRE-RELEASE\n\n");

    // Print boot drive
    printf("Boot drive: 0x%X\n", boot_drive);

    /* GET MEMORY MAP */
    MemMap mmap = (AddrRangeDesc *)0x500;       // Memory map located at physical address 0x500
    const size_t mmap_size = _getMmap(mmap);    // Passed as argument to kernel main

    // Size of 0 means no memory map
    if(!mmap_size)
    {
        printf("Unable to get memory map\n");
        return;
    }

    printf("%u entries\n", mmap_size);

    // Get high memory

    const uint32_t highmem = getHighMem(mmap, mmap_size);
    printf("High memory: %uMiB, %uKiB\n", highmem/MEBIBYTE, (highmem%MEBIBYTE)/KIBIBYTE);

    /* LOAD KERNEL */



    // TODO

    return;
}


