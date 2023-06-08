#ifndef GAME
#define GAME

/*
 * Function: display_keyboard
 * Description: Displays keyboard with keys marked by colors
 */
int display_keyboard();
/*
 * Function: check_guess
 * Description: Compares the user's guess with the correct wordle and prints feedback.
 * Arguments:
 *   guess - User's guess.
 *   wordle - Correct answer / target.
 * Return Value:
 *   1 if the guess is correct, -1 on error and 0 otherwise.
 */
int check_guess(char *guess, char *wordle);

#endif
