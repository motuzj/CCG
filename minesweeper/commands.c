#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "commands.h"

#define CLEAR_SCREEN "\e[1;1H\e[2J"

int process_command() {
    char input[15];
    char *inputCommand;
    char *inputX;
    char *inputY;
    long x, y;

    printf("\n\ncommand: ");

    // write stdin to input
    fgets(input, sizeof(input), stdin);

    //check if it's empty
    if (strcmp(input, "\n") == 0) {
        strcpy(message, "Error: Please type command or type help to see help!");
        return 1;
    }

    // remove \n newline character from `input`
    input[strcspn(input, "\n")] = 0;

    // get first input command
    inputCommand = strtok(input, " ");
    if (inputCommand == NULL) {
        strcpy(message, "Error: Please type command or type help to see help!");
        return 1;
    }

    // first command input length
    int inputCommandLen = strlen(inputCommand);

    // prints status
    if ((inputCommandLen == 1 && strcmp(inputCommand, "s") == 0) || (inputCommandLen == 6 && strcmp(inputCommand, "status") == 0)) {
        command_status();
        return 0;
    }

    // check if command is `restart`
    if ((inputCommandLen == 1 && strcmp(inputCommand, "r") == 0) || (inputCommandLen == 7 && strcmp(inputCommand, "restart") == 0)) {
        command_restart();
        return 0;
    }

    // check if command is `quit`
    if ((inputCommandLen == 1 && strcmp(inputCommand, "q") == 0) || (inputCommandLen == 4 && strcmp(inputCommand, "quit") == 0)) {
        command_quit();
        return 0;
    }

    // prints help message
    if ((inputCommandLen == 1 && strcmp(inputCommand, "h") == 0) || (inputCommandLen == 4 && strcmp(inputCommand, "help") == 0)) {
        command_help();
        return 0;
    }

    // save remaining input to these variables and exit if they are null
    inputX = strtok(NULL, " ");
    inputY = strtok(NULL, " ");
    if (inputX == NULL || inputY == NULL) {
        strcpy(message, "Error: Illegal command usage. Use help to show help.");
        return 1;
    }

    // convert inputs variables to x and y and check if they are valid ints
    char *endptr;
    x = strtol(inputX, &endptr, 10);
    if (*endptr != '\0') {
        sprintf(message, "Error: Invalid input: %s", inputX);
        return 1;
    }
    y = strtol(inputY, &endptr, 10);
    if (*endptr != '\0') {
        sprintf(message, "Error: Invalid input: %s", inputY);
        return 1;
    }

    // check if x, y are out of board -> returns an error message
    if (x < 0 || y < 0 || x > w - 1 || y > h - 1) {
        strcpy(message, "Error: The provided coordinates are out of range.");
        return 1;
    }
    printf("\n");

    // check if command is `guess`
    if ((inputCommandLen == 1 && strcmp(inputCommand, "g") == 0) || (inputCommandLen == 5 && strcmp(inputCommand, "guess") == 0)) {
        command_guess(x, y);
        return 0;
    }

    // check if command is `mark`
    if ((inputCommandLen == 1 && strcmp(inputCommand, "m") == 0) || (inputCommandLen == 4 && strcmp(inputCommand, "mark") == 0)) {
        command_mark(x, y);
        return 0;
    }
    return 0;
}

int command_guess(long x, long y) {
    // check if it's first guess and generate board
    if (firstGuess) {
        generate_board(y, x, w, h);
        firstGuess = 0;
    }

    // if it's mine -> game over
    if (board[y][x] == CELL_MINE || board[y][x] == CELL_MINE_HIDDEN || board[y][x] == CELL_MARKED_MINE) {
        strcpy(message, "Game Over, LOSER!");
        gameState = NOT_PLAYING;
    } else if (board[y][x] == CELL_BLANK) {
        strcpy(message, "Error: The cell has already been revealed!");
    } else { // else set to 0 and reveal neighborhood empty cells
        reveal_empty_cells(x, y); // function in game.c
    }

    return 0;
}

int command_mark(long x, long y) {
    if (firstGuess) {
        strcpy(message, "Error: The game hasn't started yet! Please start the game with 'guess'! For further help, type 'help'.");
        return 1;
    }
    if (board[y][x] == CELL_MINE || board[y][x] == CELL_MINE_HIDDEN) { // if it's a mine
        board[y][x] = CELL_MARKED_MINE;
    } else if (board[y][x] == CELL_BLANK_HIDDEN) { // if it's not a mine
        board[y][x] = CELL_MARKED;
    } else if (board[y][x] == CELL_MARKED_MINE) { // if it was marked and it's a mine
        board[y][x] = CELL_MINE_HIDDEN;
    } else if (board[y][x] == CELL_MARKED) { // if it was marked and it's not a mine
        board[y][x] = CELL_BLANK_HIDDEN;
    } else {
        strcpy(message, "Error: Please select non empty or valid cell!");
        return 1;
    }
    return 0;
}

int command_status() {
    sprintf(message, "Mines: %d/%d", count_cells_with_state(board, CELL_MARKED_MINE, w, h) + count_cells_with_state(board, CELL_MARKED, w, h), mines);
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
    printf("USAGE: <command> <x> <y>\n\nCOMMANDS:\n  guess <x> <y>\tReveals the cell at the specified coordinates.\n  mark <x> <y>\tMarks a cell at the specified coordinates as a potential mine.\n  status or s\tView status of the game.\n  restart or r\tStops a game and starts a new one.\n  quit or exit\tQuits the game.\n  help or h\tDisplays this message.\n\nNOTES:\n  To use a command, simply type the command name followed by any required arguments. For example, to guess the cell at x (column) 3, y (row) 4, type \"guess 3 4\" and press enter.\n  Note that all commands are case sensitive.\n  You can also use one word abbreviations as: g (guess), m (mark)...\n\nPress [ENTER] to continue");
    getchar();
    return 0;
}
