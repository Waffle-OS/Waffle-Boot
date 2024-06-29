section .entry
global entry
extern start
extern puts16

%define NEWL 13, 10

%macro msg 1
        mov     SI, %1
        call    puts16
%endmacro

[BITS 16]

entry:
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
        or      EAX, 1
        mov     CR0, EAX
        jmp     0x08:.pmode

.pmode:
        [BITS 32]

        mov     AX, 0x10
        mov     DS, AX
        mov     SS, AX

        call    start
        cli
        hlt

        jmp     $

%include "misc/a20.asm"

%include "misc/gdt.asm"
