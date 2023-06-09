#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "draw.h"
#include "game.h"
#include "input.h"
#include "main.h"

double minesPercentage = 0.13; // percentage of mines

#define CLEAR_SCREEN "\e[1;1H\e[2J"

// set seed from from arguments
int arg_set_seed(char arg[]) {
    // 10x10n13c#64821415
    sscanf(arg, "%dx%dn%dc%dx%d#", &w, &h, &mines, &cursorX, &cursorY);
    const char *hexSeed = strchr(arg, '#');
    if (hexSeed == NULL) {
        printf("Invalid string format. Hexadecimal number not found.\n");
        return 1;
    }
    hexSeed++; // Move past the "#"

    seed = strtol(hexSeed, NULL, 16);
    return 0;
}

int generate_board(int guessX, int guessY, int w, int h) {
    int temp_mines = mines;
    if (!seed) {
        seed = (unsigned int)time(NULL);
    }
    srand(seed);

    // check if minesPercentage is in valid format
    if (minesPercentage < 0.0 || minesPercentage > 1.0) {
        printf("Warning: Percentage of mines is too big or small, setting it to 13%%.");
        minesPercentage = 0.13;
    }

    // placing mines
    while (temp_mines) {
        int potencial_x = rand() % w;
        int potencial_y = rand() % h;

        // checks if neighbor is guess
        bool hasGuessNeighbor = false;
        for (int i = potencial_x - 1; i <= potencial_x + 1; i++) {
            for (int j = potencial_y - 1; j <= potencial_y + 1; j++) {
                if (j == guessX && i == guessY) {
                    hasGuessNeighbor = true;
                }
            }
        }

        // place a mine if it is not already there, or if it is not near the guess
        if (board[potencial_y][potencial_x] != CELL_MINE_HIDDEN && !(potencial_x == guessX && potencial_y == guessY) && !hasGuessNeighbor) {
            board[potencial_y][potencial_x] = CELL_MINE_HIDDEN;
            temp_mines--;
        }
    }
    return 0;
}

int reveal_empty_cells(int x, int y) {
    // detect if cell was revealed or is out of board
    if (x < 0 || x >= w || y < 0 || y >= h || board[y][x] != CELL_BLANK_HIDDEN) {
        return 0;
    }
    board[y][x] = 0;

    // exits if there are mines nearby
    if (count_mines(board, y, x, w, h) > 0) {
        return 0;
    }

    // test for all empty cells
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i == x && j == y)
                continue;             // skip the current cell
            reveal_empty_cells(i, j); // reveal the neighboring cell
        }
    }

    return 0;
}

int reveal_all_mines(Cell **board, int w, int h) {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            switch (board[i][j]) {
                case CELL_MINE_HIDDEN:
                case CELL_FLAGGED_MINE: {
                    board[i][j] = CELL_MINE;
                    break;
                }
                case CELL_FLAGGED: {
                    board[i][j] = CELL_BLANK_HIDDEN;
                    break;
                }
                default: {
                    // nothing
                    break;
                }
            }
        }
    }
    return 0;
}

int count_mines(Cell **board, int x, int y, int w, int h) {
    int minesCounter = 0;

    for (int k = x - 1; k <= x + 1; k++) {
        for (int l = y - 1; l <= y + 1; l++) {
            // Skip out-of-bounds cells
            if (k < 0 || k >= h || l < 0 || l >= w) {
                continue;
            }
            // Check if the cell has a mine
            if (board[k][l] == CELL_MINE_HIDDEN || board[k][l] == CELL_FLAGGED_MINE || board[k][l] == CELL_MINE) {
                minesCounter++;
            }
        }
    }
    return minesCounter;
}

int count_cells_with_state(Cell **board, Cell state, int w, int h) {
    int counter = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (board[i][j] == state) {
                counter++;
            }
        }
    }
    return counter;
}

