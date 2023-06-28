#ifndef PLAYER_H
#define PLAYER_H

/*
 * Function: initialize_body
 * Description: Initialize player's body.
 * Arguments:
 *   player - Pointer to the player.
 * Return Value:
 *   1 on error and 0 otherwise.
 */
int initialize_body(struct Player *player);
/*
 * Function: change_controls
 * Description: Initialize player's body.
 * Arguments:
 *   player1 - Pointer to the first player.
 *   player2 - Pointer to the second player.
 */
int change_controls(struct Player *player1, struct Player *player2);
/*
 * Function: move_player
 * Description: Move player by one cell to his direction.
 * Arguments:
 *   player - Pointer to the player.
 */
int move_player(struct Player *player);

#endif
