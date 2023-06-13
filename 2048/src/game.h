#ifndef GAME_H
#define GAME_H

/*
 * Function: process_input
 * Description: Process input and move with tiles.
 * Arguments:
 *   ch - input character that was pressed.
 *   board - Pointer to 2D array board.
 *   side_size - Length of one side of board.
 */
bool process_input(char ch, int **board, int side_size);

/*
 * Function: is_game_won
 * Description: Returns true or false depending on if game is won.
 * Arguments:
 *   board - Pointer to 2D array board.
 *   side_size - Length of one side of board.
 * Return Value:
 *   Returns a true if player won, false if not.
 */
bool is_game_won(int **board, int side_size);

/*
 * Function: is_game_over
 * Description: Returns true or false depending on if game is over.
 * Arguments:
 *   board - Pointer to 2D array board.
 *   side_size - Length of one side of board.
 * Return Value:
 *   Returns a true if player lost and can't move with tiles, false if he can still play.
 */
bool is_game_over(int **board, int side_size);

/*
 * Function: place_random
 * Description: Place a 2 or 4 at random place on board.
 * Arguments:
 *   board - Pointer to 2D array board.
 *   side_size - Length of one side of board.
 */
int place_random(int **board, int side_size);

/*
 * Function: initialize_board
 * Description: Initialize a game board.
 * Arguments:
 *   board - Pointer to 2D array board.
 *   side_size - Length of one side of board.
 */
int initialize_board(int ***board, int side_size);

/*
 * Function: free_board
 * Description: Frees a game board.
 * Arguments:
 *   board - Pointer to 2D array board.
 *   side_size - Length of one side of board.
 */
int free_board(int **board, int side_size);

/*
 * Function: getch
 * Description: Reads single char and rutns it immediately without echoing.
 * Return Value:
 *   Returns a single character.
 */
int getch();

#endif
