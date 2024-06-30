#include "common.h"
#include "tty.h"
#include "disk.h"


void __cdecl main(uint32_t boot_drive) 
{
    vga_clear(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_puts("WAFFLE-BOOT pre-release 0\n");
    vga_puts("Boot drive: 0x");
    vga_puthex(boot_drive);

    diskAdressPacket_t *dap = 0x500;
    dap->size = 0x10;
    dap->reserved = 0;
    dap->null = 0;

    setupDAP(dap, 1, 0x7000, 0, 0, 0);


    if(_readDiskLBA(&dap, boot_drive))
        return;

    const uint8_t* data = (uint8_t*)0x7000;
    const uint8_t* boot = (uint8_t*)0x7C00;

    for(int i = 0; i < 512; i++)
    {
        if(data[i] != boot[i])
            return;
    }

    vga_puts("successful read");

    return;
}
