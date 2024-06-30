; Disk related assembly functions
%include "misc/bios.asm"

section .text

; Used to read from disk
global _readDiskLBA
; ARGS - pointer to disk address packet (must not be greater than 0xFFFF), drive number (uint32_t)
_readDiskLBA:
        [BITS 32]
        ; Create new strack frame
        push    EBP
        mov     EBP, ESP
        ; Save registers
        push    ESI

        ; Set up disk read
        mov     EDX, [EBP+12]                ; Drive number
        mov     ESI, [EBP+8]                 ; Pointer to disk address packet

        enter_rmode
.rmode:
        [BITS 16]
        mov     AH, 0x42
        int     0x13
        jc      .end
        xor     EAX, EAX
.end:
        enter_pmode

        [BITS 32]
        ; Restore registers and stack frame
        pop     ESI
        pop     EBP

        ret
