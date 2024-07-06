#include <stdarg.h>
#include "tty.h"
 

static size_t vga_row = 0;
static size_t vga_column = 0;
static const uint16_t vga_colour = 0x0F00; // Black bg and white fg
static uint16_t *vga_buffer = (uint16_t *)0xB8000;

// Clears the screen
void vga_clear(void)
{
    size_t pos;

    for(pos = 0; pos < VGA_SIZE; pos++)
        vga_buffer[pos] = ' ' | vga_colour;
        
    vga_row = 0;
    vga_column = 0;
}

// Scrolls the VGA text mode buffer
static void vga_scroll(void)
{
    size_t i;

    for(i = VGA_WIDTH; i < VGA_SIZE; i++)
	{
		vga_buffer[i-VGA_WIDTH] = vga_buffer[i];
        vga_buffer[i] |= ' ';
	}
	vga_row--;
}

// Writes a character to VGA
void vga_writec(const char character)
{
    const size_t vga_index = vga_row * VGA_WIDTH + vga_column;
    switch(character)
    {
        case '\n':
            vga_column = 0;
            vga_row++;
            break;
        case '\t':
            vga_column += 4 - (vga_column % 4);
            break;

        default:
            vga_buffer[vga_index] = character | vga_colour;
            vga_column++;
    }

    if(vga_column >= VGA_WIDTH)
    {
        vga_column = 0;
        vga_row++;
    }
    if(vga_row == VGA_HEIGHT)
        vga_scroll();
}

// Writes a string to VGA
void vga_writes(const char *string)
{
    size_t i;

    for(i = 0; string[i]; i++)
    {
        vga_writec(string[i]);
    }
}

// Prints a string to VGA
void vga_puts(const char *string)
{
    vga_writes(string);
    vga_setcurpos(vga_column, vga_row);
}

// Gets the current position
void vga_getpos(uint16_t *x, uint16_t *y)
{
    *x = vga_column;
    *y = vga_row;
}

// Sets the position
void vga_setpos(const uint16_t x, const uint16_t y)
{
    vga_column = x;
    vga_row = y;
    vga_setcurpos(x, y);
}
