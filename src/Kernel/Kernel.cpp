//
//  Kernel.cpp
//  KripayaOS
//
//  Created by Ashwin Paudel on 2021-05-31.
//

#include <Drivers/Display.h>
#include <Firmware/ISR.h>
#include <Drivers/Keyboard.h>
// We are going to print 'Hello world' to our operating system
extern "C" void KMain()
{
    clearScreen();
    print("Installing interrupt service routines (ISRs).\n");
    isr_install();

    print("Enabling external interrupts.\n");
    asm volatile("sti");

    print("Initializing keyboard (IRQ 1).\n");
    init_keyboard();
}
