ENTRY(entry)

OUTPUT_FORMAT("binary")

__stage2_loc = 0x00008000;

SECTIONS
{
    . = __stage2_loc;

    /* Defined in bootloader */
    .entry  : { 
        __entry_start = .;
        *(.entry)
        __entry_end  = .;
    }

    .text   : { 
        __text_start = .;       
        *(.text)
        __text_end = .;
    }

    .data   : { 
        __data_start = .;
        *(.data)
        __data_end = .;
    }

    .rodata : { 
        __rodata_start = .;     
        *(.rodata)  
        __rodata_end = .;
    }

    .bss    : { 
        __bss_start = .;        
        *(.bss)
        __bss_end = .;
    }
    
    __end = .;
}