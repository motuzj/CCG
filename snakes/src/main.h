#ifndef MAIN
#define MAIN

#include <stdbool.h>

extern int board_rows;
extern int board_cols;

// options
extern bool disable_borders;

enum Direction {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

enum PlayerState {
    NOT_PLAYING,
    PLAYING,
    DEAD
};

struct Player {
    int head_x; // columns
    int head_y; // rows
    int *body;
    int dir;
    int player_state;
    int score;
    int key_up;
    int key_down;
    int key_left;
    int key_right;
    int color_code;
};

#endif
