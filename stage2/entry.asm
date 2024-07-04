section .entry
global entry
extern main

%define NEWL 13, 10

%macro msg 1
        mov     SI, %1
        call    puts16
%endmacro


entry:
        [BITS 16]
        ; Set up some stuff before calling start
        pop     DX
        and     EDX, 0xFF
        push    EDX
.a20_line:
        ; Enable A20 line
        call    enable_a20
        jnc     .enter_pmode

        msg     .a20_fail
        jmp     $

.a20_fail: db 'Failed to enable A20 line.', NEWL, 0

.enter_pmode:
        ; Enter protected mode
        cli
        lgdt    [gdt_start.desc]
        mov     EAX, CR0
        or      AL, 1
        mov     CR0, EAX
        jmp     0x08:.pmode

.pmode:
        [BITS 32]

        mov     AX, 0x10
        mov     DS, AX
        mov     SS, AX
        xor     AX, AX
        mov     ES, AX
        mov     FS, AX
        mov     GS, AX

; Defined in linker script
extern __bss_start
extern __bss_end
        ; Clear BSS - C standard mandates that BSS has been intitialised to 0
        mov     EDI, __bss_start
        mov     ECX, __bss_end
        sub     ECX, EDI
        xor     AL, AL
        cld
        rep     stosb

        call    main
.halt:
        cli
        hlt
        jmp     .halt

; Other stuff

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

%include "misc/a20.asm"

section .data
%include "misc/gdt.asm"
