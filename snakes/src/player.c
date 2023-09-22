#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "board.h"

int initialize_body(struct Player *player) {
    player->body = NULL;
    player->body = (int *)calloc(player->body_length * 2, sizeof(int));
    if (player->body == NULL) {
        fprintf(stderr, "\nError: Not enough memory to allocate.\nExiting...\n");
        return 1;
    }
    for (int i = 0; i < player->body_length * 2; i += 2) {
        player->body[i] = player->head_x - (i / 2) - 1;
        player->body[i + 1] = player->head_y;
    }

    // set tail coords to last element of player->body
    player->tail_x = player->body[sizeof(player->body) / sizeof(player->body[0]) - 2];
    player->tail_y = player->body[sizeof(player->body) / sizeof(player->body[0]) - 1];
    return 0;
}

int free_body(struct Player *player) {
    free(player->body);
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

    // move head
    int new_head_x = player->head_x;
    int new_head_y = player->head_y;

    switch (player->dir) {
        case UP: {
            new_head_y -= 1;
            break;
        }
        case DOWN: {
            new_head_y += 1;
            break;
        }
        case LEFT: {
            new_head_x -= 1;
            break;
        }
        case RIGHT: {
            new_head_x += 1;
            break;
        }
    }

    // move body
    int prev_head_x = player->head_x;
    int prev_head_y = player->head_y;
    player->head_x = new_head_x;
    player->head_y = new_head_y;

    if (player->dir != NONE) {
        for (int i = 0; i < player->body_length * 2; i += 2) {
            int temp_x = player->body[i];
            int temp_y = player->body[i + 1];
            player->body[i] = prev_head_x;
            player->body[i + 1] = prev_head_y;
            prev_head_x = temp_x;
            prev_head_y = temp_y;
        }
    }

    // update tail coords
    player->tail_x = player->body[(player->body_length - 1) * 2];
    player->tail_y = player->body[(player->body_length - 1) * 2 + 1];

    check_player_boundary(player);
    return 0;
}
