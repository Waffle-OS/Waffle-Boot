#include "common.h"
#include "tty.h"
#include "disk.h"
#include "bios.h"

#define PRINT_DATA_HEX(name, data) vga_puts(name); vga_puthex(data); vga_putch('\n')

diskAdressPacket_t dap;

void __cdecl start(uint32_t boot_drive) 
{
    vga_clear(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_puts("WAFFLE-BOOT pre-release 0\n");
    PRINT_DATA_HEX("boot drive: 0x", boot_drive);

    setupDAP(&dap, 1, 0x7000, 0, 0);


    if(_readDiskLBA(&dap, boot_drive))
        goto halt;

    const uint8_t* data = (uint8_t*)0x7000;
    const uint8_t* boot = (uint8_t*)0x7C00;

    for(int i = 0; i < 512; i++)
    {
        if(data[i] != boot[i])
            goto halt;
    }

    vga_puts("successful read");

    halt:
    while(1) ;
}
