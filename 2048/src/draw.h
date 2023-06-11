#ifndef DRAW_H
#define DRAW_H

#include <stddef.h>

#define CELL_SIZE 5
#define PADDING 2

#define COLOR_0 "\033[8m"
#define COLOR_2 "\033[100m"
#define COLOR_4 "\033[103m"
#define COLOR_8 "\033[43m"
#define COLOR_16 "\033[42m"
#define COLOR_32 "\033[102m"
#define COLOR_64 "\033[46m"
#define COLOR_128 "\033[106m"
#define COLOR_256 "\033[45m"
#define COLOR_512 "\033[105m"
#define COLOR_1024 "\033[44m"
#define COLOR_2048 "\033[41m"
#define COLOR_OTHER "\033[101m"
#define COLOR_RESET "\033[0m"

/*
 * Function: draw
 * Description: Returns a message used to display different information.
 * Arguments:
 *   board - Pointer to 2D array board
 *   side_size - Length of one side of board.
 */
int draw(int **board, int side_size);

/*
 * Function: print_message
 * Description: Returns a message used to display different information.
 * Arguments:
 *   n - Int that determines the message to be returned.
 * Return Value:
 *   Returns a message.
 */
char *print_message(int n);

/*
 * Function: print_message
 * Description: Prints provided char multiple times (calculated by side_size) surrounded by specified characters and with message.
 * Arguments:
 *   ch - Character to be repeated.
 *   first_char - first char that will be printed.
 *   last_char - last char that will be printed before message.
 *   side_size - Length of one side of board.
 *   n - Int that determines the message to be printed.
 * Return Value:
 *   Returns a message.
 */
int repeat_char(char *ch, char *first_char, char *last_char, int side_size, int n);

#endif
