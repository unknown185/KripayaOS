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
    print("Hello World!");
}
