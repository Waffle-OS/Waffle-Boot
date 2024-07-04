#include "common.h"
#include "tty.h"
#include "disk.h"
#include "mmap.h"

void __cdecl main(uint32_t boot_drive) 
{
    vga_clear(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_puts("WAFFLE-BOOT pre-release 0\n");
    vga_puts("Boot drive: 0x");
    vga_puthex(boot_drive);

    mmapPacket_t *mmap = (mmapPacket_t *)0x500;
    mmapInfo_t *mmap_info = (mmapInfo_t *)0x1000;

    if(_getMmap(mmap, mmap_info))
        vga_puts("\nFailed to get memory map\n");
    else
        vga_puts("\nGot memory map\n");

    vga_puthex(mmap_info->size);
    return;
}
