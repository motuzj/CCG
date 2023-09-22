#include <stdbool.h>
#include <stdio.h>

#include "main.h"

int draw(struct Player player1, struct Player player2, bool fruits[]) {
    printf("\033[1;1H\033[2J"); // clear terminal

    // print top border
    for (int i = 0; i < board_cols + 2; i++) {
        printf("#");
    }
    printf("\n");

    for (int i = 0; i < board_rows; i++) {
        printf("#");
        for (int j = 0; j < board_cols; j++) {

            // print player 1 body
            for (int k = 0; k < player1.body_length * 2; k += 2) {
                if (player1.body[k] == j && player1.body[k + 1] == i) {
                    printf("\033[%dmo\033[0m", player1.color_code);
                    goto next_line;
                }
            }

            // print player 2 body
            if (player2.player_state != NOT_PLAYING) {
                for (int k = 0; k < player2.body_length * 2; k += 2) {
                    if (player2.body[k] == j && player2.body[k + 1] == i) {
                        printf("\033[%dmo\033[0m", player2.color_code);
                        goto next_line;
                    }
                }
            }

            if (i == player1.head_y && j == player1.head_x && player1.player_state != NONE) {
                printf("\033[%dmO\033[0m", player1.color_code); // print player 1 head
            } else if (i == player2.head_y && j == player2.head_x && player2.player_state != NONE) {
                printf("\033[%dmO\033[0m", player2.color_code); // print player 2 head
            } else if (fruits[i * board_cols + j] == true) {
                printf("\033[41mX\033[0m"); // print fruit
            } else {
                printf(" ");
            }
        next_line:; // for some reason I need to add ";" or my IDE will mark it as syntax error
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
