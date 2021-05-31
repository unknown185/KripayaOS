;
;  Switch32Bit.asm
;  KripayaOS
;
;  Created by Ashwin Paudel on 2021-05-31.
;


; We are now using 16-bit instructions
[bits 16]
Switch32Bit:
    ; [1] Disable Interrupts
    cli
    ; [2] Load the GDT
    lgdt [GDTDescriptor]
    mov eax, cr0
    ; [3] Set 32 Bit mode in cr0
    or eax, 0x1
    mov cr0, eax
    ; [4] Use a different segment for far jump
    jmp CodeSegment:Init32Bit


; We are now using 32-bit instructions
[bits 32]
Init32Bit:
    ; [5] Update the Segment Registers
    mov ax, DataSegment 
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    ; [6] Update the stack right at the top of the free space
    mov ebp, 0x90000
    mov esp, ebp
    ; [7] ; Call the function to start 32 Bit Mode
    call Begin32Bit
