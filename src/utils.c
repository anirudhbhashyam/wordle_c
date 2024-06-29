#include "utils.h"

int16_t char_position(const char* word, const char c)
{
    for (size_t i = 0; i < strlen(word); i++)
    {
        if (c == word[i]) return i;
    }
    return -1;
}

void print_colorcoded_char(const char c, COLOR_CODE cc)
{
    const char* start_ansi =  "\033[0;";
    const char* end_ansi =  "\033[0m";

    switch (cc)
    {
        case WHITE:
            printf("%s100m%c%s ", start_ansi, c, end_ansi);
            break;
        case GREEN:
            printf("%s42m%c%s ", start_ansi, c, end_ansi);
            break;
        case YELLOW:
            printf("%s43m%c%s ", start_ansi, c, end_ansi);
            break;
        default:
            printf("%c ", c);
            break;
    }
}