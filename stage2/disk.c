#include "disk.h"

void setupDAP(diskAdressPacket_t *dap, uint32_t blocks, 
            uint32_t offset, uint32_t segment, 
            uint32_t lba_address)
{
    dap->size = 0x16;
    dap->reserved = 0;
    dap->blocks = blocks;
    dap->offset = offset;
    dap->segment = segment;
    dap->low_address = lba_address;
    dap->high_address = 0;
    dap->null = 0;
}
