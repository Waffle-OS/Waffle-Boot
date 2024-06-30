; Stuff useful for interfacing with BIOS

; Enters real mode
%macro enter_rmode 0
        [BITS 32]

        jmp     0x18:%%pmode16          ; 0x18 - 16-bit code segment

%%pmode16:
        [BITS 16]

        cli 
        ; ECX is used instead of EAX because EAX usually holds important data
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
