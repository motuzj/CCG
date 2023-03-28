#ifndef GAME_H
#define GAME_H

extern int** board;

int generate_board(int w, int h, int guessX, int guessY);
int reveal_empty_cells(int x, int y);
int count_mines(int** board, int x, int y, int w, int h);
int run_game();

#endif
