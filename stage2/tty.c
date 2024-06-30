#include "tty.h"

size_t terminal_row;
size_t terminal_column;
uint8_t terminal_color;
uint16_t *tty_buffer = (uint16_t *)0xB8000;

static inline uint8_t vga_color_entry(VGA_COLOR fg, VGA_COLOR bg)
{
    return (fg | bg << 4);
}

static inline uint16_t vga_entry(char character, uint8_t color_entry)
{
    return (uint16_t) character | (uint16_t) color_entry << 8;
}

// Clears the screen to the specified colours
void vga_clear(VGA_COLOR fg, VGA_COLOR bg)
{  
    terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_color_entry(fg, bg);
	for (size_t y = 0; y < VGA_HEIGHT; y++) 
    {
		for (size_t x = 0; x < VGA_WIDTH; x++) 
        {
			const size_t index = (y * VGA_WIDTH) + x;
			tty_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

// Scrolls the terminal down
void terminal_scroll(void)
{
	for(int i = VGA_WIDTH; i < (VGA_WIDTH*VGA_HEIGHT); i++)
	{
		tty_buffer[i-VGA_WIDTH] = tty_buffer[i];
		tty_buffer[i] = vga_entry(' ', terminal_color);
	}
	terminal_row--;
}

// Writes a character to VGA
static void vga_writech(char character)
{
    const size_t index = (terminal_row * VGA_WIDTH) + terminal_column;

	switch (character)
	{
        case '\n':
            if (++terminal_row == VGA_HEIGHT)
                terminal_scroll();
            terminal_column = 0;
            return;
        default:
            tty_buffer[index] = vga_entry(character, terminal_color);
	}

	if (++terminal_column == VGA_WIDTH) 
    {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
		{
			terminal_scroll();
			terminal_row -= 2;
		}
	}
}

// Prints a character to VGA
void vga_putch(char character)
{
	vga_writech(character);
}

// Prints a string to VGA
void vga_puts(char *string)
{
	for(size_t i = 0; string[i]; i++)
	{
		vga_writech(string[i]);
	}
}

// Converts a hexadecimal number to a string
static void hex_to_string(uint32_t number, char converted[9])
{
	const char hexnums[] = "0123456789ABCDEF";
	char buffer[9];
	size_t i = 0;

	do
	{
		buffer[i] = hexnums[number & 0xF];
		i++;
		number /= 16;
	} while (number);

	for(int j = i - 1; j >= 0; j--)
	{
		converted[i - 1 - j] = buffer[j];
	}

	converted[i] = '\0';
}

// Prints a hexadecimal number to VGA.
void vga_puthex(uint32_t number)
{
    char converted[9];
    hex_to_string(number, converted);
    vga_puts(converted);
}
