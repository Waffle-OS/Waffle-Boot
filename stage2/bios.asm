; Contains functions which use BIOS interrupts, and must be 16-bit.
; All functions use the __cdecl calling standard.


%macro enter_pmode 0
        cli  

        mov     eax, cr0
        and     al, ~1
        mov     cr0, eax

        ; Enter protected mode
        jmp 0x08:%%pmode            ; 0x08 - 32-bit code segment


%%pmode:
        [BITS 32]
    
        ; Setup segment registers
        mov     ax, 0x10                ; 0x10 - 32-bit data segment
        mov     ds, ax
        mov     ss, ax

        sti
%endmacro



; Used by entry.asm
global puts16
; ARGS - DS:SI
; RET - void
; Only to be used in 16 bit real mode
puts16:
        [BITS 16]
        mov     AH, 0x0E
        lodsb
.loop: 
        int     0x10
        lodsb
        test    AL, AL
        jnz     .loop
.end:   
        ret

