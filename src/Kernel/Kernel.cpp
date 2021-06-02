//
//  Kernel.cpp
//  KripayaOS
//
//  Created by Ashwin Paudel on 2021-05-31.
//

#include <Drivers/Display.h>

// We are going to print 'Hello world' to our operating system
extern "C" void KMain()
{
    // Clear the screen
    clearScreen();
    // Print 'Hello World' to the screen
    print("Hello World!");
}
