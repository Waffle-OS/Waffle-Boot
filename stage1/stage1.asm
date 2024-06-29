;----------
; STAGE 1 BOOTLOADER
;----------
[BITS 16]
[ORG 0x7C00]
%define NEWL 13, 10

%macro msg 1
        mov     SI, %1
        call    puts
%endmacro

jmp short boot
nop
%include "fat.asm"

boot:
        cli
        ; Set up stack and segments
        mov     SP, 0x8000
        mov     BP, SP
        xor     AX, AX
        mov     DS, AX
        mov     ES, AX
        mov     FS, AX
        mov     SS, AX

        sti 

        jmp     0x0000:stage1

stage1:
        cld

        ; Save boot drive
        push    DX

        ; Enter VGA mode 3 (80x25 text, 16 colours)
        mov     AH, 0x00
        mov     AL, 0x03
        int     0x10

.load_stage2:
        ; Check presence of LBA extensions
        mov     AH, 0x41
        mov     BX, 0x55AA
        int     0x13
        jc      .error                  

        ; Read stage 2 from disk
        mov     AH, 0x42
        mov     SI, lba_packet
        int     0x13
        jnc     0x8000                          ; Jump to stage 2 if no errors

        msg     stage2_fail
.error:
        msg     reboot_msg

        mov     AH, 0
        int     0x16

        jmp     0xFFFF:0

stage2_fail: db 'Failed to load stage 2.', NEWL, 0
reboot_msg: db 'Press any key to restart. ', NEWL, 0

; SI - Pointer to null-terminated string
puts:
        mov     AH, 0x0E
        lodsb
.loop: 
        int     0x10
        lodsb
        test    AL, AL
        jnz     .loop
.end:   
        ret


; Stage 2 LBA packet
lba_packet:
        .size:          db 0x10
        .reserved:      db 0
        .blocks:        dw (RESERVED_SECTS-1)
        .offset:        dw 0x8000
        .segment:       dw 0
        .low_address:   dd 1
        .high_address:  dw 0
        .null:          dw 0


; Boot signature
times 510-($-$$) db 0
dw 0xaa55