int set_board_size() {
    char input[10] = "";
    char *endptr;

    while (w < 5 || w > 99) {
        printf("Width: ");
        // write stdin to input and check if it is null
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error: There was some problem reading stdin, try it again!\n");
            continue;
        }
        // remove \n newline character from `input`
        input[strcspn(input, "\n")] = 0;

        // convert string to int
        w = strtol(input, &endptr, 10);
        if (*endptr != '\0' || w < 5 || w > 99) {
            printf("Make sure the size is valid number from 5 to 99!\n");
            continue;
        }
        break;
    }
    while (h < 5 || h > 99) {
        printf("Height: ");
        // write stdin to input and check if it is null
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("Error: There was some problem reading stdin, try it again!\n");
            continue;
        }
        // remove \n newline character from `input`
        input[strcspn(input, "\n")] = 0;

        // convert string to int
        h = strtol(input, &endptr, 10);
        if (*endptr != '\0' || h < 5 || h > 99) {
            printf("Make sure the size is valid number from 5 to 99!\n");
            continue;
        }
        break;
    }
    if (!mines) {
        // calculate number of mines to place
        mines = (int)w * h * minesPercentage;

        if (mines > (w * h)) {
            mines = w * h - 9;
        }
    }
    return 0;
}

int initialize_board() {
    set_board_size();

    // initiation of board
    board = (Cell **)calloc(h, sizeof(Cell *));
    if (board == NULL) {
        printf("\nError: Not enough memory to allocate.\nExiting...\n");
        return 1;
    }
    for (int i = 0; i < h; i++) {
        board[i] = (Cell *)calloc(w, sizeof(Cell));
    }
    for (int i = 0; i < h; i++) {
        if (board[i] == NULL) {
            printf("\nError: Not enough memory to allocate.\nExiting...\n");
            return 1;
        }
    }

    // set all numbers in board to CELL_BLANK_HIDDEN
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            board[i][j] = CELL_BLANK_HIDDEN;
        }
    }
    printf(CLEAR_SCREEN);
    return 0;
}

int free_board(Cell **board, int h) {
    // freeing board
    for (int i = 0; i < h; i++) {
        free(board[i]);
    }
    free(board);
    printf("\n");
    return 0;
}

int run_game() {
    initialize_board();

    if (custom_seed) {
        command_guess(cursorX, cursorY);
    }

    // main loop
    while (gameState == PLAYING) {
        printf(CLEAR_SCREEN);

        draw(w, h, board);
        process_input();

        // skip if player hasn't guessed yet
        if (!firstGuess) {
            // player wins if all mines are checked and all empty cells revealed
            // or if there no flagged empty cells and no unrevealed cells
            int flaggedMines = count_cells_with_state(board, CELL_FLAGGED_MINE, w, h);
            int hiddenCells = count_cells_with_state(board, CELL_BLANK_HIDDEN, w, h);
            int flaggedCells = count_cells_with_state(board, CELL_FLAGGED, w, h);
            mines = (int)w * h * minesPercentage;
            if ((flaggedMines == mines && !hiddenCells && !flaggedCells) || (!flaggedCells && !hiddenCells)) {
                gameState = NOT_PLAYING;
                strcpy(message, "You've won!!");
            }
        }

        if (gameState != PLAYING) { // game ended
            reveal_all_mines(board, w, h);
            printf(CLEAR_SCREEN);
            draw(w, h, board);

            char answer;
            if (gameState == RESTART) {
                answer = 'y';
            } else if (gameState == QUIT) {
                answer = 'n';
            } else {
                printf("\nDo you want to play again? (y/N) ");
                scanf("%c", &answer);
                if (answer != '\n') {
                    getchar(); // this is needed for catching "enter"
                }
            }

            if (answer == 'y' || answer == 'Y') {
                w = 0; // reset width
                h = 0; // reset height

                // reset cursor
                cursorX = 0;
                cursorY = 0;

                seed = 0; // reset seed

                gameState = PLAYING;
                firstGuess = 1;
                free_board(board, h);
                initialize_board();
            } else {
                printf("Bye!");
            }
        }
    }
    free_board(board, h);
    return 0;
}
