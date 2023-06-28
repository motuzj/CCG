#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"

int initialize_body(struct Player *player) {
    player->body = NULL;
    player->body = (int *)calloc(board_cols * board_rows, sizeof(int));
    if (player->body == NULL) {
        fprintf(stderr, "\nError: Not enough memory to allocate.\nExiting...\n");
        return 1;
    }
    for (int i = 0; i < board_cols * board_rows; i++) {
        player->body[i] = -1;
    }

    for (int i = 0; i <= 7; i += 2) {
        player->body[i] = player->head_x - ((i / 2) + 1);
        player->body[i + 1] = player->head_y;
    }
    return 0;
}

int _change_controls(struct Player *player, int player_number) {
    char ans[2];
    printf("\nDo you want to change controls for player %d ( y / N): ", player_number);
    if (fgets(ans, sizeof(ans), stdin) != NULL) {
        if (ans[0] == 'Y' || ans[0] == 'y') {
            printf("\nPress key for UP: ");
            player->key_up = getchar();
            printf("\nPress key for DOWN: ");
            player->key_down = getchar();
            printf("\nPress key for LEFT: ");
            player->key_left = getchar();
            printf("\nPress key for RIGHT: ");
            player->key_right = getchar();
        }
    }
    return 0;
}

int change_controls(struct Player *player1, struct Player *player2) {
    char ans[2];
    printf("Do you want to change the controls for the players ( y / N): ");
    if (fgets(ans, sizeof(ans), stdin) != NULL) {
        if (ans[0] == 'Y' || ans[0] == 'y') {
            _change_controls(player1, 1);
            if (player2->player_state != NOT_PLAYING) {
                _change_controls(player2, 2);
            }
        }
    }
    return 0;
}

int move_player(struct Player *player) {
    if (player->player_state != PLAYING) {
        return 0;
    }

    // body
    if (player->dir != NONE) {
        for (int i = (board_cols * board_rows) - 1; i > 0; i -= 2) {
            if (player->body[i] != -1) {
                int temp_x = player->body[i];
                int temp_y = player->body[i - 1];
                player->body[i] = player->body[i - 2];
                player->body[i - 1] = player->body[i - 3];
                player->body[i - 2] = temp_x;
                player->body[i - 3] = temp_y;
            }
        }
        player->body[0] = player->head_x;
        player->body[1] = player->head_y;
    }

    // head
    switch (player->dir) {
        case UP: {
            player->head_y -= 1;
            break;
        }
        case DOWN: {
            player->head_y += 1;
            break;
        }
        case LEFT: {
            player->head_x -= 1;
            break;
        }
        case RIGHT: {
            player->head_x += 1;
            break;
        }
    }

    check_player_boundary(player);
    return 0;
}
