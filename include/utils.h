#include <stdio.h>
#include <stdarg.h>
#include <string.h>

typedef enum
{
    WHITE = 0,
    GREEN, 
    YELLOW
} COLOR_CODE;

int16_t char_position(const char*, char);
void print_colorcoded_char(const char, COLOR_CODE);