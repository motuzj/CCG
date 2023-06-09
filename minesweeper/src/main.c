#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "game.h"

int w = 0;
int h = 0;
int cursorX = 0;
int cursorY = 0;
int first_cursorX = 0;
int first_cursorY = 0;
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
    while ((opt = getopt(argc, argv, "s:mw:h:")) != -1) {
        switch (opt) {
            case 's': {
                custom_seed = true;
                arg_set_seed(optarg);
                break;
            }
            case 'm': {
                minimal = true;
                break;
            }
            case 'w': {
                if (w == 0) {
                    w = atoi(optarg);
                }
                break;
            }
            case 'h': {
                if (h == 0) {
                    h = atoi(optarg);
                }
                break;
            }
        }
    }

    run_game();
    return 0;
}
