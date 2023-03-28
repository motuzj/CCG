#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

int draw(int w, int h, int** board) {
    printf("\n        _                                                   \n  /\\/\\ (_)_ __   ___  _____      _____  ___ _ __   ___ _ __ \n /    \\| | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|\n/ /\\/\\ \\ | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/ |   \n\\/    \\/_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|   \n                                           |_|              ");
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
                case 0: {
                    int counter = count_mines(board, i, j, w, h);

                    if (counter > 0) {
                        printf("%d", counter);
                    } else {
                        printf(" ");
                    }
                    break;
                }
                case 1:
                case 2:
                    printf("\033[100m\033[30m?\033[0m");
                    break;
                case 3:
                case 4:
                    printf("\033[36mX\033[0m");
                    break;
                case 5:
                case 6:
                    printf("!");
                    break;
                case 7:
                    printf("#");
                    break;
                default:
                    printf("%d", board[i][j]);
                    break;
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

    return 0;
}