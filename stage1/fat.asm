%define SECTORS_PER_FAT 9
%define NUM_FATS        2
%define RESERVED_SECTS  65
; 14 sectors, times 12 for 224 entries
%define RD_SIZE        (14*16)

FAT12:
        db      "MSWIN4.1"      ; OEM identifier
        dw      512             ; Bytes per sector 
        db      1               ; Sectors per cluster
        dw      RESERVED_SECTS  ; Reserved sectors (for bootloader)
        db      2               ; Number of FATs
        dw      RD_SIZE        ; Root directory entries
        dw      0x0b40          ; Total sectors in the logical volume
        db      0xf0            ; Media descriptor type
        dw      SECTORS_PER_FAT ; Sectors per FAT
        dw      18              ; Sectors per track
        dw      2               ; Heads on the disk
        dd      0               ; Number of hidden sectors
        dd      0               ; Number of large sectors
        db      0x00            ; Drive number (for DOS, useless here)   
        db      0x00            ; NT flag
        db      0x29            ; Signature
        dd      0xBC095A01      ; Volume serial ID 
        db      "WAFFLE OS  "   ; Volume label string
        db      "FAT12   "      ; System identifier (useless)