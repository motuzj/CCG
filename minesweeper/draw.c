#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

// returns text for priniting it on side
char *printMessage(int y) {
    switch (y) {
        case 0: {
            return "M I N E S W E E P E R";
            break;
        }
        case 1: {
            return "---------------------";
            break;
        }
        case 2: {
            return "[SPACE] reveal a cell";
            break;
        }
        case 3: {
            return "f       flag a mine";
            break;
        }
        case 4: {
            return "press ? for help";
            break;
        }
        default: {
            return "";
            break;
        }
    }
}

int draw(int w, int h, Cell **board) {
    // drawing top table
    printf("┌");
    for (int i = 0; i < (w * 2 + 1); i++) {
        printf("─");
    }
    printf("┐\t\n");

    // printing minesweeper board
    for (int i = 0; i < h; i++) {
        printf("│ ");
        for (int j = 0; j < w; j++) {
            if (i == cursorY && j == cursorX && (board[i][j] == CELL_BLANK_HIDDEN || board[i][j] == CELL_MINE_HIDDEN)) {
                printf("\033[47m\033[30m");
            } else if (board[i][j] == CELL_BLANK_HIDDEN || board[i][j] == CELL_MINE_HIDDEN) {
                printf("\033[100m\033[30m");
            } else if (i == cursorY && j == cursorX) {
                printf("\033[100m");
            }
            switch (board[i][j]) {
                case CELL_BLANK: {
                    int counter = count_mines(board, i, j, w, h);

                    if (counter > 0) {
                        printf("%d", counter);
                    } else {
                        printf(" ");
                    }
                    break;
                }
                case CELL_BLANK_HIDDEN:
                case CELL_MINE_HIDDEN: {
                    printf("?");
                    break;
                }
                case CELL_FLAGGED:
                case CELL_FLAGGED_MINE: {
                    printf("\033[36mX");
                    break;
                }
                case CELL_MINE: {
                    printf("\033[91m#");
                    break;
                }
                default: {
                    printf("?");
                    break;
                }
            }
            printf("\033[0m ");
        }
        printf("│  %s\n", printMessage(i));
    }

    // bottom of table
    printf("└");
    for (int i = 0; i < (w * 2 + 1); i++) {
        printf("─");
    }
    printf("┘\n");

    printf("%s\n", message); // print message
    strcpy(message, " ");    // clear message

    return 0;
}