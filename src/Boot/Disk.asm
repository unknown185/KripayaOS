;
;  Disk.asm
;  KripayaOS
;
;  Created by Ashwin Paudel on 2021-05-31.
;


; ES:BX should be loaded with 'dh' sectors from drive 'dl'.
DiskLoad:
    pusha
    ; We'll overwrite our input parameters from 'dx' since reading from disc necessitates setting particular values in all registers. Let's add it to the stack so we can use it later.
    push dx
    ; We're gonna get 'ah' (Interrupt 0x13 function) to be equal to 0x02 which means readable.
    mov ah, 0x02
    ; Set 'al' equal to 'dh' (number of sectors to read (0x01 .. 0x80))
    mov al, dh
    ; cl <- sector (0x01 .. 0x11)
    ; 0x01 is our boot sector, 0x02 is the first 'available' sector
    mov cl, 0x02
    ; ch <- cylinder (0x0 .. 0x3FF, upper 2 bits in 'cl')
    ; dl <- drive number. Our caller sets it as a parameter and gets it from BIOS
    ; (0 = floppy, 1 = floppy2, 0x80 = hdd, 0x81 = hdd2)
    mov ch, 0x00
    ; dh <- head number (0x0 .. 0xF)
    mov dh, 0x00
    ; [es:bx] <- pointer to buffer where the data will be stored
    ; caller sets it up for us, and it is actually the standard location for int 13h
    ; BIOS interrupt
    int 0x13
    ; if there is an error (stored in the carry bit)
    jc DiskError

    pop dx
    ; BIOS also sets 'al' to the # of sectors read. Compare it.
    cmp al, dh
    jne SectorsError
    popa
    ret



;*************************
;| If there is an error, |
;| We will do a Loop     |
;*************************
DiskError:
    jmp DiskLoop

SectorsError:
    jmp DiskLoop

DiskLoop:
    jmp $
