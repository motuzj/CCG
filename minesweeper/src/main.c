#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "game.h"

int w = 0;
int h = 0;
int cursor_x = 0;
int cursor_y = 0;
int first_guess_x = 0;
int first_guess_y = 0;
int mines = 0;
unsigned int seed = 0;
bool firstGuess = true;
char message[120] = "";

// options
bool custom_seed = false;
bool minimal = false;

Cell **board;
State gameState = PLAYING;

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "s:mr:c:h")) != -1) {
        switch (opt) {
            case 's':
                custom_seed = true;
                if (arg_set_seed(optarg)) return 1;
                break;
            case 'm':
                minimal = true;
                break;
            case 'c': // width
                if (!custom_seed) w = atoi(optarg);
                break;
            case 'r': // height
                if (!custom_seed) h = atoi(optarg);
                break;
            case 'h':
                printf("Usage: %s [OPTION]...\n\n -r \033[3m<num>\033[0m\tNumber of rows\n -c \033[3m<num>\033[0m\tNumber of columns\n -s \033[3m<str>\033[0m\tSet a seed in alphanumerical format with '#', eg. 10x10n13c0x0#65A1549F\n -m\t\tEnables minimal mode (everything except game board is hidden)\n -h\t\tPrints this help message and exit\n", argv[0]);
                exit(EXIT_SUCCESS);
        }
    }

    return run_game();
}
