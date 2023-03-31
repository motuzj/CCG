#ifndef GAME_H
#define GAME_H

typedef enum {
  CELL_BLANK=0,
  CELL_BLANK_HIDDEN,
  CELL_MINE,
  CELL_MINE_HIDDEN,
  CELL_MARKED,
  CELL_MARKED_MINE
} Cell;
extern Cell **board;

int generate_board(int guessX, int guessY, int w, int h);
int reveal_empty_cells(int x, int y);
int count_mines(Cell **board, int x, int y, int w, int h);
int set_board_size();
int initialize_board();
int run_game();

#endif
