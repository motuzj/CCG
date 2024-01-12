#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "draw.h"
#include "main.h"

// returns text for priniting it on side
static char *print_message(int i) {
    switch (i) {
        case 0: return "M I N E S W E E P E R";
        case 1: return "---------------------";
        case 2: return "[SPACE] reveal a cell";
        case 3: return "f       flag a mine";
        case 4: return "press ? for help";
        default: return "";
    }
}

int draw() {
    // drawing top table
    printf("┌");
    for (int i = 0; i < (w * 2 + 1); i++) printf("─");
    printf("┐\t\n");

    // printing minesweeper board
    for (int i = 0; i < h; i++) {
        printf("│ ");
        for (int j = 0; j < w; j++) {
            if (i == cursor_y && j == cursor_x && (board[i][j] == CELL_BLANK_HIDDEN || board[i][j] == CELL_MINE_HIDDEN)) {
                printf("\033[42m\033[30m");
            } else if (board[i][j] == CELL_BLANK_HIDDEN || board[i][j] == CELL_MINE_HIDDEN) {
                printf("\033[47m\033[30m");
            } else if (i == cursor_y && j == cursor_x) {
                printf("\033[42m");
            }
            switch (board[i][j]) {
                case CELL_BLANK: {
                    int counter = count_nearby_mines(i, j);

                    if (counter > 0) {
                        printf("%d", counter);
                    } else {
                        printf(" ");
                    }
                    break;
                }
                case CELL_FLAGGED:
                case CELL_FLAGGED_MINE:
                    printf("\033[35mX");
                    break;
                case CELL_MINE:
                    printf("\033[91m#");
                    break;
                case CELL_BLANK_HIDDEN:
                case CELL_MINE_HIDDEN:
                default:
                    printf("?");
                    break;
            }
            printf("\033[0m ");
        }
        printf("│  %s\n", (minimal ? "" : print_message(i))); // prints '|' with message only if minimal is false, else only '|'
    }

    // bottom of table
    printf("└");
    for (int i = 0; i < (w * 2 + 1); i++) printf("─");
    printf("┘\n");

    if (!minimal) printf("%s\n", message); // print message
    strcpy(message, " "); // clear message

    return 0;
}
