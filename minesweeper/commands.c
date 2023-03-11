#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "commands.h"

extern int mapWidth;
extern int mapHeight;
extern int playing;
extern int firstGuess;

extern int** map;

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
        printf("Please type command or type help to see help!");
        return 1;
    }

    // remove \n newline character from `input`
    input[strcspn(input, "\n")] = 0;
    //printf("\n'%s'\n", input);

    // get first input command
    inputCommand = strtok(input, " ");
    if (inputCommand == NULL) {
        printf("Error. Please type command or type help to see help!");
        return 1;
    }

    // first command input length
    int inputCommandLen = strlen(inputCommand);

    // TODO: remove from this, it seems like this is there for nothing
    if (!strcmp(inputCommand, "\n")) {
        //printf("Please type command or type help to see help!");
        printf("THIS MESSAGE WORKS, PLEASE REMOVE THIS FROM TODO!!!");
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
        printf("Illegal command usage. Use help to show help.");
        return 1;
    }

    // convert inputs variables to x and y and check if they are valid ints
    char *endptr;
    x = strtol(inputX, &endptr, 10);
    if (*endptr != '\0') {
        printf("Invalid input: %s\n", inputX);
        return 1;
    }
    y = strtol(inputY, &endptr, 10);
    if (*endptr != '\0') {
        printf("Invalid input: %s\n", inputY);
        return 1;
    }

    // check if x, y are out of map -> returns an error message
    if (x < 0 || y < 0 || x > mapWidth || y > mapHeight) {
        printf("Error: The provided coordinates are out of range.");
        return 1;
    }
    printf("\n");

    // check if command is `guess`
    if ((inputCommandLen == 1 && strcmp(inputCommand, "g") == 0) || (inputCommandLen == 5 && strcmp(inputCommand, "guess") == 0)) {
        command_guess(x, y);
        return 0;
    }
    return 0;
}

int command_guess(long x, long y) {
    // check if it's first guess and generate map
    if (firstGuess) {
        generate_map(mapWidth, mapHeight, y, x);
        firstGuess = 0;
    }

    // if it's mine -> game over
    if (map[y][x] == 2 || map[y][x] == 4 || map[y][x] == 6 || map[y][x] == 7) {
        printf("Game Over, LOSER!");
        playing = 0;
    } else { // else set to 0 and reveal neighborhood empty cells
        reveal_empty_cells(x, y, 0); // function in game.c
    }

    return 0;
}

int command_help() {
    printf("\nUSAGE: <command> <x> <y>\n\nCOMMANDS:\n  guess <x> <y>\tReveals the cell at the specified coordinates.\n  mark <x> <y>\tMarks a cell at the specified coordinates as a potential mine.\n  unmark <x><y>\tUnmarks a cell at the specified coordinates as a mine.\n  restart or r\tStops a game and starts a new one.\n  quit or exit\tQuits the game.\n\nNOTES:\n  To use a command, simply type the command name followed by any required arguments. For example, to guess the cell at x (column) 3, y (row) 4, type \"guess 3 4\" and press enter.\n  Note that all commands are case sensitive.\n  You can also use one word abbreviations as: g (guess), m (mark)...\n");
    return 0;
}
