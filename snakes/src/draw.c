#include <stdbool.h>
#include <stdio.h>

#include "main.h"

int draw(struct Player player1, struct Player player2, bool fruits[], int frames) {
    printf("\e[1;1H\e[2J");
    for (int i = 0; i < board_rows - 1; i++) {
        for (int j = 0; j < board_cols; j++) {
            if (i == 0 && j == 0) {
                printf("%5d", frames);
                continue;
            }
            if (i == 0 && j <= 4) {
                continue;
            }
            if (i == 0 || i == board_rows - 2 || j == 0 || j == board_cols - 1) {
                printf("#");
            } else if ((i == (int)player1.y && j == (int)player1.x && player1.player_state != NONE) || (i == (int)player2.y && j == (int)player2.x && player2.player_state != NONE)) {
                printf("O");
            } else if (fruits[i * board_cols + j] == true) {
                printf("X");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
