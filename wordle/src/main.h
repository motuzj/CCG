#ifndef MAIN_H
#define MAIN_H

#define WORD_LENGTH 5
#define CLEAR_SCREEN "\033[1;1H\033[2J"

extern const char keys_us[];
extern char correct_letters[27]; // green
extern char present_letters[27]; // yellow
extern char absent_letters[27];  // grey
extern char *dictionary_path;

// options
extern bool endless_guesses;
extern bool disable_keyboard;

#endif
