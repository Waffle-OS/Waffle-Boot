#pragma once

#include "stage2.h"

/* Types */
typedef struct _DiskAdressPacket DiskAddressPacket;

/* Structs */
/**
 * @brief Disk address packet, used by the BIOS to read from the disk.
 * 
 */
struct __packed _DiskAdressPacket
{
    uint8_t     dapSize;
    uint8_t     unused;
    uint16_t    blocks;
    uint16_t    offset;
    uint16_t    segment; 
    uint32_t    lbaLow;
    uint32_t    lbaHigh;
};

/* Functions */
/**
 * @brief Reads from the disk using LBA addressing.
 * 
 * @param dap The disk address packet to use.
 * @param drive The drive of the disk to read from.
 * @return 
 */
uint32_t __cdecl    _readDiskLBA(DiskAddressPacket *dap, 
                                 uint32_t drive);
                                

