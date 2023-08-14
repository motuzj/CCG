#ifndef MAIN
#define MAIN

#include <stdbool.h>

extern int board_rows;
extern int board_cols;

// options
extern bool disable_borders;
extern int option_speed;

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
    int head_x;       // columns
    int head_y;       // rows
    int tail_x;       // tail x coordinates (mainly used for debugging)
    int tail_y;       // tail y coordinates (mainly used for debugging)
    int *body;        // [0] -> 1. body part x coord (columns), [1] -> 1. body part y coord (rows), ....
    int body_length;  // length of body (without head and with tail)
    int dir;          // direction in enum Direction format
    int player_state; // player state in enum PlayerState format
    int score;        // score of the player
    int key_up;       // ascii character representation for keyup
    int key_down;     // ascii character representation for keydown
    int key_left;     // ascii character representation for keyleft
    int key_right;    // ascii character representation for keyright
    int color_code;   // foreground ansi color code (https://en.wikipedia.org/wiki/ANSI_escape_code#3-bit_and_4-bit)
};

#endif
