//
//  ISR.cpp
//  KripayaOS
//
//  Created by Ashwin Paudel on 2021-06-3.
//

#include <Firmware/ISR.h>

isr_t InterruptHandlers[256];

/* Can't do this with a loop because we need the address
 * of the function names */
extern "C" void ISRInstall()
{
    SetIDTGate(0, (uint32_t)isr0);
    SetIDTGate(1, (uint32_t)isr1);
    SetIDTGate(2, (uint32_t)isr2);
    SetIDTGate(3, (uint32_t)isr3);
    SetIDTGate(4, (uint32_t)isr4);
    SetIDTGate(5, (uint32_t)isr5);
    SetIDTGate(6, (uint32_t)isr6);
    SetIDTGate(7, (uint32_t)isr7);
    SetIDTGate(8, (uint32_t)isr8);
    SetIDTGate(9, (uint32_t)isr9);
    SetIDTGate(10, (uint32_t)isr10);
    SetIDTGate(11, (uint32_t)isr11);
    SetIDTGate(12, (uint32_t)isr12);
    SetIDTGate(13, (uint32_t)isr13);
    SetIDTGate(14, (uint32_t)isr14);
    SetIDTGate(15, (uint32_t)isr15);
    SetIDTGate(16, (uint32_t)isr16);
    SetIDTGate(17, (uint32_t)isr17);
    SetIDTGate(18, (uint32_t)isr18);
    SetIDTGate(19, (uint32_t)isr19);
    SetIDTGate(20, (uint32_t)isr20);
    SetIDTGate(21, (uint32_t)isr21);
    SetIDTGate(22, (uint32_t)isr22);
    SetIDTGate(23, (uint32_t)isr23);
    SetIDTGate(24, (uint32_t)isr24);
    SetIDTGate(25, (uint32_t)isr25);
    SetIDTGate(26, (uint32_t)isr26);
    SetIDTGate(27, (uint32_t)isr27);
    SetIDTGate(28, (uint32_t)isr28);
    SetIDTGate(29, (uint32_t)isr29);
    SetIDTGate(30, (uint32_t)isr30);
    SetIDTGate(31, (uint32_t)isr31);

    /// Remap the PIC
    // ICW1
    Port(0x20).write(0x11);
    Port(0xA0).write(0x11);
    // ICW2
    Port(0x21).write(0x20);
    Port(0xA1).write(0x28);
    // ICW3
    Port(0x21).write(0x04);
    Port(0xA1).write(0x02);
    // ICW4
    Port(0x21).write(0x01);
    Port(0xA1).write(0x01);
    // OCW1
    Port(0x21).write(0x0);
    Port(0xA1).write(0x0);

    // Install the IRQs
    SetIDTGate(32, (uint32_t)irq0);
    SetIDTGate(33, (uint32_t)irq1);
    SetIDTGate(34, (uint32_t)irq2);
    SetIDTGate(35, (uint32_t)irq3);
    SetIDTGate(36, (uint32_t)irq4);
    SetIDTGate(37, (uint32_t)irq5);
    SetIDTGate(38, (uint32_t)irq6);
    SetIDTGate(39, (uint32_t)irq7);
    SetIDTGate(40, (uint32_t)irq8);
    SetIDTGate(41, (uint32_t)irq9);
    SetIDTGate(42, (uint32_t)irq10);
    SetIDTGate(43, (uint32_t)irq11);
    SetIDTGate(44, (uint32_t)irq12);
    SetIDTGate(45, (uint32_t)irq13);
    SetIDTGate(46, (uint32_t)irq14);
    SetIDTGate(47, (uint32_t)irq15);

    LoadIDT(); // Load with ASM
}

/* To print the message which defines every exception */
char *ExceptionMessages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"};

extern "C" void ISRHandler(registers_t *r)
{
    print("received interrupt: ");
    char s[3];
    IntToChar(r->int_no, s);
    print(s);
    newLine();
    print(ExceptionMessages[r->int_no]);
    newLine();
}

void RegisterInterruptHandler(uint8_t n, isr_t handler)
{
    InterruptHandlers[n] = handler;
}

extern "C" void IRQHandler(registers_t *r)
{
    /* Handle the interrupt in a more modular way */
    if (InterruptHandlers[r->int_no] != 0)
    {
        isr_t handler = InterruptHandlers[r->int_no];
        handler(r);
    }

    // EOI
    if (r->int_no >= 40)
    {
        Port(0xA0).write(0x20); /* follower */
    }
    Port(0x20).write(0x20);
}