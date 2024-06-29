#include "game.h"

uint8_t positions_found[WORD_LENGTH] = { 0 };
uint8_t letters_found[WORD_LENGTH] = { 0 };
uint16_t color_codes[WORD_LENGTH] = { 0 };

void run() 
{
    srand(time(NULL) * getpid());

    char word[WORD_LENGTH + 1] = { 0 };
    char input[WORD_LENGTH + 1] = { 0 };
    get_random_word_2(WORD_LIST_PATH, word);

    printf("The word is %s\n", word);

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

        if (strcmp(input, word) == 0) 
        {
            printf("You guessed the word correctly!\n");
            exit(0);
        } 
    
        for (uint16_t i = 0; i < WORD_LENGTH; ++i)
        {
            positions_found[i] = 0;
            letters_found[i] = 0;
            color_codes[i] = 0;
        }

        check_positions_found(input, word);
        check_letters_found(input, word);
        color_code_logic(positions_found, letters_found);

        printf("\n");
        print_characters(input);
        for (int32_t i = 0; i < ARRAY_LEN(letters_found); ++i)
        {
            printf("%d ", letters_found[i]);
        }
        printf("\n");
        for (int32_t i = 0; i < ARRAY_LEN(positions_found); ++i)
        {
            printf("%d ", positions_found[i]);
        }
        printf("\n");

        tries++;
    }
}

void check_letters_found(const char* guess, const char* target)
{
    for (size_t i = 0; i < strlen(guess); ++i)
    {
        if (char_position(target, guess[i]) >= 0)
        {
            letters_found[i] = 1;
        }
    }
#if 1
    for (size_t i = 1; i < strlen(guess); ++i)
    {
        bool first_half_condition = false;
        for (size_t k = 0; k < i; ++k) 
        {
            if (letters_found[k] == 1 && guess[k] == guess[i])
                first_half_condition = true;
        }

        bool second_half_condition = false;
        for (size_t k = i + 1; k < strlen(guess); ++k)
        {
            if (letters_found[k] == 1)
                continue;
            second_half_condition = true;
        }
        
        if (first_half_condition || second_half_condition)
            letters_found[i] = 0;
    }
#endif
}

void check_positions_found(const char* guess, const char* target)
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
    for (uint16_t i = 0; i < WORD_LENGTH; ++i)
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

const char* get_random_word_2(const char* filepath, char* random_word)
{
    FILE* f = fopen(filepath, "r");

    if (f == NULL) {
        fprintf(stderr, "Error opening file %s: %s\n", filepath, strerror(errno));
        exit(1);
    }

    char word_with_newline[WORD_LENGTH + 1 + 1] = { 0 };
    size_t n_words = 0;

    while (fgets(word_with_newline, ARRAY_LEN(word_with_newline), f)) {
        n_words++;
    }

    size_t random_index = rand() % n_words;

    rewind(f);
    size_t counter = 0;
    while(fgets(word_with_newline, ARRAY_LEN(word_with_newline), f))
    {
        if (counter == random_index)
        {
            memcpy(random_word, word_with_newline, WORD_SIZE);
            break;
        }

        counter++;
    }
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