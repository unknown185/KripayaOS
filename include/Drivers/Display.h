//
//  Display.h
//  KripayaOS
//
//  Created by Ashwin Paudel on 2021-06-1.
//

#ifndef __DISPLAY_H__
#define __DISPLAY_H__

#include <Kernel/Common.h>

// Set the current cursor position
void setCursor(int offset);
// Get the current cursor position
int getCursor();
// Print a character in the screen
void setCharacterAtVideoMemory(char character, int offset);
int getRowFromOffset(int offset);
int getOffset(int col, int row);
int moveOffsetToNewLine(int offset);
void memoryCopy(char *source, char *dest, int nbytes);
int scroll_ln(int offset);
void clearScreen();
// Print a string into the screen
void print(char *string);
void newLine();
void backspace();
#endif // __DISPLAY_H__