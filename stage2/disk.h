#pragma once
#include "common.h"

typedef struct __attribute__((packed)) diskAdressPacket
{
    uint8_t size;
    uint8_t reserved; // Set to 0
    uint16_t blocks;
    uint16_t offset;
    uint16_t segment; 
    uint32_t low_address;
    uint16_t high_address; // Not really useful here
    uint16_t null; // Set to 0
} diskAdressPacket_t;

void setupDAP(diskAdressPacket_t *dap, uint32_t blocks, 
            uint32_t offset, uint32_t segment, 
            uint32_t low_address, uint16_t high_address);

// Returns 0 on success
uint8_t __cdecl _readDiskLBA(diskAdressPacket_t *dap, uint32_t drive);