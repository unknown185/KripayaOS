//
//  IDT.h
//  KripayaOS
//
//  Created by Ashwin Paudel on 2021-06-3.
//

#pragma once

#include <Kernel/Common.h>

#define KERNEL_CS 0x08

/* How every interrupt gate (handler) is defined */
typedef struct {
    uint16_t low_offset;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed)) idt_gate_t;

typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256

extern "C" void SetIDTGate(int n, uint32_t handler);

extern "C" void LoadIDT();