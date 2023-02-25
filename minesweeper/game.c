#include <stdlib.h>
#include <stdio.h>

#include "draw.h"
#include "game.h"
#include "commands.h"

int mapWidth = 10;
int mapHeight = 10;
int playing = 1;
int firstGuess = 1;

int** map;

int run_game() {
    printf("        _                                                   \n  /\\/\\ (_)_ __   ___  _____      _____  ___ _ __   ___ _ __ \n /    \\| | '_ \\ / _ \\/ __\\ \\ /\\ / / _ \\/ _ \\ '_ \\ / _ \\ '__|\n/ /\\/\\ \\ | | | |  __/\\__ \\\\ V  V /  __/  __/ |_) |  __/ |   \n\\/    \\/_|_| |_|\\___||___/ \\_/\\_/ \\___|\\___| .__/ \\___|_|   \n                                           |_|              ");
    map = (int **)malloc(mapHeight * sizeof(int *));
    for (int i = 0; i < mapHeight; i++) {
        map[i] = (int *)calloc(mapWidth, sizeof(int));
    }
    map[3][2] = 2;
    map[1][1] = 2;

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