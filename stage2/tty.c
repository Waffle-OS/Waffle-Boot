#include "stage2.h"

// The VGA text mode buffer
static uint16_t *_vgaBuffer = (uint16_t *)0xB8000;

// Clears the screen
void vgaClear(void)
{
    size_t i;

    for(i = 0; i < VGA_SIZE; i++)
        _vgaBuffer[i] = ' ' | VGA_COLOUR;
        
    vgaSetPos(0);
}

// Scrolls the VGA text mode buffer
void vgaScroll(void)
{
    size_t i;

    for(i = VGA_WIDTH; i < VGA_SIZE; i++)
	{
        // Move every character up
		_vgaBuffer[i-VGA_WIDTH] = _vgaBuffer[i];
        // Clear the new line
        _vgaBuffer[i] = ' ' | VGA_COLOUR;
	}

	vgaSetPos(vgaGetPos() - VGA_WIDTH);
}

// Writes data to VGA
void vgaWrite(const uint16_t data,
              const VgaPosition pos)
{
    // Return if position is out of bounds
    if(pos >= VGA_SIZE)
        return;

    // Write data
    _vgaBuffer[pos] = data;
}
