#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int countMines(int** map, int x, int y, int mapWidth, int mapHeight) {
    int minesCounter = 0;

    for (int k = x - 1; k <= x + 1; k++) {
        for (int l = y - 1; l <= y + 1; l++) {
            // Skip out-of-bounds cells
            if (k < 0 || k >= mapHeight || l < 0 || l >= mapWidth) {
                continue;
            }
            // Check if the cell has a mine
            if (map[k][l] == 2 || map[k][l] == 4 || map[k][l] == 6 || map[k][l] == 7) {
                minesCounter++;
            }
        }
    }

    return minesCounter;
}

int draw(int mapWidth, int mapHeight, int** map) {
    printf("\e[1;1H\e[2J");
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

    int num = 0;  // y coords

    // printing minesweeper numbers table
    for (int i = 0; i < mapHeight; i++) {
        printf("     %d\t│ ", num);
        for (int j = 0; j < mapWidth; j++) {
            switch (map[i][j]) {
                case 0: {
                    int counter = countMines(map, i, j, mapWidth, mapHeight);

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

    printf("\n\t└");
    for (int i = 0; i < (mapWidth * 2 + 1); i++) {
        printf("─");
    }
    printf("┘\n");

    return 0;
}