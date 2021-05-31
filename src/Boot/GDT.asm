;
;  GDT.asm
;  KripayaOS
;
;  Created by Ashwin Paudel on 2021-05-31.
;


; The labels are needed to compute sizes and jumps
; The Global Descriptor Table initlizes with a null 8-byte
GDTStart:
    ; This is 4 bytes
    dd 0x0
    ; This is 4 bytes
    dd 0x0

; GDT for code segment. The base is equal to 0x00000000, and the length is equal to 0xfffff
GDTCode:
    ; The Segment Length is 0-15 bits
    dw 0xffff
    ; The Segment Base is 0-15 bits
    dw 0x0
    ; The Segment Base is 16-23 bits
    db 0x0
    ; The Flags are 8 bits
    db 10011010b
    ; The 4 Bit Flags and the segment length is equal to 16-19
    db 11001111b
    ; segment base, bits 24-31
    db 0x0


; GDT for data segment. base and length identical to code segment
; some flags changed, again, refer to os-dev.pdf
GDTData:
    dw 0xffff
    dw 0x0
    db 0x0
    db 10010010b
    db 11001111b
    db 0x0

GDTEnd:

; GDT descriptor
GDTDescriptor:
    ; size (16 bit), always one less of its true size
    dw GDTEnd - GDTStart - 1
    ; address (32 bit)
    dd GDTStart

; define some constants for later use
CodeSegment equ GDTCode - GDTStart
DataSegment equ GDTData - GDTStart
