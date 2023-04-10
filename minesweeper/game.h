#ifndef GAME_H
#define GAME_H

extern int w;
extern int h;
extern int cursorX;
extern int cursorY;
extern int mines;
extern bool playing;
extern int firstGuess;
extern char message[];

typedef enum {
  CELL_BLANK=0,
  CELL_BLANK_HIDDEN,
  CELL_MINE,
  CELL_MINE_HIDDEN,
  CELL_FLAGGED,
  CELL_FLAGGED_MINE
} Cell;

extern Cell** board;

typedef enum {
  NOT_PLAYING=0,
  PLAYING,
  RESTART,
  QUIT
} State;

extern State gameState;

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
