#ifndef GAME_H
#define GAME_H

extern int** board;

int generate_board(int guessX, int guessY, int w, int h);
int reveal_empty_cells(int x, int y);
int count_mines(int** board, int x, int y, int w, int h);
int set_board_size();
int initialize_board();
int run_game();

#endif
