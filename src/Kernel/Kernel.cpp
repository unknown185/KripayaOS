//
//  Kernel.cpp
//  KripayaOS
//
//  Created by Ashwin Paudel on 2021-05-31.
//

#include <Drivers/Display.h>
#include <Firmware/ISR.h>
#include <Drivers/Keyboard.h>
#include <Kernel/Kernel.h>
// We are going to print 'Hello world' to our operating system
extern "C" void KMain()
{
    clearScreen();
    print("Installing interrupt service routines (ISRs).\n");
    ISRInstall();

    print("Enabling external interrupts.\n");
    asm volatile("sti");

    print("Initializing keyboard (IRQ 1).\n");
    init_keyboard();

    print("Type help for more information \n");
    print("> ");
}
void execute_command(char *input)
{
    if (compare_string(input, "EXIT") == 0)
    {
        print("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }
    else if (compare_string(input, "HELP") == 0)
    {
        print("List of commands:\n");
        print("    EXIT\n");
        print("> ");
    }
    else
    {
        print("Unknown command: ");
        print(input);
        print("\n> ");
    }
}