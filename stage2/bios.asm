; Contains functions which use BIOS interrupts, and must be 16-bit.
; All functions use the __cdecl calling standard.


; Enters real mode
%macro enter_rmode 0
        [BITS 32]

        jmp     0x18:%%pmode16          ; 0x18 - 16-bit code segment

%%pmode16:
        [BITS 16]

        cli
        mov     EAX, CR0
        and     AL, 0xFE
        mov     CR0, EAX

        ; Enter real mode
        jmp word 00h:%%rmode            ; 0 - No segment  

%%rmode:
        ; Setup segment registers
        mov     AX, 0                   ; 0 - No segment
        mov     DS, AX
        mov     SS, AX

        sti
%endmacro 

; Enters protected mode
%macro enter_pmode 0
        [BITS 16]

        cli  
        mov     EAX, CR0
        or      AL, 1
        mov     CR0, EAX

        ; Enter protected mode
        jmp     0x08:%%pmode            ; 0x08 - 32-bit code segment


%%pmode:
        [BITS 32]
    
        ; Setup segment registers
        mov     AX, 0x10                ; 0x10 - 32-bit data segment
        mov     DS, AX
        mov     SS, AX

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

global test
test:
        [BITS 32]
        enter_rmode
        enter_pmode
        enter_rmode
        enter_pmode
        ret
