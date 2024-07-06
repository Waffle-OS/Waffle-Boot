#pragma once

#include "common.h"

typedef struct __attribute__((packed)) mmapPacket
{
    uint32_t low_address;
    uint32_t high_address;
    uint32_t low_length;
    uint32_t high_length;
    uint32_t type;
    uint32_t acpi_attr;
} mmapPacket_t;

typedef struct __attribute__((packed)) mmapInfo
{
    size_t size;
    uint32_t reserved;  // Useless for now
} mmapInfo_t;

// Returns 0 on success
uint8_t __cdecl _getMmap(mmapPacket_t *mmap,        // Pointer to desired location of memory map. Must be below 0xFFFF.
                         mmapInfo_t *mmap_info);    // Function places any extra info in this struct.
