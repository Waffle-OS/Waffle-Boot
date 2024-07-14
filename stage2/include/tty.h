#pragma once

#include "stage2.h"

/* Macros */
#define     VGA_WIDTH       80
#define     VGA_HEIGHT      25
#define     VGA_SIZE        (VGA_WIDTH * VGA_HEIGHT)
#define     VGA_COLOUR      0x0F00

/* Types */
#define     CALC_VGA_POS(x, y)      ((y * VGA_WIDTH) + x)
#define     GET_POS_X(pos)          (pos % VGA_WIDTH)
#define     GET_POS_Y(pos)          (pos / VGA_WIDTH)
typedef uint32_t            VgaPosition;


/* Functions */
#define     printf(...)     vgaPrintf(__VA_ARGS__)
/**
 * @brief Prints a formatted string to VGA.
 * 
 * @param format The string.
 * @param ... 
 */
void        vgaPrintf      (const char      *format, 
                            ...);

/**
 * @brief Clears VGA text mode buffer.
 * 
 */
void        vgaClear       (void);

/**
 * @brief Sets the position of the cursor.
 * 
 * @param x Column to place cursor in.
 * @param y Row to place cursor in.
 */
void        vgaSetPos      (const VgaPosition   pos);
/**
 * @brief Gets the current position of the cursor in the VGA.
 * 
 * @return The position of the cursor.
 */
VgaPosition vgaGetPos      (void);

/**
 * @brief Updates VGA cursor position
 * 
 */
void        vgaUpdateCur   (void);

/**
 * @brief Shows thes VGA cursor.
 * 
 * @param start The start scanline of the cursor.
 * @param end The end scanline of the cursor.
 */
void        vgaShowCur     (const uint8_t   start, 
                            const uint8_t   end);
/**
 * @brief Hides the VGA cursor.
 * 
 */
void        vgaHideCur     (void);

/**
 * @brief Scrolls the VGA text mode buffer down.
 * 
 */
void        vgaScroll      (void);

/**
 * @brief Writes data to the VGA textmode buffer.
 * 
 * @param data The data to write.
 * @param pos The position to write to.
 */
void        vgaWrite       (const uint16_t      data,
                            const VgaPosition   pos);
