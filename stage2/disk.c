#include "disk.h"

void setupDAP(diskAdressPacket_t *dap, uint32_t blocks, 
            uint32_t offset, uint32_t segment, 
            uint32_t low_address, uint16_t high_address)
{
    dap->blocks = blocks;
    dap->offset = offset;
    dap->segment = segment;
    dap->low_address = low_address;
    dap->high_address = high_address;
}
