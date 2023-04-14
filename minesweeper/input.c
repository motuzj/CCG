#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>

#include "game.h"
#include "input.h"

#define CLEAR_SCREEN "\e[1;1H\e[2J"

int process_input() {
    char input = getch();
    // sprintf(message, "input is: %c", input);

    switch (input) {
        case 'A': { // up
            cursorY--;
            break;
        }
        case 'B': { // down
            cursorY++;
            break;
        }
        case 'C': { // right
            cursorX++;
            break;
        }
        case 'D': { // left
            cursorX--;
            break;
        }
        case '\n':
        case ' ':
        case 'g': {
            command_guess(cursorX, cursorY);
            break;
        }
        case 'f':
        case 'm': {
            command_flag(cursorX, cursorY);
            break;
        }
        case 's': {
            command_status();
            break;
        }
        case 'r': {
            command_restart();
            break;
        }
        case 'q': {
            command_quit();
            break;
        }
        case '?':
        case 'h': {
            command_help();
            break;
        }
    }

    // set cursor in bounds
    if (cursorX < 0) {
        cursorX = w - 1;
    } else if (cursorX > w - 1) {
        cursorX = 0;
    }
    if (cursorY < 0) {
        cursorY = h - 1;
    } else if (cursorY > h - 1) {
        cursorY = 0;
    }

    return 0;
}

// get one char; from this: https://stackoverflow.com/a/7469410
int getch() {
    static struct termios old, current;
    char ch;
    tcgetattr(0, &old);         /* grab old terminal i/o settings */
    current = old;              /* make new settings same as old settings */
    current.c_lflag &= ~ICANON; /* disable buffered i/o */
    current.c_lflag &= ~ECHO;   /* set no echo mode */
    tcsetattr(0, TCSANOW, &current);
    ch = getchar();
    tcsetattr(0, TCSANOW, &old);
    return ch;
}

int command_guess(long x, long y) {
    // check if it's first guess and generate board
    if (firstGuess) {
        generate_board(y, x, w, h);
        firstGuess = 0;
    }

    // if it's mine -> game over
    if (board[y][x] == CELL_MINE || board[y][x] == CELL_MINE_HIDDEN || board[y][x] == CELL_FLAGGED_MINE) {
        strcpy(message, "Game Over, LOSER!");
        gameState = NOT_PLAYING;
    } else if (board[y][x] == CELL_BLANK) {
        strcpy(message, "Error: The cell has already been revealed!");
    } else {                      // else set to 0 and reveal neighborhood empty cells
        reveal_empty_cells(x, y); // function in game.c
    }

    return 0;
}

int command_flag(long x, long y) {
    if (firstGuess) {
        strcpy(message, "Error: The game hasn't started yet! Please start the game with first guess! For further help, press '?'.");
        return 1;
    }
    if (board[y][x] == CELL_MINE || board[y][x] == CELL_MINE_HIDDEN) { // if it's a mine
        board[y][x] = CELL_FLAGGED_MINE;
    } else if (board[y][x] == CELL_BLANK_HIDDEN) { // if it's not a mine
        board[y][x] = CELL_FLAGGED;
    } else if (board[y][x] == CELL_FLAGGED_MINE) { // if it was flagged and it's a mine
        board[y][x] = CELL_MINE_HIDDEN;
    } else if (board[y][x] == CELL_FLAGGED) { // if it was flagged and it's not a mine
        board[y][x] = CELL_BLANK_HIDDEN;
    } else {
        strcpy(message, "Error: Please select non empty or valid cell!");
        return 1;
    }
    return 0;
}

int command_status() {
    sprintf(message, "Mines: %d/%d", count_cells_with_state(board, CELL_FLAGGED_MINE, w, h) + count_cells_with_state(board, CELL_FLAGGED, w, h), mines);
    return 0;
}

int command_restart() {
    gameState = RESTART;
    return 0;
}

int command_quit() {
    gameState = QUIT;
    return 0;
}

int command_help() {
    printf(CLEAR_SCREEN);
    printf("CONTROLS:\n  Arrow keys\t\tMove the cursor around\n  Space, Enter, g\tReveal a cell\n  f\t\t\tFlag a cell as mine\n  s\t\t\tView status of the game\n  r\t\t\tStops a game and starts a new one\n  q\t\t\tQuits the game\n  h, ?\t\t\tDisplays this message\n\nPress [ENTER] to continue");
    getch();
    return 0;
}