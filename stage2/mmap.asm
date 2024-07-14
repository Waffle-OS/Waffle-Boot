%include "misc/bios.asm"

section .text

global _getMmap
; Gets a memory map from the BIOS
_getMmap:
        [BITS 32]
        ; Create new strack frame
        push    EBP
        mov     EBP, ESP
        ; Save registers
        push    ESI
        push    EDI
        push    EBX

        mov     EDI, [EBP+8]
        mov     ESI, [EBP+12]

        enter_rmode
.get_mmap:
        ; Clear ES
        xor     AX, AX
        mov     ES, AX
        ; Get memory map
%define MAGIC_NUM 0x534D4150

        clc
        mov     EAX, 0xE820    
        mov     EBX, 0                  ; 0 indicates that it is the first entry we want. 
                                        ; BIOS will change it to some other value to indicate which entry is next.
        mov     ECX, 24                 ; Entry is 24 bytes long
        mov     EDX, MAGIC_NUM          ; Magic number :O (just SMAP in ASCII)
        int     0x15

        jc      .error
        or      EBX, EBX
        jz      .error                  ; Single element memory map - useless
        
        ; Force a valid ACPI entry
        mov     [DI+20], dword 1

        add     DI, 24

.loop:
        mov     EAX, 0xE820
        ; Ask for 24 bytes
        mov     ECX, 24
        mov     EDX, MAGIC_NUM
        int     0x15
        ; Force a valid ACPI entry
        mov     [DI+20], dword 1
        ; Check if we've reached the end
        jc      .finish
        or      EBX, EBX
        jz      .finish
        add     DI, 24
        jmp    .loop

.error:
        ; Memory map size of 0
        xor     EAX, EAX
        jmp     .end
.finish:
        ; Return number of memory map entries
        mov     EAX, EDI
        sub     EAX, [EBP+8]
        shr     EAX, 4
        sub     EAX, 1
.end:
        enter_pmode
        
        ; Restore registers
        pop EBX
        pop EDI
        pop ESI
        ; Restore stack frame
        pop EBP
        ret
