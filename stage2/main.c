#include "common.h"
#include "tty.h"

void __cdecl start() 
{
    vga_clear(VGA_COLOR_WHITE, VGA_COLOR_BLACK);
    vga_puts("Hello, World!\n");

    while(1) ;
}
