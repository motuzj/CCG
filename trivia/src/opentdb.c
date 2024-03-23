#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "extern/b64.c/b64.h"
#include "extern/cJSON/cJSON.h"
#include "network.h"
#include "opentdb.h"
#include "main.h"

#define OPENTDB_URL_API "https://opentdb.com/api.php"
#define OPENTDB_URL_CATEGORIES "https://opentdb.com/api_category.php"

static char *opentdb_error_text[] = { "No errors detected.", "The API doesn't have enough questions for specified category", "Arguements passed in aren't valid.", " Session Token does not exist.", "Session Token has returned all possible questions for the specified query. Resetting the Token is necessary.", "Too many requests, please wait at least 5 seconds and try again." };

char *opentdb_error_code_to_string(int err_code) {
    return opentdb_error_text[err_code];
}

// print question with answers and returns correct answer number (from 0)
static Question opentdb_json_to_struct_question(cJSON *result, bool *err) {
    INIT_QUESTION(new_question);

    // write type to Question struct
    const cJSON *json_type = cJSON_GetObjectItemCaseSensitive(result, "type");
    if (cJSON_IsString(json_type)) {
        new_question.type = (char *)DECODE(json_type);
    } else {
        *err = true;
        fprintf(stderr, "Error: The question type was expected to be a string.\n");
        return new_question;
    }

    // write difficulty to Question struct
    const cJSON *json_difficulty = cJSON_GetObjectItemCaseSensitive(result, "difficulty");
    if (cJSON_IsString(json_difficulty)) {
        new_question.difficulty = (char *)DECODE(json_difficulty);
    } else {
        *err = true;
        fprintf(stderr, "Error: The question difficulty was expected to be a string.\n");
        return new_question;
    }

    // write category to Question struct
    const cJSON *json_category = cJSON_GetObjectItemCaseSensitive(result, "category");
    if (cJSON_IsString(json_category)) {
        new_question.category = (char *)DECODE(json_category);
    } else {
        *err = true;
        fprintf(stderr, "Error: The question category was expected to be a string.\n");
        return new_question;
    }

    // write question text to Question struct
    const cJSON *json_question_text = cJSON_GetObjectItemCaseSensitive(result, "question");
    if (cJSON_IsString(json_question_text)) {
        new_question.question_text = (char *)DECODE(json_question_text);
    } else {
        *err = true;
        fprintf(stderr, "Error: The question text was expected to be a string.\n");
        return new_question;
    }

    // write answers to Question struct
    const cJSON *correct_answer = cJSON_GetObjectItemCaseSensitive(result, "correct_answer");
    const cJSON *incorrect_answers = cJSON_GetObjectItemCaseSensitive(result, "incorrect_answers");

    new_question.answers_amount = cJSON_GetArraySize(incorrect_answers) + 1;
    new_question.answers = (char **)malloc(new_question.answers_amount * sizeof(char *));
    if (new_question.answers == NULL) {
        *err = true;
        fprintf(stderr, "Error: Failed to allocate memory.\n");
        return new_question;
    }
    
    // store incorrect answers
    for (int i = 0; i < new_question.answers_amount - 1; i++) {
        const cJSON *curr_incor_answer = cJSON_GetArrayItem(incorrect_answers, i);
        new_question.answers[i] = (char *)DECODE(curr_incor_answer);
    }

    // randomly place correct answer if not bool
    if (strcmp(new_question.type, "boolean") == 0) {
        if (strcmp(new_question.answers[0], "True") == 0) {
            new_question.corr_answ_index = 1;
            new_question.answers[1] = (char *)DECODE(correct_answer);
        } else if (strcmp(new_question.answers[0], "False") == 0) {
            new_question.corr_answ_index = 0;
            new_question.answers[1] = new_question.answers[0];
            new_question.answers[0] = (char *)DECODE(correct_answer);
        } else {
            fprintf(stderr, "Error: The boolean question is not in correct format.\n");
        }

        return new_question;
    }
    const int random = rand() % new_question.answers_amount;
    new_question.corr_answ_index = random;
    new_question.answers[new_question.answers_amount - 1] = new_question.answers[random];
    new_question.answers[random] = (char *)DECODE(correct_answer);

    return new_question;
}

char *opentdb_create_url(Arguments args) {
    char *url = (char *)malloc(255 * sizeof(char));

    char category_str[14] = "";
    if (args.category != 0) {
        sprintf(category_str, "&category=%d", args.category);
    }

    char difficulty_str[19] = "";
    if (strlen(args.difficulty) != 0) {
        sprintf(difficulty_str, "&difficulty=%s", args.difficulty);
    }

    char type_str[15] = "";
    if (strlen(args.type) != 0) {
        sprintf(type_str, "&type=%s", args.type);
    }

    sprintf(url, "%s?amount=%d%s%s%s&encode=base64", OPENTDB_URL_API, args.amount, category_str, difficulty_str, type_str);
    return url;
}

int opentdb_process_json(cJSON *json, Question **questions, Arguments args) {
    *questions = (Question *)malloc(args.amount * sizeof(Question));
    if (*questions == NULL) {
        return 1;
    }

    const cJSON *response_code_cJSON = cJSON_GetObjectItemCaseSensitive(json, "response_code");
    int response_code = response_code_cJSON->valueint;
    
    if (response_code != 0) {
        fprintf(stderr, "Error: %s\n", opentdb_error_code_to_string(response_code));
        return 1;
    }

    const cJSON *results = cJSON_GetObjectItemCaseSensitive(json, "results");
    cJSON *result = NULL;
    int n = 0;
    cJSON_ArrayForEach(result, results) {
        bool err = false;
        (*questions)[n] = opentdb_json_to_struct_question(result, &err);
        if (err) return 1;
        n++;
    }
    return 0;
}

int opentdb_list_categories() {
    char *response = get_string_from_url(OPENTDB_URL_CATEGORIES);

    cJSON *json = cJSON_Parse(response);
    if (json == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error: %s\n", error_ptr);
        }
        cJSON_Delete(json);
        return 1;
    }

    const cJSON *categories = cJSON_GetObjectItemCaseSensitive(json, "trivia_categories");
    cJSON *category = NULL;

    printf("ID  Category name\n----------------\n");
    cJSON_ArrayForEach(category, categories) {
        const cJSON *id = cJSON_GetObjectItemCaseSensitive(category, "id");
        const cJSON *name = cJSON_GetObjectItemCaseSensitive(category, "name");
        printf("%3d %s\n", id->valueint, name->valuestring);
    }
    cJSON_Delete(json);
    return 0;
}
