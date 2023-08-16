#ifndef MAIN_H
#define MAIN_H

#include <stdbool.h>

extern int columns;
extern int rows;

typedef struct {
    const char *name;
    const bool is_enemy;
    char texture[10][50]; // texture of spaceship from spaceships.h
    int texture_lines;
    int shields;
    int column; // spaceships column (top left corner)
    int row;    // spaceship row (top left corner)
} Spaceship;

#endif
