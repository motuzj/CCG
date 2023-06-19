#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>

#include "draw.h"
#include "input.h"
#include "main.h"

int board_rows;
int board_cols;

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
    int player_row = (int)player->y;
    int player_col = (int)player->x;

    if (fruits[player_row * board_cols + player_col] == true) {
        player->score += 1;
        fruits[player_row * board_cols + player_col] = false;
    }
    return 0;
}

int set_to_boundaries(struct Player *player) {
    if (player->y < 1) {
        player->y = 1;
    } else if (player->y > board_rows - 3) {
        player->y = board_rows - 3;
    } else if (player->x < 1) {
        player->x = 1;
    } else if (player->x > board_cols - 2) {
        player->x = board_cols - 2;
    }
    return 0;
}

int move_player(struct Player *player) {
    switch (player->dir) {
        case UP: {
            player->y -= 0.5;
            break;
        }
        case DOWN: {
            player->y += 0.5;
            break;
        }
        case LEFT: {
            player->x -= 1;
            break;
        }
        case RIGHT: {
            player->x += 1;
            break;
        }
    }
    set_to_boundaries(player);
    return 0;
}

int main(int argc, char *argv[]) {
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    board_cols = ws.ws_col; // terminal width
    board_rows = ws.ws_row; // terminal height

    bool fruits[board_cols * board_rows]; // if the cell is true it contains a fruit
    for (int i = 0; i < board_cols * board_rows; i++) {
        fruits[i] = false;
    }

    struct Player player1 = {(double)board_cols / 3, (double)board_rows / 2, NONE, PLAYING, 0, 'w', 's', 'a', 'd'};
    struct Player player2 = {(double)board_cols / 3 * 2, (double)board_rows / 2, NONE, PLAYING, 0, 'i', 'k', 'j', 'l'};

    char input_num[5];
    printf("Number of players ( 1 / 2): ");
    if (fgets(input_num, sizeof(input_num), stdin) != NULL) {
        if (atoi(input_num) == 1) {
            player2.player_state = NONE;
        }
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
    return 0;
}
