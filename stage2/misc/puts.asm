; Used only by entry.asm
[BITS 16]

; ARGS - DS:SI
; RET - void
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
