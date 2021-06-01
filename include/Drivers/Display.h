#ifndef __DISPLAY_H__
#define __DISPLAY_H__

//
//  Display.h
//  KripayaOS
//
//  Created by Ashwin Paudel on 2021-06-1.
//

#include <Kernel/Common.h>
// #include <Drivers/Port.h>

void setCursor(int offset);
int getCursor();
void setCharacterAtVideoMemory(char character, int offset);
void print(char *string);


#endif // __DISPLAY_H__