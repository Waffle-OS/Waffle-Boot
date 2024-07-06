#include "tty.h"

static bool cursorOn = true;

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

static inline void outb(uint16_t port, uint8_t val)
{
    __asm__ volatile ( "outb %b0, %w1" 
                    : 
                    : "a"(val), "Nd"(port) 
                    : "memory");
}

// Sets cursor postion
void vga_setcurpos(const uint16_t x,
                const uint16_t y)
{
    if(!cursorOn)
        return;

    const uint16_t pos = y * VGA_WIDTH + x;

    outb(0x3D4, 0x0F);
    outb(0x3D5, 
        (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, 
        (uint8_t)((pos >> 8) & 0xFF));
}

// Shows the cursor and sets the start and end scanlines
void vga_showcur(const uint8_t start, 
                    const uint8_t end)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 
        (inb(0x3D5) & 0xC0) | start);   // Set the first scanline to draw the cursor at

    outb(0x3D4, 0x0B);
    outb(0x3D5, 
        (inb(0x3D5) & 0xE0) | end);    // Set the last scanline to draw the cursor at
}

// Hides the cursor
void vga_hidecur(void)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}
