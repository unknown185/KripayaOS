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
    Port VGADataRegister(VGA_DATA_REGISTER);
    VGAControlRegister.write(VGA_OFFSET_HIGH);
    VGADataRegister.write((unsigned char)(offset >> 8));
    VGAControlRegister.write(VGA_OFFSET_LOW);
    VGADataRegister.write((unsigned char)(offset & 0xff));
}

int getCursor()
{
    Port VGAControlRegister(VGA_CTRL_REGISTER);
    Port VGADataRegister(VGA_DATA_REGISTER);
    VGAControlRegister.write(VGA_OFFSET_HIGH);
    int offset = VGADataRegister.read() << 8;
    VGAControlRegister.write(VGA_OFFSET_LOW);
    offset += VGADataRegister.read();
    return offset * 2;
}

void setCharacterAtVideoMemory(char character, int offset)
{
    uint8_t *vidmem = (uint8_t *)VIDEO_ADDRESS;
    vidmem[offset] = character;
    vidmem[offset + 1] = WHITE_ON_BLACK;
}

int getRowFromOffset(int offset)
{
    return offset / (2 * MAX_COLS);
}

int getOffset(int col, int row)
{
    return 2 * (row * MAX_COLS + col);
}
int moveOffsetToNewLine(int offset)
{
    return getOffset(0, getRowFromOffset(offset) + 1);
}
// Copying a chunk of the video memory.
// Write a function that copies a given number of bytes nbytes in memory from *source to *dest.
void memoryCopy(char *source, char *dest, int nbytes)
{
    int i;
    for (i = 0; i < nbytes; i++)
    {
        *(dest + i) = *(source + i);
    }
}
int scroll_ln(int offset)
{
    memoryCopy(
        (char *)(getOffset(0, 1) + VIDEO_ADDRESS),
        (char *)(getOffset(0, 0) + VIDEO_ADDRESS),
        MAX_COLS * (MAX_ROWS - 1) * 2);

    for (int col = 0; col < MAX_COLS; col++)
    {
        setCharacterAtVideoMemory(' ', getOffset(col, MAX_ROWS - 1));
    }

    return offset - 2 * MAX_COLS;
}
void clearScreen()
{
    int screen_size = MAX_COLS * MAX_ROWS;
    for (int i = 0; i < screen_size; ++i)
    {
        setCharacterAtVideoMemory(' ', i * 2);
    }
    setCursor(getOffset(0, 0));
}
// Print a string onto the screen
void print(char *string)
{
    int offset = getCursor();
    int i = 0;
    while (string[i] != 0)
    {
        if (offset >= MAX_ROWS * MAX_COLS * 2)
        {
            offset = scroll_ln(offset);
        }
        if (string[i] == '\n')
        {
            offset = moveOffsetToNewLine(offset);
        }
        else
        {
            setCharacterAtVideoMemory(string[i], offset);
            offset += 2;
        }
        i++;
    }
    setCursor(offset);
}
void newLine() {
     int newOffset = moveOffsetToNewLine(getCursor());
    if (newOffset >= MAX_ROWS * MAX_COLS * 2) {
        newOffset = scroll_ln(newOffset);
    }
    setCursor(newOffset);
}
void backspace() {
    int newCursor = getCursor() - 2;
    setCharacterAtVideoMemory(' ', newCursor);
    setCursor(newCursor);
}