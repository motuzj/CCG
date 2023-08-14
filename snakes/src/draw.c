#include <stdbool.h>
#include <stdio.h>

#include "main.h"

int draw(struct Player player1, struct Player player2, bool fruits[]) {
    printf("\e[1;1H\e[2J"); // clear terminal

    // print top border
    for (int i = 0; i < board_cols + 2; i++) {
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < board_rows; i++) {
        printf("#");
        for (int j = 0; j < board_cols; j++) {
            bool printed_body_part = false;

            for (int k = 0; k < player1.body_length * 2; k += 2) {
                if (player1.body[k] == j && player1.body[k + 1] == i) {
                    printf("\033[%dmo\033[0m", player1.color_code);
                    printed_body_part = true;
                    break;
                }
            }

            if (printed_body_part) {
                continue;
            }

            if (player2.player_state != NOT_PLAYING) {
                for (int k = 0; k < player2.body_length * 2; k += 2) {
                    if (player2.body[k] == j && player2.body[k + 1] == i) {
                        printf("\033[%dmo\033[0m", player2.color_code);
                        printed_body_part = true;
                        break;
                    }
                }
            }

            if (printed_body_part) {
                continue;
            }

            if (i == player1.head_y && j == player1.head_x && player1.player_state != NONE) {
                printf("\033[%dmO\033[0m", player1.color_code);
            } else if (i == player2.head_y && j == player2.head_x && player2.player_state != NONE) {
                printf("\033[%dmO\033[0m", player2.color_code);
            } else if (fruits[i * board_cols + j] == true) {
                printf("\033[41mX\033[0m");
            } else {
                printf(" ");
            }
        }
        printf("#\n");
    }

    // print bottom border
    for (int i = 0; i < board_cols + 2; i++) {
        printf("#");
    }

    printf("\n");

    return 0;
}
