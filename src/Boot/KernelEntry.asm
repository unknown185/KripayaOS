;
;  KernelEntry.asm
;  KripayaOS
;
;  Created by Ashwin Paudel on 2021-05-31.
;


; Tell the assembler that we're on 32 bit mode
[bits 32]
; Create a new function from the Kernel/Kernel.cpp file
[extern KMain]
; Call the function in the Kernel/Kernel.cpp file.
; The linker will place this in the memory
call KMain
; Create infinite loop
jmp $
