#include <getopt.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include "game.h"
#include "help.h"

int board_rows; // y
int board_cols; // x

// options
bool disable_borders = false;
int option_speed = 5;

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "bs:h")) != -1) {
        switch (opt) {
            case 'b':
                disable_borders = true;
                break;
            case 's':
                option_speed = atoi(optarg);
                if (option_speed < 1 && option_speed > 10) {
                    fprintf(stderr, "Speed option value is not a number or it is smaller than 1 or bigger than 10! Setting speed to 5.");
                    option_speed = 5;
                }
                break;
            case 'h':
                display_help();
                exit(0);
        }
    }

    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    board_cols = ws.ws_col - 2; // terminal width
    board_rows = ws.ws_row - 3; // terminal height

    run_game();
    return 0;
}
