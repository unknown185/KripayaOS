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
    ~Port();
    uint8_t read();
    void write(uint8_t data);
};