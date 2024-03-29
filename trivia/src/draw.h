#ifndef DRAW_H
#define DRAW_H

#include "main.h"

#define FORMAT_COLOR_GREEN "\033[32m"
#define FORMAT_COLOR_YELLOW "\033[33m"
#define FORMAT_COLOR_RED "\033[31m"

#define FORMAT_RESET "\033[0m"
#define FORMAT_BOLD "\033[1m"
#define FORMAT_ITALIC "\033[3m"
#define FORMAT_UNDERLINE "\033[4m"

void print_help();
void print_question(Question question, Arguments args, int question_number);
void print_answer_result(Question question, Arguments args);
void print_stats(Question *questions, Arguments args);

#endif
