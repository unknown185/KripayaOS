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
#include <Kernel/Memory.h>


void* alloc(int n) {
    int *ptr = (int *) mem_alloc(n * sizeof(int));
    if (ptr == NULL_POINTER) {
        print("Memory not allocated.\n");
    } else {
        // Get the elements of the array
        for (int i = 0; i < n; ++i) {
//            ptr[i] = i + 1; // shorthand for *(ptr + i)
        }

        for (int i = 0; i < n; ++i) {
//            char str[256];
//            int_to_string(ptr[i], str);
//            print_string(str);
        }
//        print_nl();
    }
    return ptr;
}

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

    print("Initializing dynamic memory.\n");
    init_dynamic_mem();

    clearScreen();

    print("init_dynamic_mem()\n");
    print_dynamic_node_size();
    print_dynamic_mem();
    newLine();

    int *ptr1 = (int*)alloc(5);
    print("int *ptr1 = alloc(5)\n");
    print_dynamic_mem();
    newLine();

    int *ptr2 = (int *)alloc(10);
    print("int *ptr2 = alloc(10)\n");
    print_dynamic_mem();
    newLine();

    mem_free(ptr1);
    print("mem_free(ptr1)\n");
    print_dynamic_mem();
    newLine();

    int *ptr3 = (int *)alloc(2);
    print("int *ptr3 = alloc(2)\n");
    print_dynamic_mem();
    newLine();

    mem_free(ptr2);
    print("mem_free(ptr2)\n");
    print_dynamic_mem();
    newLine();

    mem_free(ptr3);
    print("mem_free(ptr3)\n");
    print_dynamic_mem();
    newLine();

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