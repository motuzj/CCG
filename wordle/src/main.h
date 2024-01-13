#ifndef MAIN_H
#define MAIN_H

#define WORD_LENGTH 5
#define CLEAR_SCREEN "\033[1;1H\033[2J"

extern const char keys_us[];
extern char correct_letters[27]; // letters correctly guessed and at the correct position - green
extern char present_letters[27]; // letters correctly guessed, but at the wrong position - yellow
extern char absent_letters[27]; // guessed letters that are not it the secret word - grey
extern char *dictionary_path;

// options
extern bool endless_guesses;
extern bool disable_keyboard;

#endif
