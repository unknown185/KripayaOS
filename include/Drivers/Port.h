#ifndef __PORT_H__
#define __PORT_H__

//
//  Port.h
//  KripayaOS
//
//  Created by Ashwin Paudel on 2021-06-1.
//

#include <Kernel/Common.h>

class Port
{
protected:
    uint16_t portNumber;

public:
    Port(uint16_t port);
    uint8_t read();
    void write(uint8_t data);
};
#endif // __PORT_H__