#ifndef INPUT_H
#define INPUT_H

void disableRawMode();
void enableRawMode();

/*
 * Function: get_input
 * Description: Returns a character or 0 if none is avaible and -1 on error.
 * Arguments:
 *   player - Pointer to the player.
 * Return Value:
 *   Character as int, -1 on error and 0 otherwise.
 */
int get_input(struct Player *player);

/*
 * Function: process_input
 * Description: Sets player direction using pressed key.
 * Arguments:
 *   player - Pointer to the player.
 *   key - Input key.
 */
int process_input(struct Player *player, int key);

#endif
