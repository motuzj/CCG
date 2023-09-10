#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "dict.h"
#include "main.h"

int display_keyboard() {
    if (disable_keyboard) {
        return 0;
    }
    for (int i = 0; i < strlen(keys_us); i++) {
        char ch = keys_us[i];

        // check if the character exists
        int in_correct_letters = char_exists(ch, correct_letters);
        int in_present_letters = char_exists(ch, present_letters);
        int in_absent_letters = char_exists(ch, absent_letters);

        if (in_correct_letters) {
            printf("\033[0;42m%c\033[0m ", ch); // green
        } else if (in_present_letters) {
            printf("\033[0;43m%c\033[0m ", ch); // yellow
        } else if (in_absent_letters) {
            printf("\033[0;90m%c\033[0m ", ch); // grey
        } else {
            printf("\033[0;100m%c\033[0m ", ch); // without color
        }

        if (i == 9 || i == 18 || i == 25) {
            printf("\n");
        }
    }
    return 0;
}

int check_guess(char *guess, char *secret_word) {
    if (!strcmp(secret_word, guess)) {
        printf("┃");
        for (int i = 0; i < strlen(guess); i++) {
            printf("\033[0;32m%c\033[0m┃", toupper(guess[i]));
        }
        printf("\n┗━┻━┻━┻━┻━┛\n");
        printf("You have won!\n");
        return 1;
    }

    if (!is_word_in_dict(guess, dictionary_path)) {
        printf("Word wasn't found in dictionary\n");
        display_keyboard();
        return -1;
    }

    printf("┃");

    for (int i = 0; i < strlen(guess); i++) {
        guess[i] = toupper(guess[i]);
    }

    char temp_secret_word[strlen(secret_word) + 1];

    for (int i = 0; i < strlen(secret_word); i++) {
        temp_secret_word[i] = toupper(secret_word[i]);
    }

    for (int i = 0; i < strlen(guess); i++) {
        if (guess[i] == temp_secret_word[i]) {
            printf("\033[0;32m%c\033[0m┃", guess[i]);
            copy_char_to_array(guess[i], correct_letters);
            continue;
        }

        int correct_same_letters = 0;
        int worlde_same_letters = 0;
        for (int j = 0; j < WORD_LENGTH; j++) {
            if (guess[j] == temp_secret_word[j] && guess[j] == guess[i]) {
                correct_same_letters++;
            }
            if (guess[i] == temp_secret_word[j]) {
                worlde_same_letters++;
            }
        }

        char letters_before[WORD_LENGTH];
        strncpy(letters_before, guess, i);

        int guess_same_letters = 0;
        for (int j = 0; j < i; j++) {
            if (guess[i] == letters_before[j]) {
                guess_same_letters++;
            }
        }

        if (guess_same_letters < worlde_same_letters && correct_same_letters < worlde_same_letters && strchr(temp_secret_word, guess[i]) != NULL) {
            printf("\033[0;33m%c\033[0m┃", guess[i]);
            copy_char_to_array(guess[i], present_letters);
        } else {
            printf("%c┃", guess[i]);
            copy_char_to_array(guess[i], absent_letters);
        }
    }
    printf("\n┣━╋━╋━╋━╋━┫\n\n");
    display_keyboard();
    printf("\n");
    return 0;
}
