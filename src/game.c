#include "game.h"

void run() 
{
    srand(time(NULL) * getpid());
    const char* word = get_random_word();
    // const char* word = "manoc";
    printf("Read the random word: %s\n", word);

    uint8_t running = 1;
    uint16_t tries = 1;

    while (running) 
    {
        const char* input = read_user_input();

        if (tries >= 5)
        {
            printf("Game over.");
            free((char*) input);
            exit(0);
        }

        if (input == NULL)
        {
            continue;
        }

        if (strcmp(input, word) == 0) 
        {
            printf("You guessed the word correctly!\n");
            free((char*) input);
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
        printf("############################################\n");
    }
}

void letters_found_logic(const char* target, const char* guess) 
{
    // If the guess is not correct, then check if any characters
    // in the guess occur in the target word.
    uint16_t i;
    for (i = 0; i < strlen(guess); i++)
    {
        if (char_position(target, guess[i]) >= 0)
        {
            letters_found[i] = 1;
        }
    }
}

void positions_found_logic(const char* target, const char* guess)
{
    uint16_t i;
    for (i = 0; i < strlen(guess); i++)
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
    for (i = 0; i < WORD_LENGTH; i++)
    {
        if (letters_found[i] == 1) 
            color_codes[i] = (positions_found[i] == 1) ? GREEN : YELLOW;
    }
}

const char* read_user_input()
{
    char* input = malloc(sizeof(char) * (WORD_LENGTH + 1));
    printf("Guess the word: ");
    scanf("%s", input);
    if (strlen(input) < WORD_LENGTH) 
    {
        printf("Input word is too short!\n");
        return NULL;
    }
    return input;
}

const char* get_random_word()
{
    FILE* f = fopen(WORD_LIST_PATH, "r");

    if (f == NULL) 
    {
        printf("Error opening file.\n");
        exit(-1);
    }

    char* word = malloc(WORD_SIZE);
    size_t n_words = 0;

    while (fgets(word, sizeof(word), f))
    {
        n_words++;
    }

    char** words = (char**) malloc(sizeof(char*) * n_words);

    rewind(f);

    for (size_t i = 0; i < n_words; i++)
    {
        words[i] = (char*) malloc(WORD_SIZE);
        fgets(words[i], sizeof(words[i]), f);
    }

    fclose(f);

    size_t random_index = rand() % n_words;

    char* random_word = (char*) malloc(WORD_SIZE);
    memcpy(random_word, words[random_index], WORD_SIZE);

    for (size_t i = 0; i < n_words; i++)
    {
        free(words[i]);
    }
    free(words);
    free(word);

    random_word[strcspn(random_word, "\n")] = 0;

    return random_word;
}

void print_characters(const char* characters) 
{
    size_t i;
    for (i = 0; i < strlen(characters); i++) 
    {
        print_colorcoded_char(characters[i], color_codes[i]);
    }
    printf("\n");
}