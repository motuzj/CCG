#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>

#include "main.h"

bool process_input(char ch, int **board, int side_size) {
    bool moved = false;

    switch (ch) {
        case 'h':
        case 'D':
        case 'a': // left
            for (int i = 0; i < side_size; i++) {
                bool merged = false;
                for (int j = 1; j < side_size; j++) {
                    if (board[i][j] > 0) {
                        for (int k = j; k > 0; k--) {
                            if (board[i][k - 1] == 0) {
                                board[i][k - 1] = board[i][k];
                                board[i][k] = 0;
                                moved = true;
                            } else if (board[i][k] == board[i][k - 1] && !merged) {
                                board[i][k] = 0;
                                board[i][k - 1] *= 2;
                                score += board[i][k - 1];
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
            for (int i = side_size - 1; i >= 0; i--) {
                bool merged = false;
                for (int j = side_size - 2; j >= 0; j--) {
                    if (board[i][j] > 0) {
                        for (int k = j; k < side_size - 1; k++) {
                            if (board[i][k + 1] == 0) {
                                board[i][k + 1] = board[i][k];
                                board[i][k] = 0;
                                moved = true;
                            } else if (board[i][k] == board[i][k + 1] && !merged) {
                                board[i][k] = 0;
                                board[i][k + 1] *= 2;
                                score += board[i][k + 1];
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
            for (int i = 1; i < side_size; i++) {
                for (int j = 0; j < side_size; j++) {
                    bool merged = false;
                    if (board[i][j] > 0) {
                        for (int k = i; k > 0; k--) {
                            if (board[k - 1][j] == 0) {
                                board[k - 1][j] = board[k][j];
                                board[k][j] = 0;
                                moved = true;
                            } else if (board[k][j] == board[k - 1][j] && !merged) {
                                board[k][j] = 0;
                                board[k - 1][j] *= 2;
                                score += board[k - 1][j];
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
            for (int i = side_size - 2; i >= 0; i--) {
                for (int j = side_size - 1; j >= 0; j--) {
                    bool merged = false;
                    if (board[i][j] > 0) {
                        for (int k = i; k < side_size - 1; k++) {
                            if (board[k + 1][j] == 0) {
                                board[k + 1][j] = board[k][j];
                                board[k][j] = 0;
                                moved = true;
                            } else if (board[k][j] == board[k + 1][j] && !merged) {
                                board[k][j] = 0;
                                board[k + 1][j] *= 2;
                                score += board[k + 1][j];
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

bool is_game_over(int **board, int side_size) {
    // check if there are any empty cells
    for (int i = 0; i < side_size; i++) {
        for (int j = 0; j < side_size; j++) {
            if (board[i][j] == 0) {
                return false; // there is an empty cell
            }
        }
    }

    // check if there are any cells with the same value
    for (int i = 0; i < side_size; i++) {
        for (int j = 0; j < side_size; j++) {
            if (j < side_size - 1 && board[i][j] == board[i][j + 1]) {
                return false;
            }
            if (i < side_size - 1 && board[i][j] == board[i + 1][j]) {
                return false;
            }
        }
    }

    return true; // game over - no empty cells and no other cells with the same value
}

bool is_game_won(int **board, int side_size) {
    for (int i = 0; i < side_size; i++) {
        for (int j = 0; j < side_size; j++) {
            if (board[i][j] >= 2048) {
                return true;
            }
        }
    }
    return false;
}

int place_random(int **board, int side_size) {
    srand(time(NULL));
    while (1) {
        int rand_x = rand() % side_size;
        int rand_y = rand() % side_size;
        if (board[rand_y][rand_x] == 0) {
            board[rand_y][rand_x] = rand() % 10 == rand() % 10 ? 4 : 2;
            return 0;
        }
    }
}

int initialize_board(int ***board, int side_size) {
    *board = (int **)calloc(side_size, sizeof(int *));
    if (*board == NULL) {
        fprintf(stderr, "\nError: Not enough memory to allocate.\nExiting...\n");
        return 1;
    }
    for (int i = 0; i < side_size; i++) {
        (*board)[i] = (int *)calloc(side_size, sizeof(int));
        if ((*board)[i] == NULL) {
            fprintf(stderr, "\nError: Not enough memory to allocate.\nExiting...\n");
            return 1;
        }
    }

    return 0;
}

int free_board(int **board, int side_size) {
    for (int i = 0; i < side_size; i++) {
        free(board[i]);
    }
    free(board);
    return 0;
}

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
