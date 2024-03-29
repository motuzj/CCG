#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "extern/cJSON/cJSON.h"
#include "args.h"
#include "draw.h"
#include "input.h"
#include "network.h"
#include "opentdb.h"
#include "main.h"

static void free_questions(Question *questions, Arguments args) {
    for (int i = 0; i < args.amount; i++) {
        for (int j = 0; j < questions[i].answers_amount; j++) {
            free(questions[i].answers[j]);
        }
        free(questions[i].answers);
        free(questions[i].type);
        free(questions[i].difficulty);
        free(questions[i].category);
        free(questions[i].question_text);
    }
    free(questions);
}

int main(int argc, char *argv[]) {
    // default arguments
    Arguments args = {
        .amount = 10,
        .category = 0,
        .difficulty = "",
        .type = "",
        .formatting = true
    };
    Question *questions = NULL; // struct array of questions

    srand(time(NULL));

    process_args(argc, argv, &args);

    // get json from url
    char *url = opentdb_create_url(args);
    char *json_data = get_string_from_url(url);
    free(url);
    
    // parse json into struct 'questions'
    cJSON *json = cJSON_Parse(json_data);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error: %s\n", error_ptr);
        }
        cJSON_Delete(json);
        return 1;
    }
    if (opentdb_process_json(json, &questions, args)) return EXIT_FAILURE;
    cJSON_Delete(json);

    // loop thru every question
    for (int i = 0; i < args.amount; i++) {
        print_question(questions[i], args, i + 1);

        // get user input
        const char input = get_input();

        // check input with the correct answer
        if (check_user_answer(questions[i], input)) {
            questions[i].correctly_answered = true;
        }

        // print whether user's answer is correct
        print_answer_result(questions[i], args);
    }

    print_stats(questions, args);

    free_questions(questions, args);

    return EXIT_SUCCESS;
}
