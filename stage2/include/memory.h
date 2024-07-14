#pragma once

#include "stage2.h"

/* Macros */
#define KIBIBYTE    1024
#define MEBIBYTE    (KIBIBYTE * 1024)

/* Types */
typedef enum _AddrType          AddrType;       // Address range type
typedef struct  _AddrRangeDesc  AddrRangeDesc;  // Address range descriptor
typedef AddrRangeDesc*          MemMap;         // Pointer to address range descriptors

/* Enums */

/**
 * @brief Address range type of an address range descriptor
 * 
 */
enum _AddrType
{
    ADDR_MEMORY = 1, ADDR_RESERVED,
    ADDR_ACPI, ADDR_NVS, ADDR_UNUSABLE,
    ADDR_DISABLED, ADDR_PERSISTENT
};

/* Structs */

/**
 * @brief Memory map packet, as described in the ACPI spec
 * (https://uefi.org/htmlspecs/ACPI_Spec_6_4_html/15_System_Address_Map_Interfaces/Sys_Address_Map_Interfaces.html)
 * 
 */
struct __packed _AddrRangeDesc
{
    uint32_t    baseAddrLow;    // Lower 32 bits of address
    uint32_t    baseAddrHigh;   // Upper 32 bits of address
    uint32_t    lengthLow;      // Lower 32 bits of length
    uint32_t    lengthHigh;     // Upper 32 bits of length
    uint32_t    type;           // Type of memory
    uint32_t    extAttr;        // ACPI extended attributes
};

/* Functions */

/**
 * @brief Gets a memory map from the BIOS
 * 
 * @param mmap Pointer to desired location of memory map
 * @return Size of memory map, or 0 on failure
 */
size_t __cdecl  _getMmap(MemMap mmap);

/**
 * @brief Gets the total amount of high memory
 * 
 * @param mmap The memory map
 * @param size The size of the memory map
 * @return uint32_t Amount of high memory
 */
uint32_t        getHighMem(const MemMap mmap,
                           const size_t size);
