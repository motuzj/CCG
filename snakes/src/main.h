#ifndef MAIN
#define MAIN

extern int board_rows;
extern int board_cols;
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
    float head_x; // columns
    float head_y; // rows
    float *body;
    int dir;
    int player_state;
    int score;
    const int key_up;
    const int key_down;
    const int key_left;
    const int key_right;
    const int color_code;
};

#endif
