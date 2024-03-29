#include <stdbool.h>
#include <stdio.h>

#include "main.h"

bool check_user_answer(Question question, char user_input) {
    if (user_input == question.corr_answ_index + 'a') {
        return true;
    }
    return false;
}

char get_input() {
    char input;
    printf("Your answer: ");
    input = getchar();

    // flush stdin
    int temp;
    while ((temp = fgetc(stdin)) != '\n' && temp != EOF);

    return input;
}
