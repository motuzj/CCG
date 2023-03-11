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

int processCommand() {
    char input[15];
    char *inputCommand;
    char *inputX;
    char *inputY;
    long x, y;

    printf("\n\ncommand: ");

    fgets(input, sizeof(input), stdin);
    if (strcmp(input, "\n") == 0) {
        printf("Please type command or type help to see help!");
        return 1;
    }

    input[strcspn(input, "\n")] = 0;  // remove \n newline character
    printf("\n'%s'\n", input);

    inputCommand = strtok(input, " ");  // get first input command
    if (inputCommand == NULL) {
        printf("Error. Please type command or type help to see help!");
        return 1;
    }

    int inputCommandLen = strlen(inputCommand);  // first input lenght

    if (!strcmp(inputCommand, "\n")) {
        printf("Please type command or type help to see help!");
        return 0;
    }
    if ((inputCommandLen == 1 && strcmp(inputCommand, "h") == 0) || (inputCommandLen == 4 && strcmp(inputCommand, "help") == 0)) {
        printf("TODO"); // TODO: Help message
        return 0;
    } else {
    }

    inputX = strtok(NULL, " ");
    inputY = strtok(NULL, " ");
    if (inputX == NULL || inputY == NULL) {
        printf("Illegal command usage. Use help to show help.");
        return 1;
    }
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


    if (x < 0 || y < 0 || x > mapWidth || y > mapWidth) {
        printf("Error: The provided coordinates are out of range.");
        return 1;
    }
    printf("\n");

    // guess
    if ((inputCommandLen == 1 && strcmp(inputCommand, "g") == 0) || (inputCommandLen == 5 && strcmp(inputCommand, "guess") == 0)) {
        if (firstGuess) {
            generateMap(mapWidth, mapHeight, y, x);
            firstGuess = 0;
        }

        if (map[x][y] == 2 || map[x][y] == 4 || map[x][y] == 6 || map[x][y] == 7) {
            printf("Game Over, LOSER!");
            playing = 0;
        }

        return 0;
    }
    return 0;
}
