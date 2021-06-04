//
//  IDT.cpp
//  KripayaOS
//
//  Created by Ashwin Paudel on 2021-06-3.
//

#include <Firmware/IDT.h>

#define LOW_16(address) (uint16_t)((address)&0xFFFF)
#define HIGH_16(address) (uint16_t)(((address) >> 16) & 0xFFFF)

idt_gate_t idt[IDT_ENTRIES];
idt_register_t idt_reg;

extern "C" void SetIDTGate(int n, uint32_t handler)
{
    idt[n].low_offset = LOW_16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E;
    idt[n].high_offset = HIGH_16(handler);
}

extern "C" void LoadIDT()
{
    idt_reg.base = (uint32_t)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    /* Don't make the mistake of loading &idt -- always load &idt_reg */
    asm volatile("lidt (%0)"
                 :
                 : "r"(&idt_reg));
}