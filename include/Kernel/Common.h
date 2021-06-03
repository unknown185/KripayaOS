//
//  Common.h
//  KripayaOS
//
//  Created by Ashwin Paudel on 2021-05-31.
//

#ifndef __COMMON_H__
#define __COMMON_H__

typedef char int8_t;
typedef unsigned char uint8_t;
typedef short int16_t;
typedef unsigned short uint16_t;
typedef int int32_t;
typedef unsigned int uint32_t;
typedef long long int int64_t;
typedef unsigned long long int uint64_t;
typedef const char *string;
typedef uint32_t size_t;

#define VGA_CTRL_REGISTER 0x3d4
#define VGA_DATA_REGISTER 0x3d5
#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
#define WHITE_ON_BLACK 0x0f

void memory_copy(uint8_t *source, uint8_t *dest, uint32_t nbytes);

int string_length(char s[]);

void reverse(char s[]);

void IntToChar(int n, char str[]);

void append(char s[], char n);

int compare_string(char s1[], char s2[]);

bool backspace(char s[]);

#endif // __COMMON_H__