#include <stdbool.h>
#include <stdio.h>

#include "main.h"

int draw(struct Player player1, struct Player player2, bool fruits[], int frames) {
    printf("\e[1;1H\e[2J"); // clear terminal
    for (int i = 0; i < board_rows - 1; i++) {
        for (int j = 0; j < board_cols; j++) {
            if (i == 0 && j == 0) {
                printf("%5ds%2d", frames, player1.score); // frames counter
                continue;
            }
            if (i == 0 && j <= 7) {
                continue;
            }

            bool printed_body_part = false;

            for (int k = 0; k < i * j; k += 2) {
                if ((int)player1.body[k] == j && (int)player1.body[k + 1] == i) {
                    printf("\033[%dmo\033[0m", player1.color_code);
                    printed_body_part = true;
                    break;
                }
            }

            if (player2.player_state != NONE) {
                for (int k = 0; k < i * j; k += 2) {
                    if ((int)player2.body[k] == j && (int)player2.body[k + 1] == i) {
                        printf("\033[%dmo\033[0m", player2.color_code);
                        printed_body_part = true;
                        break;
                    }
                }
            }

            if (printed_body_part) {
                continue;
            }

            if (i == 0 || i == board_rows - 2 || j == 0 || j == board_cols - 1) {
                printf("#");
            } else if (i == (int)player1.head_y && j == (int)player1.head_x && player1.player_state != NONE) {
                printf("\033[%dmO\033[0m", player1.color_code);
            } else if (i == (int)player2.head_y && j == (int)player2.head_x && player2.player_state != NONE) {
                printf("\033[%dmO\033[0m", player2.color_code);
            } else if (fruits[i * board_cols + j] == true) {
                printf("\033[41mX\033[0m");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}
