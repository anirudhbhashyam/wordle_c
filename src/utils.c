#include "utils.h"

int16_t char_position(const char* word, char c)
{
    u_int16_t i;
    for (i = 0; i < strlen(word); i++)
    {
        if (c == word[i]) return i;
    }
    return -1;
}

void print_colorcoded_char(const char c, COLOR_CODE cc)
{
    const char* start_color =  "\033[0;";
    const char* end_color =  "\033[0m";

    switch (cc)
    {
        case WHITE:
            printf("%s100m%c%s ", start_color, c, end_color);
            break;
        case GREEN:
            printf("%s42m%c%s ", start_color, c, end_color);
            break;
        case YELLOW:
            printf("%s43m%c%s ", start_color, c, end_color);
            break;
        default:
            printf("%c ", c);
            break;
    }
}