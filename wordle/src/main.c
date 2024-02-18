#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "dict.h"
#include "game.h"
#include "main.h"

const char keys_us[] = "QWERTYUIOPASDFGHJKLZXCVBNM";
char correct_letters[27];
char present_letters[27];
char absent_letters[27];
char *dictionary_path;
bool custom_secret_word = false;

// options
bool endless_guesses = false;
bool disable_keyboard = false;

int main(int argc, char *argv[]) {
    char *secret_word = NULL;
    int opt;

    while ((opt = getopt(argc, argv, "d:w:ekh")) != -1) {
        switch (opt) {
            case 'd':
                dictionary_path = optarg;
                break;
            case 'w':
                if (strlen(optarg) == 5) {
                    custom_secret_word = true;
                    secret_word = optarg;
                }
                break;
            case 'e':
                endless_guesses = true;
                break;
            case 'k':
                disable_keyboard = true;
                break;
            case 'h':
                printf("Usage: wordle [OPTION]...\n\n"
                       " -d \033[3m<path>\033[0m\tSpecify the path to a custom dictionary file.\n"
                       " -w \033[3m<str>\033[0m\tChoose manually a word to guess.\n"
                       " -e\t\tEnable endless guesses mode.\n"
                       " -k\t\tDisable keyboard display.\n"
                       " -h\t\tDisplay help message.\n");
                return 0;
        }
    }

    if (dictionary_path == NULL) {
        dictionary_path = "dict/english.txt";
    }

    if (secret_word == NULL) {
        if ((secret_word = get_word(dictionary_path)) == NULL) {
            return 1;
        }
    }

    int loops_count = 0;

    printf(ENTER_ALTERNATE_SCREEN);
    printf(CLEAR_SCREEN);
    printf("┏━┳━┳━┳━┳━┓\n\n");

    char guess[WORD_LENGTH + 1];

    // game loop
    while (loops_count < WORD_LENGTH + 1 || endless_guesses) {
        printf("Guess: ");
        scanf("%5s", guess); // TODO: number of characters to scan should be defined by WORD_LENGTH

        for (int i = 0; i < strlen(guess); i++) {
            guess[i] = tolower(guess[i]);
        }
        printf("\033[%d;1H\033[J", loops_count * 2 + 2); // clear only part of the terminal

        if (strlen(guess) != WORD_LENGTH) {
            printf("Incorect guess size.\n");
            continue;
        }

        int last_guess_state; // return value of check_guess()
        if ((last_guess_state = check_guess(guess, secret_word)) == 1) {
            break;
        } else if (last_guess_state == 0) {
            loops_count++;
        }
    }
    if (loops_count >= WORD_LENGTH + 1 && !endless_guesses) {
        printf("\033[%d;1H\033[J", loops_count * 2 + 2);
        printf("┃G┃A┃M┃E┃ ┃\n┃ ┃O┃V┃E┃R┃");
        printf("\n┗━┻━┻━┻━┻━┛\n");
        printf("You failed to guess the word '%s'\n\nPress [ENTER] to exit.\n", secret_word);
        getchar();
        getchar(); // idk why i need two getchars
        printf(EXIT_ALTERNATE_SCREEN);
    }
    if (!custom_secret_word) free(secret_word);
    return 0;
}
