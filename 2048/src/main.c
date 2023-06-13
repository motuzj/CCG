#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "draw.h"
#include "game.h"

// GLOBAL VARIABLES/OPTIONS
unsigned long score = 0; // score counter
bool minimal = false;

int main(int argc, char *argv[]) {
    int **board = NULL;
    int side_size = 4; // default size of the board

    bool endless = false; // endless mode, you can loose, but can't win

    int opt;
    while ((opt = getopt(argc, argv, "s:em")) != -1) {
        switch (opt) {
            case 's': {
                int arg_side_size = atoi(optarg);
                if (arg_side_size > 1) {
                    side_size = arg_side_size;
                }
                break;
            }
            case 'e': {
                endless = true;
                break;
            }
            case 'm': {
                minimal = true;
            }
        }
    }

    if (initialize_board(&board, side_size)) {
        return 1;
    }

    place_random(board, side_size);

    while (1) {
        place_random(board, side_size);
        draw(board, side_size);

        if (is_game_won(board, side_size) && !endless) {
            printf("You've won, do you want to keep playing?[Y/n] ");
            switch (getchar()) {
                case 'n':
                case 'N': {
                    free_board(board, side_size);
                    return 0;
                    break;
                }
                case 'y':
                case 'Y':
                case '\n': {
                    endless = true;
                    break;
                }
            }
            draw(board, side_size);
        }

        if (is_game_over(board, side_size)) {
            printf("No empty space left. GAME OVER!\n");
            break;
        }

        while (!process_input(getch(), board, side_size)) {
        }
    }
    printf("\n");
    return 0;
}
