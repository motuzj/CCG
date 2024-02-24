#ifndef DRAW_H
#define DRAW_H

#include "main.h"

#define FORMAT_RESET "\033[0m"
#define FORMAT_BOLD "\033[1m"
#define FORMAT_UNDERLINE "\033[4m"
#define FORMAT_CORRECT "\033[32m"
#define FORMAT_WRONG "\033[31m"

int print_help();
int print_question(Question question, Arguments args);

#endif
