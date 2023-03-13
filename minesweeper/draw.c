#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

int draw(int mapWidth, int mapHeight, int** map) {
    printf("        _                                                   \n  /\\/\\ (_)_ __   ___  _____      _____  ___ _ __   ___ _ __ \n /    \\| | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|\n/ /\\/\\ \\ | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/ |   \n\\/    \\/_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|   \n                                           |_|              ");
    // x coords
    printf("\n    y\\x\t  ");
    for (int i = 0; i < mapWidth; i++) {
        if (i >= 10) {
            printf("%d", i);
        } else {
            printf("%d ", i);
        }
    }

    // drawing top table
    printf("\n\t┌");
    for (int i = 0; i < (mapWidth * 2 + 1); i++) {
        printf("─");
    }
    printf("┐\n");

    int num = 0;  // numbers for y coords

    // printing minesweeper map/board
    for (int i = 0; i < mapHeight; i++) {
        printf("     %d\t│ ", num);
        for (int j = 0; j < mapWidth; j++) {
            switch (map[i][j]) {
                case 0: {
                    int counter = count_mines(map, i, j, mapWidth, mapHeight);

                    if (counter > 0) {
                        printf("%d ", counter);
                    } else {
                        printf("  ");
                    }
                    break;
                }
                case 1:
                case 2:
                    printf("? ");
                    break;
                case 3:
                case 4:
                    printf("X ");
                    break;
                case 5:
                case 6:
                    printf("! ");
                    break;
                case 7:
                    printf("# ");
                    break;
                case 8:
                    printf("& ");
                    break;
                default:
                    printf("%d ", map[i][j]);
                    break;
            }
        }
        if (i >= mapHeight - 1) {
            printf("│");
            break;
        }
        printf("│\n");
        num++;
    }

    // bottom of table
    printf("\n\t└");
    for (int i = 0; i < (mapWidth * 2 + 1); i++) {
        printf("─");
    }
    printf("┘\n");

    return 0;
}