#include <stdio.h>
#include <stdbool.h>

#include "main.h"

int print_help() {
	printf("Usage: trivia [OPTION]...\n");
	printf("\n");
	printf("Options:\n");
	printf("  -n NUMBER\tSet the number of questions\n");
	printf("  -c NUMBER\tSet the category ID of questions, to get list of categories use option '-l'\n");
	printf("  -d STRING\tSet the difficulty of questions (easy / e, medium / m, hard / h)\n");
	printf("  -t STRING\tSet the type of questions (multiple / m, boolean / b)\n");
	printf("  -l\t\tList avaible categories\n");
	printf("  -f\t\tDisable all escape sequences\n");
	printf("  -h\t\tShow this help message and exit\n");
	return 0;
}

int print_question(Question question, Arguments args) {
    // print the question
    printf("Q: %s%s%s\n", args.formatting ? FORMAT_BOLD : "", question.question_text, args.formatting ? FORMAT_RESET : "");

    // print all avaible options (answers)
    for (int i = 0; i < question.answers_amount; i++) {
        printf("%c) %s%s%s%s", 'a' + i, args.formatting ? FORMAT_UNDERLINE : "", question.answers[i], args.formatting ? FORMAT_RESET : "", (question.answers_amount - 1 != i) ? ", " : "\n");
    }
    printf("\n");
    return 0;
}
