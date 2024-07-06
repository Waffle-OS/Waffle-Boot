#include "common.h"
#include "tty.h"
#include "disk.h"
#include "mmap.h"

void __cdecl main(uint32_t boot_drive) 
{
    vga_clear();
    vga_printf("WAFFLE-BOOT pre-release\n\n");
    vga_printf("Boot drive: 0x%X\n", boot_drive);
}
