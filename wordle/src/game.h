#ifndef GAME_H
#define GAME_H

/*
 * Function: check_guess
 * Description: Compares the user's guess with the correct word and prints feedback.
 * Arguments:
 *   guess - User's guess.
 *   secret_word - Correct answer / target.
 * Return Value:
 *   1 if the guess is correct, -1 on error and 0 otherwise.
 */
int check_guess(char *guess, char *secret_word);

#endif
