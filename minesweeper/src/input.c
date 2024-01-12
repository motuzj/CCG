#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

#include "game.h"
#include "input.h"
#include "main.h"

#define CLEAR_SCREEN "\033[1;1H\033[2J"

// get one char; from this: https://stackoverflow.com/a/7469410
static int getch() {
    static struct termios old, current;
    int ch;
    tcgetattr(0, &old);         /* grab old terminal i/o settings */
    current = old;              /* make new settings same as old settings */
    current.c_lflag &= ~ICANON; /* disable buffered i/o */
    current.c_lflag &= ~ECHO;   /* set no echo mode */
    tcsetattr(0, TCSANOW, &current);
    ch = getchar();
    tcsetattr(0, TCSANOW, &old);
    return ch;
}

void command_guess(int x, int y) {
    // check if it's first guess and generate board
    if (firstGuess) {
        generate_board(y, x);
        first_guess_x = x;
        first_guess_y = y;
        firstGuess = 0;
    }

    // if it's mine -> game over
    if (board[y][x] == CELL_MINE || board[y][x] == CELL_MINE_HIDDEN || board[y][x] == CELL_FLAGGED_MINE) {
        strcpy(message, "Game Over, LOSER!");
        gameState = NOT_PLAYING;
    } else if (board[y][x] == CELL_BLANK) {
        strcpy(message, "Error: The cell has already been revealed!");
    } else {                      // else reveal cell and it's neighborhood empty cells
        reveal_empty_cells(x, y);
    }
}

static void command_flag(int x, int y) {
    if (firstGuess) {
        strcpy(message, "Error: The game hasn't started yet! Please start the game with first guess! For further help, press '?'.");
    }
    switch (board[y][x]) {
        case CELL_MINE:
        case CELL_MINE_HIDDEN:
            board[y][x] = CELL_FLAGGED_MINE;
            break;
        case CELL_BLANK_HIDDEN:
            board[y][x] = CELL_FLAGGED;
            break;
        case CELL_FLAGGED_MINE:
            board[y][x] = CELL_MINE_HIDDEN;
            break;
        case CELL_FLAGGED:
            board[y][x] = CELL_BLANK_HIDDEN;
            break;
        default:
            strcpy(message, "Error: Please select non empty or valid cell!");
            break;
    }
}

static void command_status() {
    sprintf(message, "Mines: %d/%d\nSeed: %dx%dn%dc%dx%d#%X", count_cells_with_state(CELL_FLAGGED_MINE) + count_cells_with_state(CELL_FLAGGED), mines, w, h, mines, first_guess_x, first_guess_y, seed);
}

static void command_help() {
    printf(CLEAR_SCREEN);
    printf("CONTROLS:\n  Arrow keys\t\tMove the cursor around\n  Space, Enter, g\tReveal a cell\n  f, m\t\t\tFlag a cell as mine\n  s\t\t\tView status of the game and game seed\n  r\t\t\tStops a game and starts a new one\n  q\t\t\tQuits the game\n  h, ?\t\t\tDisplays this message\n\nPress [ENTER] to continue");
    getch();
}

void process_input() {
    int input = getch();

    switch (input) {
        case 'A': // up
            cursor_y--;
            break;
        case 'B': // down
            cursor_y++;
            break;
        case 'C': // right
            cursor_x++;
            break;
        case 'D': // left
            cursor_x--;
            break;
        case '\n':
        case ' ':
        case 'g':
            command_guess(cursor_x, cursor_y);
            break;
        case 'f':
        case 'm':
            command_flag(cursor_x, cursor_y);
            break;
        case 's':
            command_status();
            break;
        case 'r':
            gameState = RESTART;
            break;
        case 'q':
            gameState = QUIT;
            break;
        case '?':
        case 'h':
            command_help();
            break;
    }

    // set cursor in bounds
    if (cursor_x < 0) {
        cursor_x = w - 1;
    } else if (cursor_x > w - 1) {
        cursor_x = 0;
    }
    if (cursor_y < 0) {
        cursor_y = h - 1;
    } else if (cursor_y > h - 1) {
        cursor_y = 0;
    }
}
