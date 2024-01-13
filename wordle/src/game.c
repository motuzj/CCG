#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "dict.h"
#include "main.h"

void display_keyboard() {
    for (int i = 0; i < strlen(keys_us); i++) {
        char ch = keys_us[i];

        // check if the character exists
        bool in_correct_letters = char_exists(ch, correct_letters);
        bool in_present_letters = char_exists(ch, present_letters);
        bool in_absent_letters = char_exists(ch, absent_letters);

        if (in_correct_letters) {
            printf("\033[42m%c\033[0m ", ch); // green
        } else if (in_present_letters) {
            printf("\033[43m%c\033[0m ", ch); // yellow
        } else if (in_absent_letters) {
            printf("\033[90m%c\033[0m ", ch); // grey
        } else {
            printf("\033[100m%c\033[0m ", ch); // without color
        }

        // print newline after few characters
        if (i == 9 || i == 18 || i == 25) {
            printf("\n");
        }
    }
}

int check_guess(char *guess, char *secret_word) {
    // check if the guess is correct
    if (!strcmp(secret_word, guess)) {
        printf("┃");
        for (int i = 0; i < WORD_LENGTH; i++) {
            printf("\033[32m%c\033[0m┃", toupper(guess[i])); // print letter in green
        }
        printf("\n┗━┻━┻━┻━┻━┛\n");
        printf("You have won!\n");
        return 1;
    }

    // check if the guess is not in the dictionary
    if (!is_word_in_dict(guess, dictionary_path)) {
        printf("Word wasn't found in dictionary\n");
        display_keyboard();
        return -1;
    }

    printf("┃");

    // convert guess to uppercase
    for (int i = 0; i < WORD_LENGTH; i++) {
        guess[i] = toupper(guess[i]);
    }

    // make a copy of secret_word and convert it to uppercase
    char temp_secret_word[WORD_LENGTH + 1];
    for (int i = 0; i < WORD_LENGTH; i++) {
        temp_secret_word[i] = toupper(secret_word[i]);
    }

    // check what letters are same
    for (int i = 0; i < WORD_LENGTH; i++) {
        // check if the letter in the guess is in the correct position in secret word
        if (guess[i] == temp_secret_word[i]) {
            printf("\033[32m%c\033[0m┃", guess[i]); // print letter in green
            copy_char_to_array(guess[i], correct_letters);
            continue;
        }

        // this part seems too complicated, but I wanted the word checking to be the same as in the
        // original/NY Times version of the game. to understand this code you need

        // number of letters in the correct position
        int correct_same_letters = 0;
        // number of letters appearing in the secret word but not in the correct position
        int secret_word_same_letters = 0;
        for (int j = 0; j < WORD_LENGTH; j++) {
            if (guess[j] == temp_secret_word[j] && guess[j] == guess[i]) {
                correct_same_letters++;
            }
            if (guess[i] == temp_secret_word[j]) {
                secret_word_same_letters++;
            }
        }

        // number of times the current letter appears before the guess
        int previous_same_letters = 0;
        for (int j = 0; j < i; j++) {
            if (guess[i] == guess[j]) {
                previous_same_letters++;
            }
        }

        if (previous_same_letters < secret_word_same_letters &&
            correct_same_letters < secret_word_same_letters &&
            strchr(temp_secret_word, guess[i]) != NULL) {
            printf("\033[33m%c\033[0m┃", guess[i]); // print letter in yellow
            copy_char_to_array(guess[i], present_letters);
        } else {
            printf("%c┃", guess[i]); // print letter without color
            copy_char_to_array(guess[i], absent_letters);
        }
    }
    printf("\n┣━╋━╋━╋━╋━┫\n\n");
    if (!disable_keyboard) display_keyboard();
    printf("\n");
    return 0;
}
