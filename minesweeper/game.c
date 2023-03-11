#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#include "draw.h"
#include "game.h"
#include "commands.h"

int mapWidth = 10;
int mapHeight = 10;
int playing = 1;
int firstGuess = 1;

int** map;

int generateMap(int mapWidth, int mapHeight, int guessX, int guessY) {
    srand(time(NULL));
    int mines = mapWidth * mapHeight * 0.18;
    printf("\n%d %d %d", mines, mapWidth, mapHeight);
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

int run_game() {
    if (mapHeight < 2 || mapWidth < 2) {
        printf("\nMap size is too small.\nExiting...\n");
        return 1;
    }
    if (mapHeight > 100 || mapWidth > 100) {
        printf("\nMap size is too big.\nExiting...\n");
        return 1;
    }
    
    map = (int **)calloc(mapHeight, sizeof(int *));
    if (map == NULL) {
        printf("\nNot enough memory to allocate.\nExiting...\n");
        return 1;
    }
    for (int i = 0; i < mapHeight; i++) {
        map[i] = (int *)calloc(mapWidth, sizeof(int));
    }

    while (playing) {
        draw(mapWidth, mapHeight, map);
        processCommand();
    }

    for (int i = 0; i < mapHeight; i++) {
        free(map[i]);
    }
    free(map);

    printf("\n");
    return 0;
}
