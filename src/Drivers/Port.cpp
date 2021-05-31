//
//  Port.cpp
//  KripayaOS
//
//  Created by Ashwin Paudel on 2021-06-1.
//

#include <Drivers/Port.h>

Port::Port(uint16_t port)
{
    portNumber = port;
}
// Read data from a specific port.
uint8_t Port::read()
{
    unsigned char result;
    /* 
    The C++ variable 'port' is mapped to the dx register.
    And then we execute assembly code 'in al, dx' 
    Then store the value of 'al' into 'result' variable.
    */
    __asm__("in %%dx, %%al"
            : "=a"(result)
            : "d"(portNumber));
    return result;
}

// Write data to a specfic port.
void Port::write(uint8_t data)
{
    // It runs the command 'out dx, al,' which maps the port to 'dx' and the data to 'al.'
    __asm__("out %%al, %%dx"
            :
            : "a"(data), "d"(portNumber));
}