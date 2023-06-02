#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define WORD_LENGTH 5

// TODO:
// * check if guessed words are in dictionary
// * better tui
// * limit guesses
// * cli arguments (disable keyboard, no color mode?, custom dictionary)
// * comments

const char keys_us[] = "qwertyuiopasdfghjklzxcvbnm";
char correct_letters[27]; // green
char present_letters[27]; // yellow
char absent_letters[27];  // grey

/*
 * Function: get_word
 * Description: Returns random line with word from dictionary file.
 * Return Value:
 *   Pointer to a string representing a random line from file, or NULL at error.
 */
char *get_word() {
    FILE *file = fopen("dict/english.txt", "r");
    if (file == NULL) {
        perror("Error: Can't open file. Does it really exist?\n");
        return NULL;
    }

    if (fgetc(file) == EOF) {
        fprintf(stderr, "Error: File is empty\n");
        return NULL;
    }

    // count all newlines in file
    int line_count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            line_count++;
        }
    }

    rewind(file);

    srand(time(NULL));
    int random_line = rand() % line_count;

    char *line = NULL;
    size_t line_length = 0;
    long read;

    // save lines to 'read' until a random_line is reached
    for (int current_line = 0; current_line <= random_line; current_line++) {
        read = getline(&line, &line_length, file);
        if (read == -1) {
            fprintf(stderr, "Error: Can't read file\n");
            return NULL;
        }
    }

    // remove newline from 'line'
    line[strlen(line) - 1] = '\0';

    fclose(file);
    return line;
}

/*
 * Function: char_exists
 * Description: Checks if char already exists in file
 * Arguments:
 *   ch - Char that will be searched
 *   array - Array where will char be searched
 *   array_size - Size of Array
 * Return Value:
 *   1 if char exists in array, 0 if wasn't found.
 */
int char_exists(char ch, char arr[], int array_size) {
    for (int i = 0; i < array_size; i++) {
        if (arr[i] == ch) {
            return 1;
        }
    }
    return 0;
}

/*
 * Function: copy_char_to_array
 * Description: Copies char to the end of the array, if it's not already present in array.
 * Arguments:
 *   ch - Char that will be copied
 *   array - Array that will be char copied to
 * Return Value:
 *   0 if successfully copied to the end of array, 1 if char was already present.
 */
int copy_char_to_array(char ch, char *array) {
    if (char_exists(ch, array, strlen(correct_letters))) {
        return 1;
    }
    int length = strlen(array);
    array[length] = ch;
    array[length + 1] = '\0';
    return 0;
}

/*
 * Function: display_keyboard
 * Description: Displays keyboard with keys marked by colors
 */
int display_keyboard() {
    for (int i = 0; i < strlen(keys_us); i++) {
        char ch = keys_us[i];

        // check if the character exists
        int in_correct_letters = char_exists(ch, correct_letters, strlen(correct_letters));
        int in_present_letters = char_exists(ch, present_letters, strlen(present_letters));
        int in_absent_letters = char_exists(ch, absent_letters, strlen(absent_letters));

        if (in_correct_letters) {
            printf("\033[0;32m%c\033[0m ", ch); // green
        } else if (in_present_letters) {
            printf("\033[0;33m%c\033[0m ", ch); // yellow
        } else if (in_absent_letters) {
            printf("\033[0;90m%c\033[0m ", ch); // grey
        } else {
            printf("%c ", ch); // without color
        }

        if (i == 9 || i == 18 || i == 25) {
            printf("\n");
        }
    }
    return 0;
}

/*
 * Function: check_guess
 * Description: Compares the user's guess with the correct wordle and prints feedback.
 * Arguments:
 *   guess - User's guess.
 *   wordle - Correct answer / target.
 * Return Value:
 *   1 if the guess is correct, 0 otherwise.
 */
int check_guess(char *guess, char *wordle) {
    if (!strcmp(wordle, guess)) {
        printf("You have won!\n");
        return 1;
    }

    for (int i = 0; i < strlen(guess); i++) {
        if (guess[i] == wordle[i]) {
            printf("\e[0;32m%c\e[0m", guess[i]);
            copy_char_to_array(guess[i], correct_letters);
            continue;
        }

        int correct_same_letters = 0;
        int worlde_same_letters = 0;
        for (int j = 0; j < WORD_LENGTH; j++) {
            if (guess[j] == wordle[j] && guess[j] == guess[i]) {
                correct_same_letters++;
            }
            if (guess[i] == wordle[j]) {
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

        if (guess_same_letters < worlde_same_letters && correct_same_letters < worlde_same_letters && strchr(wordle, guess[i]) != NULL) {
            printf("\e[0;33m%c\e[0m", guess[i]);
            copy_char_to_array(guess[i], present_letters);
        } else {
            printf("%c", guess[i]);
            copy_char_to_array(guess[i], absent_letters);
        }
    }
    printf("\n");
    display_keyboard();
    printf("\n");
    return 0;
}

int main(void) {
    char *wordle;

    if ((wordle = get_word()) == NULL) {
        return 1;
    }

    // game loop
    while (1) {
        char guess[WORD_LENGTH + 1];

        printf("Guess: ");
        scanf("%5s", guess);

        for (int i = 0; i < strlen(guess); i++) {
            guess[i] = tolower(guess[i]);
        }

        if (strlen(guess) != WORD_LENGTH) {
            printf("Incorect guess size.\n");
            continue;
        }

        if (check_guess(guess, wordle)) {
            break;
        }
    }
    free(wordle);
    return 0;
}
