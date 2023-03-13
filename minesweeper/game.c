#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "draw.h"
#include "game.h"
#include "commands.h"

int mapWidth = 15;
int mapHeight = 10;
int playing = 1;
int firstGuess = 1;

int** map;

int generate_map(int mapWidth, int mapHeight, int guessX, int guessY) {
    srand(time(NULL));

    // calculate number of mines to place
    int mines = mapWidth * mapHeight * 0.18;

    // placing mines
    while (mines) {
        int tempx = rand() % mapWidth;
        int tempy = rand() % mapHeight;
        if (map[tempy][tempx] != 2 && !(tempx == guessX && tempy == guessY)) {
            map[tempy][tempx] = 2;
            mines--;
        }
    }
    return 0;
}

int reveal_empty_cells(int x, int y, int counter) {
    // detect if cell was revealed or is out of map
    if (x < 0 || x >= mapWidth || y < 0 || y >= mapHeight || map[y][x] != 1) {
        return 0;
    }
    map[y][x] = 0;

    if (count_mines(map, x, y, mapWidth, mapHeight) > 0) {
        return 0;
    }

    // test for all empty cells
    reveal_empty_cells(x-1, y, counter + 1);
    reveal_empty_cells(x, y-1, counter + 1);
    reveal_empty_cells(x, y+1, counter + 1);
    reveal_empty_cells(x+1, y, counter + 1);

    return 0;
}

int count_mines(int** map, int x, int y, int mapWidth, int mapHeight) {
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

int run_game() {
    // check if map size is not too small or big
    if (mapHeight < 2 || mapWidth < 2) {
        printf("\nMap size is too small.\nExiting...\n");
        return 1;
    }
    if (mapHeight > 100 || mapWidth > 100) {
        printf("\nMap size is too big.\nExiting...\n");
        return 1;
    }
    
    // initiation of map
    map = (int **)calloc(mapHeight, sizeof(int *));
    if (map == NULL) {
        printf("\nNot enough memory to allocate.\nExiting...\n");
        return 1;
    }
    for (int i = 0; i < mapHeight; i++) {
        map[i] = (int *)calloc(mapWidth, sizeof(int));
    }

    // set all numbers in map to 1 (unrevealed, without mines)
    for (int i = 0; i < mapHeight; i++) {
        for (int j = 0; j < mapWidth; j++) {
            map[i][j] = 1;
        }
    }

    // main loop
    while (playing) {
        draw(mapWidth, mapHeight, map);
        process_command();
    }


    // freeing map
    for (int i = 0; i < mapHeight; i++) {
        free(map[i]);
    }
    free(map);

    printf("\n");
    return 0;
}
