#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>

#include "draw.h"
#include "main.h"

//
// YOU CAN SET BOARD SIZE IN MAIN.H
//

int board[BOARD_SIZE][BOARD_SIZE];

// get one char; from this: https://stackoverflow.com/a/7469410
int getch() {
    static struct termios old, current;
    char ch;
    tcgetattr(0, &old);         /* grab old terminal i/o settings */
    current = old;              /* make new settings same as old settings */
    current.c_lflag &= ~ICANON; /* disable buffered i/o */
    current.c_lflag &= ~ECHO;   /* set no echo mode */
    tcsetattr(0, TCSANOW, &current);
    ch = getchar();
    tcsetattr(0, TCSANOW, &old);
    return ch;
}

bool process_input(char ch) {
    bool moved = false;

    switch (ch) {
        case 'h':
        case 'D':
        case 'a': // left
            for (int i = 0; i < BOARD_SIZE; i++) {
                bool merged = false;
                for (int j = 1; j < BOARD_SIZE; j++) {
                    if (board[i][j] > 0) {
                        for (int k = j; k > 0; k--) {
                            if (board[i][k - 1] == 0) {
                                board[i][k - 1] = board[i][k];
                                board[i][k] = 0;
                                moved = true;
                            } else if (board[i][k] == board[i][k - 1] && !merged) {
                                board[i][k] = 0;
                                board[i][k - 1] *= 2;
                                merged = true;
                                moved = true;
                            }
                        }
                    }
                }
            }
            break;
        case 'l':
        case 'C':
        case 'd': // right
            for (int i = BOARD_SIZE - 1; i >= 0; i--) {
                bool merged = false;
                for (int j = BOARD_SIZE - 2; j >= 0; j--) {
                    if (board[i][j] > 0) {
                        for (int k = j; k < BOARD_SIZE - 1; k++) {
                            if (board[i][k + 1] == 0) {
                                board[i][k + 1] = board[i][k];
                                board[i][k] = 0;
                                moved = true;
                            } else if (board[i][k] == board[i][k + 1] && !merged) {
                                board[i][k] = 0;
                                board[i][k + 1] *= 2;
                                merged = true;
                                moved = true;
                            }
                        }
                    }
                }
            }
            break;
        case 'k':
        case 'A':
        case 'w': // up
            for (int i = 1; i < BOARD_SIZE; i++) {
                bool merged = false;
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (board[i][j] > 0) {
                        for (int k = i; k > 0; k--) {
                            if (board[k - 1][j] == 0) {
                                board[k - 1][j] = board[k][j];
                                board[k][j] = 0;
                                moved = true;
                            } else if (board[k][j] == board[k - 1][j] && !merged) {
                                board[k][j] = 0;
                                board[k - 1][j] *= 2;
                                merged = true;
                                moved = true;
                            }
                        }
                    }
                }
            }
            break;
        case 'j':
        case 'B':
        case 's': // down
            for (int i = BOARD_SIZE - 2; i >= 0; i--) {
                bool merged = false;
                for (int j = BOARD_SIZE - 1; j >= 0; j--) {
                    if (board[i][j] > 0) {
                        for (int k = i; k < BOARD_SIZE - 1; k++) {
                            if (board[k + 1][j] == 0) {
                                board[k + 1][j] = board[k][j];
                                board[k][j] = 0;
                                moved = true;
                            } else if (board[k][j] == board[k + 1][j] && !merged) {
                                board[k][j] = 0;
                                board[k + 1][j] *= 2;
                                merged = true;
                                moved = true;
                            }
                        }
                    }
                }
            }
            break;
    }
    return moved;
}

int main(int argc, char *argv[]) {
    // fill board with zeros
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = 0;
        }
    }

    srand(time(NULL));
    board[rand() % BOARD_SIZE][rand() % BOARD_SIZE] = 2;

    while (1) {
        while (1) {

            size_t rand_x = rand() % BOARD_SIZE;
            size_t rand_y = rand() % BOARD_SIZE;
            if (board[rand_y][rand_x] == 0) {
                board[rand_y][rand_x] = rand() % 10 == rand() % 10 ? 4 : 2;
                break;
            }
        }
        draw(board, BOARD_SIZE);
        while (!process_input(getch())) {
        }
        system("clear");
    }
    return 0;
}
