#include "stage2.h"

/* IO FUNCTIONS */

// Reads a byte from port
static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile ( "inb %w1, %b0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

// Outputs byte to port
static inline void outb(uint16_t port, 
                        uint8_t val)
{
    __asm__ volatile ( "outb %b0, %w1" 
                    : 
                    : "a"(val), "Nd"(port) 
                    : "memory");
}


/* EVERYTHING ELSE*/

static bool cursorOn = true;
static VgaPosition cursorPos = 0;

// Sets cursor postion
static void _setCurPos(const VgaPosition pos)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, 
        (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, 
        (uint8_t)((pos >> 8) & 0xFF));
}

// Sets cursor postion
void vgaSetPos(const VgaPosition pos)
{
    cursorPos = pos;

}

// Gets the current cursor position
VgaPosition vgaGetPos()
{
    return cursorPos;
}

void vgaUpdateCur(void)
{
    if(cursorOn)
        _setCurPos(cursorPos);
}


// Shows the cursor and sets the start and end scanlines
void vgaShowCur(const uint8_t start, 
                const uint8_t end)
{
    outb(0x3D4, 0x0A);
    outb(0x3D5, 
         (inb(0x3D5) & 0xC0) | start);  // Set the first scanline to draw the cursor at

    outb(0x3D4, 0x0B);
    outb(0x3D5, 
         (inb(0x3D5) & 0xE0) | end);    // Set the last scanline to draw the cursor at
    
    // Cursor is now on
    cursorOn = true;
}

// Hides the cursor
void vgaHideCur(void)
{
    if(!cursorOn)
        return;

    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);

    // Cursor is now off
    cursorOn = false;
}
