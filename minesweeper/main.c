#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "game.h"
#include "input.h"

int w = 0;       // board width / max x coords
int h = 0;       // board height / max y coords
int cursorX = 0; // position of cursor x coords
int cursorY = 0; // position of cursor y coords
int mines;
int firstGuess = 1;     // 1 - first game ; 0 - not first game
char message[120] = ""; // message that will be printed during draw()

Cell **board;
State gameState = PLAYING;

int main(int argc, char *argv[]) {

    //
    int opt;
    while ((opt = getopt(argc, argv, "w:h:help")) != -1) {
        switch (opt) {
            case 'w': {
                w = atoi(optarg);
                break;
            }
            case 'h': {
                h = atoi(optarg);
                break;
            }
        }
    }

    run_game();
    return 0;
}
