#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

int draw(int w, int h, Cell** board) {
    // minesweeper logo ascii
    printf("        _                                                   \n  /\\/\\ (_)_ __   ___  _____      _____  ___ _ __   ___ _ __ \n /    \\| | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|\n/ /\\/\\ \\ | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/ |   \n\\/    \\/_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|   \n                                           |_|              ");
    
    // x coords
    printf("\n    y\\x\t  ");
    for (int i = 0; i < w; i++) {
        if (i >= 10) {
            printf("%d", i);
        } else {
            printf("%d ", i);
        }
    }

    // drawing top table
    printf("\n\t┌");
    for (int i = 0; i < (w * 2 + 1); i++) {
        printf("─");
    }
    printf("┐\n");

    int num = 0;  // numbers for y coords

    // printing minesweeper board
    for (int i = 0; i < h; i++) {
        printf("     %d\t│ ", num);
        for (int j = 0; j < w; j++) {
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
                    printf("\033[100m\033[30m?\033[0m");
                    break;
                }
                case CELL_MARKED:
                case CELL_MARKED_MINE: {
                    printf("\033[36mX\033[0m");
                    break;
                }
                case CELL_MINE: {
                    printf("\033[31m#\033[0m");
                    break;
                }
                default: {
                    printf("?");
                    break;
                }
            }
            printf(" ");
        }
        if (i >= h - 1) {
            printf("│");
            break;
        }
        printf("│\n");
        num++;
    }

    // bottom of table
    printf("\n\t└");
    for (int i = 0; i < (w * 2 + 1); i++) {
        printf("─");
    }
    printf("┘\n");

    printf("%s", message); // print message
    strcpy(message, " "); // clear message

    return 0;
}