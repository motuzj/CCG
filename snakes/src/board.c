#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "main.h"

int check_fruit_collision(struct Player *player, bool fruits[]) {
    int player_row = player->head_y;
    int player_col = player->head_x;

    if (fruits[player_row * board_cols + player_col] == true) {
        player->score++;
        player->body_length++;
        fruits[player_row * board_cols + player_col] = false;

        // add +1 size to body
        player->body = (int *)realloc(player->body, 2 * player->body_length * sizeof(int));
        player->body[(player->body_length - 1) * 2] = player->tail_x;
        player->body[(player->body_length - 1) * 2 + 1] = player->tail_y;
    }
    return 0;
}

int check_snakes_collision(struct Player *player, struct Player *enemy) {
    for (int i = 0; i < enemy->body_length * 2; i += 2) {
        if ((player->head_x == enemy->body[i] && player->head_y == enemy->body[i + 1]) ||
            (player->head_x == enemy->head_x && player->head_y == enemy->head_y)) {
            player->player_state = DEAD;
            break;
        }
    }
    return 0;
}

int check_self_collision(struct Player *player) {
    for (int i = 0; i < player->body_length * 2; i += 2) {
        if (player->head_x == player->body[i] && player->head_y == player->body[i + 1]) {
            player->player_state = DEAD;
            break;
        }
    }
    return 0;
}

int count_fruits(bool fruits[]) {
    int counter = 0;
    for (int i = 0; i < board_rows * board_cols; i++) {
        if (fruits[i] == true) {
            counter++;
        }
    }
    return counter;
}

int place_fruit(bool fruits[]) {
    srand(time(NULL));

    int rand_row;
    int rand_col;
    do {
        rand_col = rand() % (board_cols - 2) + 1;
        rand_row = rand() % (board_rows - 2);
    } while (fruits[rand_row * board_cols + rand_col] == true);
    fruits[rand_row * board_cols + rand_col] = true;
    return 0;
}

int check_player_boundary(struct Player *player) {
    if (disable_borders) {
        if (player->head_y < 0) {
            player->head_y = board_rows - 1;
        } else if (player->head_y > board_rows - 1) {
            player->head_y = 0;
        } else if (player->head_x < 0) {
            player->head_x = board_cols - 1;
        } else if (player->head_x > board_cols - 1) {
            player->head_x = 0;
        }
    } else {
        if (player->head_y < 0) {
            player->head_y = 0;
            player->player_state = DEAD;
        } else if (player->head_y > board_rows - 1) {
            player->head_y = board_rows - 1;
            player->player_state = DEAD;
        } else if (player->head_x < 0) {
            player->head_x = 0;
            player->player_state = DEAD;
        } else if (player->head_x > board_cols - 1) {
            player->head_x = board_cols - 1;
            player->player_state = DEAD;
        }
    }
    return 0;
}
