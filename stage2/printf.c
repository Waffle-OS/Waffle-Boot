#include <stdarg.h>
#include "tty.h"

// Writes a character to VGA
static void _vgaWritec(const char c)
{
    const VgaPosition pos = vgaGetPos();
    switch (c)
    {
        case '\n':
            vgaSetPos(pos + (VGA_WIDTH - GET_POS_X(pos)));
            break;
        case '\r':
            vgaSetPos(pos - GET_POS_X(pos));
            break;
        case '\t':
            vgaSetPos(pos + (8 - (GET_POS_X(pos) % 8)));
            break;
        case '\b':
            vgaSetPos(pos - 1);
            break;
    
        default:
            vgaWrite(c | VGA_COLOUR, pos);
            vgaSetPos(pos + 1);
            break;
    }

    if(vgaGetPos() >= (VGA_SIZE-VGA_WIDTH))
        vgaScroll();
}

// Writes a string to VGA
static void _vgaWrites(const char *s)
{
    while(*s)
        _vgaWritec(*s++);
}


// Converts unsigned integer to a string
static void _utoa(char *buffer,
                  uint32_t number, 
                  const uint8_t base)
{
    static const char *nums = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    size_t i = 0, j;

    // Convert to string, in reverse order
    do
    {
        buffer[i++] = nums[number % base];
        number /= base;
    } while(number);

    buffer[i] = '\0';

    // Reverse string
    for(j = 0, i--; j < i; j++, i--)
    {
        const char c = buffer[j];
        buffer[j] = buffer[i];
        buffer[i] = c;
    }
}


// Writes a hexadecimal number to VGA
static void _vgaWriteHex(const uint32_t number)
{
    char buffer[9];
    _utoa(buffer, number, 16);
    _vgaWrites(buffer);
}

// Writes an unsigned integer to VGA
static void _vgaWriteUint(const uint32_t number)
{
    char buffer[11];
    _utoa(buffer, number, 10);
    _vgaWrites(buffer);
}


// Implementation of printf
void vgaPrintf(const char *format, 
               ...)
{
    va_list ap;
    size_t i;

    va_start(ap, format);

    for(i = 0; format[i]; i++)
    {
        if(format[i] != '%')
        {
            _vgaWritec(format[i]);
            continue;
        }

        switch(format[i+1])
        {
            case 'u': case 'd':
                _vgaWriteUint(va_arg(ap, uint32_t));
                i++;
                break;
            case 'X': case 'x':
                _vgaWriteHex(va_arg(ap, uint32_t));
                i++;
                break;
            case 'c':
                _vgaWritec(va_arg(ap, int));            // char promotes to int 
                i++;
                break;
            case 's':
                _vgaWrites(va_arg(ap, char*));
                i++;
                break;

            default:
                _vgaWritec('%');
        }   

    }

    vgaUpdateCur();

    va_end(ap);
}
