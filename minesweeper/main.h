#ifndef MAIN_H
#define MAIN_H

extern int w;
extern int h;
extern int cursorX;
extern int cursorY;
extern int mines;
extern bool playing;
extern int firstGuess;
extern char message[];

typedef enum {
    CELL_BLANK = 0,
    CELL_BLANK_HIDDEN,
    CELL_MINE,
    CELL_MINE_HIDDEN,
    CELL_FLAGGED,
    CELL_FLAGGED_MINE
} Cell;

extern Cell **board;

typedef enum {
    NOT_PLAYING = 0,
    PLAYING,
    RESTART,
    QUIT
} State;

extern State gameState;

#endif