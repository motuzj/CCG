#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <time.h>
#include <unistd.h>

#include "draw.h"
#include "input.h"
#include "main.h"

int board_rows;
int board_cols;

// options
bool disable_borders = false;

int initialize_body(struct Player *player) {
    player->body = (float *)calloc(board_cols * board_rows, sizeof(float));
    if (player->body == NULL) {
        printf("\nError: Not enough memory to allocate.\nExiting...\n");
        free(player->body);
        return 1;
    }

    player->body[0] = player->head_x - 1;
    player->body[1] = player->head_y;

    player->body[2] = player->head_x - 2;
    player->body[3] = player->head_y;

    player->body[4] = player->head_x - 3;
    player->body[5] = player->head_y;

    player->body[6] = player->head_x - 3;
    player->body[7] = player->head_y;
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

int check_fruit_collision(struct Player *player, bool fruits[]) {
    int player_row = (int)player->head_y;
    int player_col = (int)player->head_x;

    if (fruits[player_row * board_cols + player_col] == true) {
        player->score += 1;
        fruits[player_row * board_cols + player_col] = false;

        // add +1 size to body
        for (int i = board_cols * board_rows; i >= 0; i--) {
            if (player->body[i] != 0) {
                player->body[i + 1] = player->body[i];     // y
                player->body[i + 2] = player->body[i - 1]; // x
                break;
            }
        }
    }
    return 0;
}

int check_player_collision(struct Player *player, bool fruits[]) {
    // collision with wall
    // TODO
    return 0;
}

int set_to_boundaries(struct Player *player) {
    if (disable_borders) {
        if (player->head_y < 1) {
            player->head_y = board_rows - 3;
        } else if (player->head_y > board_rows - 3) {
            player->head_y = 1;
        } else if (player->head_x < 1) {
            player->head_x = board_cols - 2;
        } else if (player->head_x > board_cols - 2) {
            player->head_x = 1;
        }
    } else {
        if (player->head_y < 1) {
            player->head_y = 1;
        } else if (player->head_y > board_rows - 3) {
            player->head_y = board_rows - 3;
        } else if (player->head_x < 1) {
            player->head_x = 1;
        } else if (player->head_x > board_cols - 2) {
            player->head_x = board_cols - 2;
        }
    }
    return 0;
}

int move_player(struct Player *player) {
    // body
    if (player->dir != NONE) {
        int counter = 0;
        for (int i = (board_cols * board_rows); i >= 2; i -= 2) {
            if (player->body[i] != 0) {
                player->body[i] = player->body[i - 2];
                player->body[i - 1] = player->body[i - 3];
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
    set_to_boundaries(player);
    return 0;
}

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "b")) != -1) {
        switch (opt) {
            case 'b':
                disable_borders = true;
                break;
        }
    }

    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    board_cols = ws.ws_col; // terminal width
    board_rows = ws.ws_row; // terminal height

    bool fruits[board_cols * board_rows]; // if the cell is true it contains a fruit
    for (int i = 0; i < board_cols * board_rows; i++) {
        fruits[i] = false;
    }

    struct Player player1 = {(float)board_cols / 3, (float)board_rows / 2, NULL, NONE, PLAYING, 0, 'w', 's', 'a', 'd', 32};
    struct Player player2 = {(float)board_cols / 3 * 2, (float)board_rows / 2, NULL, NONE, PLAYING, 0, 'i', 'k', 'j', 'l', 92};

    char input_chars[5];
    int input_num;
    printf("Number of players ( 1 / 2 ): ");
    if (fgets(input_chars, sizeof(input_num), stdin) != NULL) {
        input_num = atoi(input_chars);
        if (input_num == 1) {
            player2.player_state = NONE;
        }
    }

    initialize_body(&player1);

    if (player2.player_state != NONE) {
        initialize_body(&player2);
    }

    enableRawMode();

    int frames = 0;

    while (1) {
        if (frames % 80 == 0 && count_fruits(fruits) < 6) {
            place_fruit(fruits);
        }
        check_fruit_collision(&player1, fruits);
        check_fruit_collision(&player2, fruits);
        int input = get_input(&player1);
        if (input > 0) {
            process_input(&player1, input);
            process_input(&player2, input);
        } else if (input == -1) {
            return 1;
        }
        draw(player1, player2, fruits, frames);
        move_player(&player1);
        move_player(&player2);
        frames++;
    }
    free(&player1);
    if (player2.player_state != NONE) {
        free(&player2);
    }
    return 0;
}
