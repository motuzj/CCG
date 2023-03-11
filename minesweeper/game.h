#ifndef GAME_H
#define GAME_H

extern int** map;

int generateMap(int mapWidth, int mapHeight, int guessX, int guessY);
int run_game();

#endif
