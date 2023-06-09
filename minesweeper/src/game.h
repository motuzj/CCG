#ifndef GAME_H
#define GAME_H

#include "main.h"

int arg_set_seed(char arg[]);
int generate_board(int guessX, int guessY, int w, int h);
int reveal_empty_cells(int x, int y);
int count_mines(Cell **board, int x, int y, int w, int h);
int count_cells_with_state(Cell **board, Cell state, int w, int h);
int run_game();

#endif
