#include <stdio.h>
#include <stdlib.h>

#include "board.h"
#include "draw.h"
#include "help.h"
#include "input.h"
#include "main.h"
#include "player.h"

int run_game() {
    welcome_message();

    // fruits initialization
    bool fruits[board_cols * board_rows]; // if the cell is true it contains a fruit
    for (int i = 0; i < board_cols * board_rows; i++) {
        fruits[i] = false;
    }

    place_fruit(fruits); // place first fruit

    struct Player player1 = {
        .head_x = board_cols / 3,
        .head_y = board_rows / 2,
        .tail_x = 0,
        .tail_y = 0,
        .body = NULL,
        .body_length = 4,
        .dir = NONE,
        .player_state = PLAYING,
        .score = 0,
        .key_up = 'w',
        .key_down = 's',
        .key_left = 'a',
        .key_right = 'd',
        .color_code = 32};

    struct Player player2 = {
        .head_x = board_cols / 3 * 2,
        .head_y = board_rows / 2,
        .tail_x = 0,
        .tail_y = 0,
        .body = NULL,
        .body_length = 4,
        .dir = NONE,
        .player_state = PLAYING,
        .score = 0,
        .key_up = 'i',
        .key_down = 'k',
        .key_left = 'j',
        .key_right = 'l',
        .color_code = 92};

    initialize_body(&player1);

    char input_chars[5];
    int input_num;
    printf("Number of players ( 1 / 2 ): ");
    if (fgets(input_chars, sizeof(input_num), stdin) != NULL) {
        input_num = atoi(input_chars);
        if (input_num == 1) {
            player2.player_state = NOT_PLAYING;
        } else {
            initialize_body(&player2);
        }
    }

    enableRawMode();

    change_controls(&player1, &player2);

    int frames = 0; // counts every redraw
    while (1) {
        check_fruit_collision(&player1, fruits);
        check_fruit_collision(&player2, fruits);

        // get user input, if there is any, and process it
        int input = get_input(&player1);
        if (input > 0) {
            process_input(&player1, input);
            process_input(&player2, input);
        } else if (input == -1) {
            return 1;
        }

        // move player +1 in it's dir
        move_player(&player1);
        move_player(&player2);

        // draw frame
        draw(player1, player2, fruits);

        // check if the first player crashed into himself
        check_self_collision(&player1);

        // check if the second player crashed into himself or if either player has crashed into an opposing player
        if (player2.player_state != NOT_PLAYING) {
            check_self_collision(&player2);
            check_snakes_collision(&player1, &player2);
            check_snakes_collision(&player2, &player1);
        }

        if (player1.player_state == DEAD && player2.player_state == DEAD) { // if 2 players were playing
            if (player1.score != player2.score) {                           // one player has bigger score
                printf("Player %s has won!\n", (player1.score > player2.score ? "1" : "2"));
            } else { // players have same score
                printf("Both players got the same score!\n");
            }

            // print scores
            printf("\nPlayer 1: %d\nPlayer 2: %d\n", player1.score, player2.score);
            break;
        } else if (player1.player_state == DEAD && player2.player_state == NOT_PLAYING) { // if 1 player was playing
            printf("You have lost!\nYour score: %d\n", player1.score);
            break;
        }

        // set direction to none to dead players
        if (player1.player_state == DEAD) {
            player1.dir = NONE;
        }
        if (player2.player_state == DEAD) {
            player2.dir = NONE;
        }

        frames++;
    }
    return 0;
}
