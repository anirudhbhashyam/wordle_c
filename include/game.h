#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "utils.h"

#define WORD_LIST_PATH "./res/words.txt"

#define WORD_LENGTH 5
#define WORD_SIZE sizeof(char) * (WORD_LENGTH + 1)

static uint8_t positions_found[WORD_LENGTH] = { 0, 0, 0, 0, 0 };
static uint8_t letters_found[WORD_LENGTH] = { 0, 0, 0, 0, 0 };
static uint16_t color_codes[WORD_LENGTH] = { 0, 0, 0, 0, 0 };

void run();
void letters_found_logic(const char*, const char*);
void positions_found_logic(const char*, const char*);
void color_code_logic();
const char* read_user_input();
const char* get_random_word();
void print_characters(const char*);