//
//  Kernel.cpp
//  KripayaOS
//
//  Created by Ashwin Paudel on 2021-05-31.
//

// We are going to print 'Hello world' to our operating system
extern "C" void KMain()
{
    unsigned char *VideoMemory = (unsigned char *)0xb8000;
    VideoMemory[0] = 'H';
    VideoMemory[2] = 'E';
    VideoMemory[4] = 'L';
    VideoMemory[6] = 'L';
    VideoMemory[8] = 'O';
    VideoMemory[10] = ' ';
    VideoMemory[12] = 'W';
    VideoMemory[14] = 'O';
    VideoMemory[16] = 'R';
    VideoMemory[18] = 'L';
    VideoMemory[20] = 'D';
    VideoMemory[22] = '!';
    VideoMemory[24] = ' ';
    VideoMemory[26] = '\0';
}
