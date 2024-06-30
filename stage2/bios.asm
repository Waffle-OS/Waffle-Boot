; Contains functions which use BIOS interrupts, and must be 16-bit.
; All functions use the __cdecl calling standard.

; Enters real mode
%macro enter_rmode 0
        [BITS 32]

        jmp     0x18:%%pmode16          ; 0x18 - 16-bit code segment

%%pmode16:
        [BITS 16]

        cli 
        mov     ECX, CR0
        and     CL, 0xFE
        mov     CR0, ECX

        ; Enter real mode
        jmp     0:%%rmode               ; 0 - No segment  

%%rmode:
        ; Setup segment registers
        mov     CX, 0                   ; 0 - No segment
        mov     DS, CX
        mov     SS, CX

        sti
%endmacro 

; Enters protected mode
%macro enter_pmode 0
        [BITS 16]

        cli  
        ; Uses ECX instead of EAX because EAX holds some important info usually
        mov     ECX, CR0
        or      CL, 1
        mov     CR0, ECX

        ; Enter protected mode
        jmp     0x08:%%pmode            ; 0x08 - 32-bit code segment


%%pmode:
        [BITS 32]
    
        ; Setup segment registers
        mov     CX, 0x10                ; 0x10 - 32-bit data segment
        mov     DS, CX
        mov     SS, CX

%endmacro


section .text

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
        mov     EDX, [EBP+12]
        mov     ESI, [EBP+8]

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
