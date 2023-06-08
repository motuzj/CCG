#ifndef MAIN
#define MAIN

#define WORD_LENGTH 5
#define CLEAR_SCREEN "\e[1;1H\e[2J"

extern const char keys_us[];
extern char correct_letters[27]; // green
extern char present_letters[27]; // yellow
extern char absent_letters[27];  // grey
extern char *dictionary_path;

// options
extern bool endless_guesses;
extern bool disable_keyboard;

#endif
