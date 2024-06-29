#ifndef GAME_H
#define GAME_H

#include <stdbool.h>
#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "utils.h"

#define WORD_LIST_PATH "./res/words.txt"

#define WORD_LENGTH 5
#define WORD_SIZE sizeof(char) * (WORD_LENGTH + 1)

extern uint8_t positions_found[WORD_LENGTH];
extern uint8_t letters_found[WORD_LENGTH];
extern uint16_t color_codes[WORD_LENGTH];

void run();
void check_letters_found(const char*, const char*);
void check_positions_found(const char*, const char*);
void color_code_logic();
char* read_user_input(char*);
const char* get_random_word(char*);
const char* get_random_word_2(const char*, char*);
void print_characters(const char*);

#endif // GAME_H