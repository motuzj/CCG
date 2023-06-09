#ifndef MAIN_H
#define MAIN_H

extern int w;             // board width / max x coords
extern int h;             // board height / max y coords
extern int cursorX;       // position of cursor x coords
extern int cursorY;       // position of cursor y coords
extern int first_cursorX; // position of cursor x coords
extern int first_cursorY; // position of cursor y coords
extern int mines;         // number of mines
extern unsigned int seed; // random number for generating map
extern bool playing;      // true if playing false when not
extern bool firstGuess;   // true if first guess wasn't made yet
extern char message[];    // message that will be printed during draw()

// options

extern bool custom_seed; // true if custom seed is provided
extern bool minimal;     // minimal option (no text, only gameboard)

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
