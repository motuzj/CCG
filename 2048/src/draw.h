#ifndef DRAW_H
#define DRAW_H

#include <stddef.h>

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

// #define COLOR_0 "\033[8m"
// #define COLOR_2 "\033[90m"
// #define COLOR_4 "\033[93m"
// #define COLOR_8 "\033[33m"
// #define COLOR_16 "\033[32m"
// #define COLOR_32 "\033[92m"
// #define COLOR_64 "\033[36m"
// #define COLOR_128 "\033[96m"
// #define COLOR_256 "\033[35m"
// #define COLOR_512 "\033[95m"
// #define COLOR_1024 "\033[34m"
// #define COLOR_2048 "\033[31m"
// #define COLOR_OTHER "\033[91m"
// #define COLOR_RESET "\033[0m"

int draw(const int board[4][4], size_t side_size);

#endif
