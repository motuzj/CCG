#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "main.h"

#define MAX_STARS 100

typedef struct {
    int column;
    int row;
} Star;
Star stars[MAX_STARS];

int init_stars() {
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].column = rand() % columns;
        stars[i].row = rand() % rows;
    }
    return 0;
}

int update_stars() {
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].column--;
        if (stars[i].column < 1) {
            stars[i].column = columns;
            stars[i].row = rand() % rows;
        }
    }

    return 0;
}

int draw_stars() {
    for (int i = 0; i < MAX_STARS; i++) {
        printf("\033[%d;%dH", stars[i].row, stars[i].column);
        printf("\033[90m*\033[0m");
    }
    fflush(stdout);
    return 0;
}
