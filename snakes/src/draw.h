#ifndef DRAW_H
#define DRAW_H

#include "main.h"

/*
 * Function: draw
 * Description: Prints a board with snakes and fruits.
 * Arguments:
 *   player1 - Pointer to the first player.
 *   player2 - Pointer to the second player.
 *   fruits - Pointer to a array containing all fruits from board
 */
int draw(struct Player player1, struct Player player2, bool fruits[], int frames);

#endif
