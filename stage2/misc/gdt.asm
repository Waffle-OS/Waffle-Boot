
gdt_start:
        .null:
                dq 0
        .code_32:
                dw 0xFFFF               ; Lower limit
                dw 0                   
                db 0                    ; Lower base
                db 0x9A                 ; Access byte  
                db 0xCF                 ; Other flags + Higher limit
                db 0                    ; Higher base
        .data_32:
                dw 0xFFFF
                dw 0
                db 0
                db 0x92
                db 0xCF
                db 0
        .code_16:
                dw 0xFFFF     
                dw 0                   
                db 0                 
                db 0x9A           
                db 0x0F             
                db 0                  
        .data_16:
                dw 0xFFFF
                dw 0
                db 0
                db 0x92
                db 0x0F
                db 0

.desc:
        dw .desc - gdt_start - 1
        dd gdt_start
        