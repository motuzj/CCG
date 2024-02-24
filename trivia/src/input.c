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
    char input[2];
    printf("Your answer: ");
    scanf("%s", input);
    return input[0];
}
