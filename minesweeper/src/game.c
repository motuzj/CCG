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

#define CLEAR_SCREEN "\033[1;1H\033[2J"

static double minesPercentage = 0.13; // percentage of mines


// set seed from from arguments
int arg_set_seed(char arg[]) {
    sscanf(arg, "%dx%dn%dc%dx%d#", &w, &h, &mines, &cursor_x, &cursor_y);
    const char *hexSeed = strchr(arg, '#');
    if (hexSeed == NULL) {
        fprintf(stderr, "Error: Invalid string format. Hexadecimal number not found.\n");
        return 1;
    }
    hexSeed++; // Move past the '#'

    seed = strtol(hexSeed, NULL, 16);
    return 0;
}

void generate_board(int guess_x, int guess_y) {
    int temp_mines = mines;
    if (!seed) seed = (unsigned int)time(NULL);
    srand(seed);

    // check if minesPercentage is in valid format
    if (minesPercentage < 0.0 || minesPercentage > 1.0) {
        fprintf(stderr, "Warning: Percentage of mines is too big or small, setting it to 13%%.");
        minesPercentage = 0.13;
    }

    // placing mines
    while (temp_mines) {
        int potencial_x = rand() % w;
        int potencial_y = rand() % h;

        // checks if it's next to first guess cords
        bool hasGuessNeighbor = false;
        for (int i = potencial_x - 1; i <= potencial_x + 1; i++) {
            for (int j = potencial_y - 1; j <= potencial_y + 1; j++) {
                if (j == guess_x && i == guess_y) {
                    hasGuessNeighbor = true;
                }
            }
        }

        // place a mine if it is not already there, or if it is not near the guess
        if (board[potencial_y][potencial_x] != CELL_MINE_HIDDEN && !(potencial_x == guess_x && potencial_y == guess_y) && !hasGuessNeighbor) {
            board[potencial_y][potencial_x] = CELL_MINE_HIDDEN;
            temp_mines--;
        }
    }
}

void reveal_empty_cells(int x, int y) {
    // detect if cell was revealed or is out of board
    if (x < 0 || x >= w || y < 0 || y >= h || board[y][x] != CELL_BLANK_HIDDEN) return;
    board[y][x] = 0;

    // exits if there are mines nearby
    if (count_nearby_mines(y, x) > 0) return;

    // test for all empty cells
    for (int i = x - 1; i <= x + 1; i++) {
        for (int j = y - 1; j <= y + 1; j++) {
            if (i == x && j == y) continue; // skip the current cell
            reveal_empty_cells(i, j); // reveal the neighboring cell
        }
    }
}

static void reveal_all_mines() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            switch (board[i][j]) {
                case CELL_MINE_HIDDEN:
                case CELL_FLAGGED_MINE:
                    board[i][j] = CELL_MINE;
                    break;
                case CELL_FLAGGED:
                    board[i][j] = CELL_BLANK_HIDDEN;
                    break;
                default: break;
            }
        }
    }
}

int count_nearby_mines(int x, int y) {
    int minesCounter = 0;
    for (int k = x - 1; k <= x + 1; k++) {
        for (int l = y - 1; l <= y + 1; l++) {
            // Skip out-of-bounds cells
            if (k < 0 || k >= h || l < 0 || l >= w) continue;
            // Check if the cell has a mine
            if (board[k][l] == CELL_MINE_HIDDEN || board[k][l] == CELL_FLAGGED_MINE || board[k][l] == CELL_MINE) minesCounter++;
        }
    }
    return minesCounter;
}

int count_cells_with_state(Cell state) {
    int counter = 0;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (board[i][j] == state) counter++;
        }
    }
    return counter;
}

static int set_valid_size(int *var, const char *var_name) {
    char input[10] = "";
    char *endptr;
    while (*var < 5 || *var > 99) {
        printf("%s: ", var_name);
        // write stdin to input and check if it is null
        if (fgets(input, sizeof(input), stdin) == NULL) {
            fprintf(stderr, "Error: There was some problem reading stdin, try it again!\n");
            return 1;
        }
        // remove \n newline character from `input`
        input[strcspn(input, "\n")] = 0;

        // convert string to int
        *var = (int)strtol(input, &endptr, 10);
        if (*endptr != '\0' || *var < 5 || *var > 99) {
            printf("Make sure the size is valid number from 5 to 99!\n");
            continue;
        }
        break;
    }
    return 0;
}

static int set_board_size() {
    if (set_valid_size(&w, "Width")) return 1;
    if (set_valid_size(&h, "Height")) return 1;

    if (!mines) {
        // calculate number of mines to place
        mines = (int)(w * h * minesPercentage);

        if (mines > (w * h)) mines = w * h - 9;
    }
    return 0;
}

static int initialize_board() {
    if (set_board_size()) return 1;

    // initiation of board
    board = (Cell **)calloc(h, sizeof(Cell *));
    if (board == NULL) {
        fprintf(stderr, "\nError: Not enough memory to allocate.\nExiting...\n");
        return 1;
    }
    for (int i = 0; i < h; i++) {
        board[i] = (Cell *)calloc(w, sizeof(Cell));
    }
    for (int i = 0; i < h; i++) {
        if (board[i] == NULL) {
            fprintf(stderr, "\nError: Not enough memory to allocate.\nExiting...\n");
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

static void free_board() {
    // freeing board
    for (int i = 0; i < h; i++) free(board[i]);
    free(board);
    board = NULL;
}

int run_game() {
    if (initialize_board()) return 1;

    if (custom_seed) command_guess(cursor_x, cursor_y);

    // main loop
    while (gameState == PLAYING) {
        printf(CLEAR_SCREEN);

        draw();
        process_input();

        // skip if player hasn't guessed yet
        if (!firstGuess) {
            // player wins if all mines are checked and all empty cells revealed
            // or if there are no flagged empty cells and no unrevealed cells
            int flaggedMines = count_cells_with_state(CELL_FLAGGED_MINE);
            int hiddenCells = count_cells_with_state(CELL_BLANK_HIDDEN);
            int flaggedCells = count_cells_with_state(CELL_FLAGGED);
            mines = (int)w * h * minesPercentage;
            if ((flaggedMines == mines && !hiddenCells && !flaggedCells) || (!flaggedCells && !hiddenCells)) {
                gameState = NOT_PLAYING;
                strcpy(message, "You've won!!");
            }
        }

        if (gameState != PLAYING) { // game ended
            reveal_all_mines();
            printf(CLEAR_SCREEN);
            draw();

            char answer;
            if (gameState == RESTART) {
                answer = 'y';
            } else if (gameState == QUIT) {
                answer = 'n';
            } else {
                printf("\nDo you want to play again? (y/N) ");
                scanf("%c", &answer);
                if (answer != '\n') {
                    getchar(); // this is needed for catching 'ENTER'
                }
            }

            if (answer == 'y' || answer == 'Y') {
                free_board();

                gameState = PLAYING;
                firstGuess = 1;
                w = 0;       // reset width
                h = 0;       // reset height
                mines = 0;   // reset mines counter
                seed = 0;    // reset seed
                cursor_x = 0; // reset cursor x coord
                cursor_y = 0; // reset cursor y coord

                if (initialize_board()) return 1;
            } else {
                printf("Bye!");
            }
        }
    }
    free_board();
    printf("\n");
    return 0;
}
