#include <stddef.h>
#include <stdio.h>

#include "draw.h"
#include "main.h"

int repeat_char(int ch, size_t side_size) {
    printf("│");
    for (size_t i = 0; i < side_size * 5; i++) {
        printf("%c", ch);
    }
    printf("│\n");
    return 0;
}

int draw(const int board[BOARD_SIZE][BOARD_SIZE], size_t side_size) {
    // top of a border
    printf("┌");
    for (int i = 0; i < side_size * 5; i++) {
        printf("─");
    }
    printf("┐\n");

    repeat_char(' ', side_size);

    for (int i = 0; i < side_size; i++) {
        printf("│  ");
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

            printf("%s%4d%s", color_code, board[i][j], COLOR_RESET);
        }
        printf("  │\n");
        repeat_char(' ', side_size);
    }

    // bottom of a border
    printf("└");
    for (int i = 0; i < side_size * 5; i++) {
        printf("─");
    }
    printf("┘\n");
    return 0;
}
