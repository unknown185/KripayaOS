//
//  Display.cpp
//  KripayaOS
//
//  Created by Ashwin Paudel on 2021-06-1.
//

#include <Drivers/Display.h>
#include <Drivers/Port.h>

void setCursor(int offset)
{
    offset /= 2;
    Port VGAControlRegister(VGA_CTRL_REGISTER);
    VGAControlRegister.write(VGA_OFFSET_HIGH);
    VGAControlRegister.write(VGA_OFFSET_LOW);
    Port VGADataRegister(VGA_DATA_REGISTER);
    VGADataRegister.write((uint8_t)(offset >> 8));
    VGADataRegister.write((uint8_t)(offset & 0xff));
}

int getCursor()
{
    Port VGAControlRegister(VGA_CTRL_REGISTER);
    VGAControlRegister.write(VGA_OFFSET_HIGH);
    Port VGADataRegister(VGA_DATA_REGISTER);
    int offset = VGADataRegister.read() << 8;
    VGAControlRegister.write(VGA_OFFSET_LOW);
    offset += VGADataRegister.read();
    return offset * 2;
}

void setCharacterAtVideoMemory(char character, int offset) {
    uint8_t *vidmem = (uint8_t *) VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = WHITE_ON_BLACK;
}

void print(char *string) {
    int offset = getCursor();
    int i = 0;
    while (string[i] != 0) {
        setCharacterAtVideoMemory(string[i], offset);
        i++;
        offset += 2;
    }
    setCursor(offset);
}