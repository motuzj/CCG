#ifndef GAME_H
#define GAME_H

#include "main.h"

int arg_set_seed(char arg[]);
void generate_board(int guess_x, int guess_y);
void reveal_empty_cells(int x, int y);
int count_nearby_mines(int x, int y);
int count_cells_with_state(Cell state);
int run_game(void);

#endif
