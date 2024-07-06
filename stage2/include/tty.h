#pragma once

#include "common.h"

// Macros
#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_SIZE (VGA_WIDTH * VGA_HEIGHT)

// Cursor functions
void vga_setcurpos(const uint16_t x,
                const uint16_t y);
void vga_hidecur(void);
void vga_showcur(const uint8_t start, 
                const uint8_t end);
// Output functions 
void vga_writec(char character);
void vga_writes(const char *string);
void vga_puts(const char *string);

void vga_writehex(const uint32_t number);
void vga_writeuint(const uint32_t number);

void vga_printf(const char *format, ...);
// Other
void vga_clear(void);
void vga_setpos(const uint16_t x,
                const uint16_t y);
void vga_getpos(uint16_t *x, 
                uint16_t *y);
