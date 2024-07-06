#include <stdarg.h>
#include "tty.h"

// Converts unsigned integer to a string
static void utoa(char buffer[static 9],
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

// Writes a hexadecimal string to VGA
void vga_writehex(const uint32_t number)
{
    char buffer[9];
    utoa(buffer, number, 16);
    vga_writes(buffer);
}

// Writes an integer to VGA
void vga_writeuint(const uint32_t number)
{
    char buffer[11];
    utoa(buffer, number, 10);
    vga_writes(buffer);
}

// Implementation of printf - code could be better, but it works so whatever
void vga_printf(const char *format, ...)
{
    va_list ap;
    size_t i;

    va_start(ap, format);

    for(i = 0; format[i]; i++)
    {
        if(format[i] != '%')
        {
            vga_writec(format[i]);
            continue;
        }

        switch(format[i+1])
        {
            case 'U': case 'd':
                vga_writeuint(va_arg(ap, uint32_t));
                i++;
                break;
            case 'X': case 'x':
                vga_writehex(va_arg(ap, uint32_t));
                i++;
                break;
            case 'c':
                vga_writec(va_arg(ap, int));
                i++;
                break;
            case 's':
                vga_writes(va_arg(ap, char*));
                i++;
                break;

            default:
                vga_writec('%');
        }   

    }

    uint16_t x, y;
    vga_getpos(&x, &y);
    vga_setcurpos(x, y);

    va_end(ap);
}
