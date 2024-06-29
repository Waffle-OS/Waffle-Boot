;----------
; STAGE 2 BOOTLOADER
;----------
[BITS 16]
[ORG 0x7E00]


%include "misc/utils.asm"

stage2:
        mov     [drive_num], DL
        mov     SI, stage2_load_msg
        call    puts
        jmp     a20


%include "misc/a20.asm"
; Enables A20 line
a20:
        call    enable_a20
        jc     .error
        mov    SI, a20_enable_msg
        call    puts
        jmp     get_mmap

.error:
        mov    SI, a20_fail_msg
        call    puts
        perm_halt


%define MAGIC_NUM 0x534D4150
%define MMAP_LOC 0x5008
; Gets memory map
get_mmap:
        clc
        mov     EAX, 0xE820
        mov     EBX, 0
        mov     DI, MMAP_LOC                     
        mov     ECX, 24
        mov     EDX, MAGIC_NUM
        int     0x15
        jc      .error
        add     DI, 24

.loop:
        test    EBX, EBX
        jz      .add_info
        mov     EAX, 0xE820
        mov     ECX, 24
        mov     EDX, MAGIC_NUM
        int     0x15
        add     DI, 24
        jmp    .loop

.error:
        mov    SI, mmap_fail_msg
        call    puts
        perm_halt

.add_info:
        mov     [0x5004], DI                     ; Memory map info stored at 0x5000
        mov     SI, get_mmap_msg
        call    puts

        mov     DI, MMAP_LOC

.get_mmap_entry:
        ; Gets first mmap entry starting from 0x100000
        
        add     DI, 24
        cmp     DI, [0x5004]
        je      .too_low_mem
        mov     EAX, [DI]
        cmp     EAX, 0x100000
        jne     .get_mmap_entry

.check_mem:
        ; Check if there is sufficient memory
        
        mov     EAX, [DI+16]
        cmp     EAX, 1
        jne     .too_low_mem
        

        mov     EAX, [DI+8]
        cmp     EAX, 0x100000
        jl      .too_low_mem

.success:
        mov     SI, sufficient_mem_msg 
        call    puts
        jmp     get_kernel_loc

.too_low_mem:
        ; Insufficient memory
        mov     SI, too_low_mem_msg
        call    puts
        perm_halt

%include "misc/fat12_data.asm"

; Gets kernel location on disk
get_kernel_loc:
        ; Load root directory
        mov     AH, 0x42
        mov     DL, [drive_num]
        mov     SI, rootdir_lba_packet
        int     0x13
        jc      .error

        mov     DI, 0x1000
        mov     CX, 16
.find_rde:
        ; Find root directory entry of kernel

        push    CX 
        mov     CX, 11 
        mov     SI, kernel_filename 
        push    DI 
        repe    cmpsb 
        pop     DI 
        je      .get_current_cluster 
        pop     CX 
        add     DI, 32
        loop    .find_rde 
        jmp     .error

.get_current_cluster:
        ; Get the first cluster the kernel is stored in
        pop     CX

        mov     DX, [DI+26]
        mov     [current_cluster], DX
        
.load_fat:
        ; Loads the FAT


        mov     AH, 0x42
        mov     DL, [drive_num]
        mov     SI, fat_lba_packet
        int     0x13
        jnc     load_kernel

.error:
        mov    SI, kernel_loc_fail_msg
        call    puts
        perm_halt


load_kernel:
        ; Loads the kernel
        
        ;;
        ;;
        ;;; TODO: Load kernel
        ;;
        ;;

        
        perm_halt

%include "misc/text_mode.asm"


;----------
; DATA
;----------

drive_num: db 0
current_cluster: dw 0

stage2_load_msg: db "Successfully loaded stage 2 bootloader.", NEWL, 0

a20_enable_msg: db "Successfully enabled A20 line.", NEWL, 0
a20_fail_msg: db "Unable to enable A20 line.", NEWL, 0

get_mmap_msg: db "Successfully obtained memory map.", NEWL, 0
mmap_fail_msg: db "Unable to obtain memory map.", NEWL, 0
too_low_mem_msg: db "Insufficient memory (2MiB needed to boot).", NEWL, 0
sufficient_mem_msg: db "Sufficient memory to boot.", NEWL, 0

kernel_filename: db "KERNEL  BIN"
kernel_loc_fail_msg: db "Unable to obtain kernel location (file system corrupt?).", NEWL, 0
kernel_failed_load_msg: db "Unable to load kernel.", NEWL, 0

rootdir_lba_packet:
        .size:          db 0x10
        .reserved:      db 0
        .blocks:        dw 1
        .offset:        dw 0x1000
        .segment:       dw 0
        .low_address:   dd ROOTDIR_SECTOR       ; Low 32 bits of address
        .high_address:  dw 0                    ; High 16 bits of address
        .null:          dw 0

fat_lba_packet:
        .size:          db 0x10
        .reserved:      db 0
        .blocks:        dw 9
        .offset:        dw 0x1000
        .segment:       dw 0
        .low_address:   dd FAT_LOCATION         ; Low 32 bits of address
        .high_address:  dw 0                    ; High 16 bits of address
        .null:          dw 0


kernel_lba_packet:
        .size:          db 0x10
        .reserved:      db 0
        .blocks:        dw 1
        .offset:        dw 0
        .segment:       dw 0x1000
        .low_address:   dd 23                   ; Low 32 bits of address
        .high_address:  dw 0                    ; High 16 bits of address
        .null:          dw 0
