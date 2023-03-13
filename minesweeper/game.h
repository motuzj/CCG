#ifndef GAME_H
#define GAME_H

extern int** map;

int generate_map(int mapWidth, int mapHeight, int guessX, int guessY);
int reveal_empty_cells(int x, int y, int counter);
int count_mines(int** map, int x, int y, int mapWidth, int mapHeight);
int run_game();

#endif
