#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "draw.h"
#include "main.h"

int draw(int **board, int side_size) {
    printf("\033[1;1H\033[2J");
    int n = 0;

    // top of a border
    repeat_char("─", "┌", "┐", side_size, n);
    n++;
    repeat_char(" ", "│", "│", side_size, n);

    for (int i = 0; i < side_size; i++) {
        n++;
        printf("│%*s", PADDING, " ");
        for (int j = 0; j < side_size; j++) {
            const char *color_code = COLOR_OTHER;

            // clang-format off
            switch (board[i][j]) {
                case 0: color_code = COLOR_0; break;
                case 2: color_code = COLOR_2; break;
                case 4: color_code = COLOR_4; break;
                case 8: color_code = COLOR_8; break;
                case 16: color_code = COLOR_16; break;
                case 32: color_code = COLOR_32; break;
                case 64: color_code = COLOR_64; break;
                case 128: color_code = COLOR_128; break;
                case 256: color_code = COLOR_256; break;
                case 512: color_code = COLOR_512; break;
                case 1024: color_code = COLOR_1024; break;
                case 2048: color_code = COLOR_2048; break;
            }
            // clang-format on

            printf("%s%*d%s", color_code, CELL_SIZE, board[i][j], COLOR_RESET);
        }
        printf("%*s│%s\n", PADDING, " ", print_message(n));
        n++;
        repeat_char(" ", "│", "│", side_size, n);
    }

    // bottom of a border
    n++;
    repeat_char("─", "└", "┘", side_size, n);
    return 0;
}

char *print_message(int n) {
    if (minimal) {
        return "";
    }
    static char temp[25];
    sprintf(temp, "  SCORE: %8lu", score);
    // clang-format off
    switch (n) {
        case 0: return "      2 0 4 8    ";
        case 1: return "  ---------------";
        case 2: return temp;

        default: return "";
    }
    // clang-format on
}

int repeat_char(char *ch, char *first_char, char *last_char, int side_size, int n) {
    printf("%s", first_char);
    for (int i = 0; i < side_size * CELL_SIZE + PADDING * 2; i++) {
        printf("%s", ch);
    }
    printf("%s%s\n", last_char, print_message(n));
    return 0;
}
