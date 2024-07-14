#include "memory.h"

uint32_t getHighMem(const MemMap mmap,
                    const size_t size)
{
    size_t i;
    uint32_t highmem = 0;

    // Skip entries below 0x100000
    for (i = 0;
        mmap[i].baseAddrLow < 0x100000; 
        i++) ;
    
    // Get sum of length of all usable entries
    for (; i < size; i++)
    {
        const uint32_t length = mmap[i].lengthLow;
        highmem += length;
    }

    return highmem;
}
