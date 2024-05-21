#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "main.h"

#define MAX_STARS 100

typedef struct {
    double column;
    int row;
    double speed;
} Star;
Star stars[MAX_STARS];

void init_stars(void) {
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].column = (int)(rand() % columns);
        stars[i].row = rand() % rows;
        stars[i].speed = 0.1 + ((double)rand() / RAND_MAX) * 2.0;
    }
}

void update_stars(void) {
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].column -= stars[i].speed;
        if (stars[i].column < 1.0) {
            stars[i].column = columns;
            stars[i].row = rand() % rows;
        }
    }
}

void draw_stars(void) {
    for (int i = 0; i < MAX_STARS; i++) {
        printf("\033[%d;%dH", stars[i].row, (int)stars[i].column);
        printf("\033[90m*\033[0m");
    }
    fflush(stdout);
}
