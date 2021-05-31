//
//  Display.cpp
//  KripayaOS
//
//  Created by Ashwin Paudel on 2021-06-1.
//

#include <Drivers/Display.h>

void setCursor(int offset)
{
    offset /= 2;
    Port VGAControlRegister(VGA_CTRL_REGISTER);
    VGAControlRegister.write(VGA_OFFSET_HIGH);
    VGAControlRegister.write(VGA_OFFSET_LOW);
    Port VGADataRegister(VGA_DATA_REGISTER);
    VGAControlRegister.write((uint8_t)(offset >> 8));
    VGAControlRegister.write((uint8_t)(offset & 0xff));
}

int get_cursor()
{
    Port VGAControlRegister(VGA_CTRL_REGISTER);
    VGAControlRegister.write(VGA_OFFSET_HIGH);
    Port VGADataRegister(VGA_DATA_REGISTER);
    int offset = VGADataRegister.read() << 8;
    VGAControlRegister.write(VGA_OFFSET_LOW);
    offset += VGADataRegister.read();
    return offset * 2;
}