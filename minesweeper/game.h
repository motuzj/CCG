#ifndef GAME_H
#define GAME_H

#include "main.h"

int generate_board(int guessX, int guessY, int w, int h);
int reveal_empty_cells(int x, int y);
int reveal_all_mines(Cell **board, int w, int h);
int count_mines(Cell **board, int x, int y, int w, int h);
int count_cells_with_state(Cell **board, Cell state, int w, int h);
int set_board_size();
int initialize_board();
int free_board(Cell **board, int h);
int run_game();

#endif
