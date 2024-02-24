#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "extern/b64.c/b64.h"
#include "extern/cJSON/cJSON.h"
#include "args.h"
#include "draw.h"
#include "input.h"
#include "network.h"
#include "opentdb.h"
#include "main.h"

int main(int argc, char *argv[]) {
    // default arguments
    Arguments args = { .amount = 10, .category = 0, .difficulty = "", .type = "", .formatting = true};
    Question *questions = NULL; // struct array of questions

    srand(time(NULL));

    process_args(argc, argv, &args);

    // get json from url
    char *url = opentdb_create_url(args);
    char *json_data = get_string_from_url(url);
    free(url);
    
    // parse json
    cJSON *json = cJSON_Parse(json_data);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error: %s\n", error_ptr);
        }
        cJSON_Delete(json);
        return 1;
    }
    if (opentdb_process_json(json, &questions, args)) return 1;
    cJSON_Delete(json);

    // loop thru every question
    for (int i = 0; i < args.amount; i++) {
        print_question(questions[i], args);

        const char input = get_input(); // get user input

        // check input with the correct answer
        if (check_user_answer(questions[i], input)) {
            questions[i].correctly_answered = true;
        }

        // print whether user's answer is correct
        if (questions[i].correctly_answered) {
            printf("%sCorrect!%s\n\n", args.formatting ? FORMAT_CORRECT : "", args.formatting ? FORMAT_RESET : "");
        } else {
            printf("%sWrong, correct answer was: %c) %s%s%s\n\n", args.formatting ? FORMAT_WRONG : "", questions[i].corr_answ_index + 'a', args.formatting ? FORMAT_UNDERLINE : "", questions[i].answers[questions[i].corr_answ_index], args.formatting ? FORMAT_RESET : "");
        }
    }

    // free questions and answers in them
    for (int i = 0; i < args.amount; i++) {
        for (int j = 0; j < questions[i].answers_amount; j++) {
            free(questions[i].answers[j]);
        }
    }
    free(questions);
    return 0;
}
