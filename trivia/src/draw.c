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

int print_question(Question question, Arguments args, int question_number) {
	// print difficulty
	switch (question.difficulty[0]) {
		case 'e':
			printf("%sEASY%s, ", args.formatting ? FORMAT_COLOR_GREEN : "", args.formatting ? FORMAT_RESET : "");
			break;
		case 'm':
			printf("%sMEDIUM%s, ", args.formatting ? FORMAT_COLOR_YELLOW : "", args.formatting ? FORMAT_RESET : "");
			break;
		case 'h':
			printf("%sHARD%s, ", args.formatting ? FORMAT_COLOR_RED : "", args.formatting ? FORMAT_RESET : "");
			break;
		default:
			printf("%s, ", question.difficulty);
			break;
	}

	// print category
	printf("%s\"%s\"%s\n", args.formatting ? FORMAT_ITALIC : "", question.category, args.formatting ? FORMAT_RESET : "");

    // print the question
    printf("%d. Q: %s%s%s\n", question_number, args.formatting ? FORMAT_BOLD : "", question.question_text, args.formatting ? FORMAT_RESET : "");

    // print all avaible options (answers)
    for (int i = 0; i < question.answers_amount; i++) {
        printf("%c) %s%s%s%s", 'a' + i, args.formatting ? FORMAT_UNDERLINE : "", question.answers[i], args.formatting ? FORMAT_RESET : "", (question.answers_amount - 1 != i) ? ", " : "\n");
    }
    printf("\n");
    return 0;
}
