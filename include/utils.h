#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdint.h>

#define ARRAY_LEN(x) sizeof((x)) / sizeof(x[0])

typedef enum
{
    WHITE = 0,
    GREEN, 
    YELLOW
} COLOR_CODE;

int16_t char_position(const char*, char);
void print_colorcoded_char(const char, COLOR_CODE);

#endif // UTILS_H