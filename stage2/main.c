#include "common.h"
#include "tty.h"

#define PRINT_DATA_HEX(name, data) vga_puts(name); vga_puthex(data); vga_putch('\n')

void __cdecl start(uint32_t boot_drive) 
{
    test();
    vga_clear(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_puts("WAFFLE-BOOT pre-release 0\n");
    PRINT_DATA_HEX("boot drive: 0x", boot_drive);

    while(1) ;
}
