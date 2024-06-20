#include "game.h"

uint8_t positions_found[WORD_LENGTH] = { 0 };
uint8_t letters_found[WORD_LENGTH] = { 0 };
uint16_t color_codes[WORD_LENGTH] = { 0 };

void run() 
{
    srand(time(NULL) * getpid());
    char* word = malloc(WORD_SIZE);
    get_random_word(word);
    char* input = malloc(WORD_SIZE);

    uint8_t running = 1;
    uint16_t tries = 1;

    while (running) 
    {
        read_user_input(input);

        if (tries >= 5)
        {
            printf("Game over.\n");
            printf("The word was: %s\n", word);
            exit(0);
        }

        if (input == NULL)
        {
            continue;
        }

        if (strcmp(input, word) == 0) 
        {
            printf("You guessed the word correctly!\n");
            exit(0);
        } 
        else 
        {
            positions_found_logic(word, input);
            letters_found_logic(word, input);
            color_code_logic(positions_found, letters_found);
        }
        printf("\n");
        print_characters(input);

        tries++;
    }
    free(input);
    free((char*) word);
}

void letters_found_logic(const char* target, const char* guess) 
{
    for (size_t i = 0; i < strlen(guess); ++i)
    {
        if (char_position(target, guess[i]) >= 0)
        {
            letters_found[i] = 1;
        }
    }
}

void positions_found_logic(const char* target, const char* guess)
{
    for (size_t i = 0; i < strlen(guess); ++i)
    {
        if (target[i] == guess[i])
        {
            positions_found[i] = 1;
        }
    }
}

void color_code_logic()
{
    uint16_t i;
    for (i = 0; i < WORD_LENGTH; ++i)
    {
        if (letters_found[i] == 1) 
            color_codes[i] = (positions_found[i] == 1) ? GREEN : YELLOW;
    }
}

char* read_user_input(char* input)
{
    printf("Guess the word: ");
    scanf("%s", input);
    if (strlen(input) < WORD_LENGTH) 
    {
        printf("Input word is too short!\n");
        return NULL;
    }
    if (strlen(input) > WORD_LENGTH)
    {
        printf("Input word is too long!\n");
        return NULL;
    }
    for (size_t i = 0; i < strlen(input); ++i)
    {
        if (!isalpha(input[i]))
            return NULL;
    }
    return input;
}

const char* get_random_word(char* random_word)
{
    FILE* f = fopen(WORD_LIST_PATH, "r");

    if (f == NULL) 
    {
        fprintf(stderr, "Error opening file %s: %s", WORD_LIST_PATH, strerror(errno));
        exit(-1);
    }

    char word[WORD_SIZE] = { 0 };
    size_t n_words = 0;

    while (fgets(word, ARRAY_LEN(word), f))
    {
        n_words++;
    }

    rewind(f);

    char** words = malloc(sizeof(char*) * n_words);

    for (size_t i = 0; i < n_words; ++i)
    {
        words[i] = malloc(WORD_SIZE);
        fgets(words[i], sizeof(words[i]), f);
    }

    if (fclose(f) != 0) {
        fprintf(stderr, "Error closing file %s: %s", WORD_LIST_PATH, strerror(errno));
    }

    size_t random_index = rand() % n_words;

    memcpy(random_word, words[random_index], WORD_SIZE);

    for (size_t i = 0; i < n_words; ++i)
    {
        free(words[i]);
    }
    free(words);

    random_word[strcspn(random_word, "\n")] = 0;

    return random_word;
}

void print_characters(const char* characters) 
{
    for (size_t i = 0; i < strlen(characters); ++i)
    {
        print_colorcoded_char(characters[i], color_codes[i]);
    }
    printf("\n");
}