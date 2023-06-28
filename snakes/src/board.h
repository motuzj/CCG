#ifndef BOARD_H
#define BOARD_H

#include "main.h"
#include <stdbool.h>

/*
 * Function: check_fruit_collision
 * Description: Checks collision with player and fruit and adds score to the player.
 * Arguments:
 *   player - Pointer to the player.
 *   fruits - Bool array with fruits.
 */
int check_fruit_collision(struct Player *player, bool fruits[]);
/*
 * Function: check_snakes_collision
 * Description: Checks collision with player and enemy.
 * Arguments:
 *   player - Pointer to the player.
 *   enemy - Pointer to the player's enemy / opponent.
 */
int check_snakes_collision(struct Player *player, struct Player *enemy);
/*
 * Function: check_self_collision
 * Description: Checks collision with player's head and body.
 * Arguments:
 *   player - Pointer to the player.
 */
int check_self_collision(struct Player *player);
/*
 * Function: count_fruits
 * Description: Counts and returns all fruits inside fruits bool array.
 * Arguments:
 *   fruits - Bool array with fruits.
 * Return Value:
 *   Returns a int number of fruits inside array.
 */
int count_fruits(bool fruits[]);
/*
 * Function: place_fruit
 * Description: Places a fruit to the random location to the fruits array.
 * Arguments:
 *   fruits - Bool array with fruits.
 */
int place_fruit(bool fruits[]);
/*
 * Function: check_player_boundary
 * Description: Sets the player to the boundaries of the board.
 * Arguments:
 *   player - Pointer to the player.
 */
int check_player_boundary(struct Player *player);

#endif
