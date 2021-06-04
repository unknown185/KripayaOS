;
;  MBR.asm
;  KripayaOS
;
;  Created by Ashwin Paudel on 2021-05-31.
;


; Tell the assembler that we are running 16 bit instructions
[bits 16]
; Specifies the offset from the start of a segment.
[org 0x7c00]

; This is a variable with the value 0x1000
; Loading the kernel into memory and jumping to its entry point.
KernelOffset equ 0x1000

; Keep in mind that the BIOS sets the boot drive to 'dl' on startup.
mov [BootDrive], dl

; Set bp (Bottom of the stack) equal to 0x9000
mov bp, 0x9000
; Set sp (Top of the stack) equal to bp (Bottom of the stack)
mov sp, bp

; Load the kernel into the disk
call LoadKernel
; Disable the Interrupts, Global Descriptor table etc. and then go to 32 bit mode
call Switch32Bit
; Will never be called
jmp $

; Include other files
%include "src/Boot/Disk.asm"
%include "src/Boot/GDT.asm"
%include "src/Boot/Switch32bit.asm"
%include "src/Boot/Print16Bit.asm"
%include "src/Boot/Print32Bit.asm"
; We're using 16 bit instructions, so we have to tell assembler.
[bits 16]
; Create a new function
; This will load the kernel into the memory
; call print32_nl
LoadKernel:
    mov bx, KernelOffset
    mov dh, 31
    mov dl, [BootDrive]
    call DiskLoad
    ret

; We're using 32 bit instructions, so we have to tell assembler.
[bits 32]
; Begin 32 Bit mode
Begin32Bit:
    ; Let the Kernel take over
    call KernelOffset
    ; If the Kernel wants to give us control, we'll create an infinite loop
    jmp $

; We are storing in memory because 'dl' can be overwritten
BootDrive db 0

; Padding
times 510 - ($-$$) db 0
dw 0xaa55
