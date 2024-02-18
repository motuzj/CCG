#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>
#include <ctype.h>

#include "extern/cJSON/cJSON.h"
#include "network.h"
#include "extern/b64.c/b64.h"
#include "main.h"

#define FORMAT_RESET "\033[0m"
#define FORMAT_BOLD "\033[1m"
#define FORMAT_UNDERLINE "\033[4m"
#define FORMAT_CORRECT "\033[32m"
#define FORMAT_WRONG "\033[31m"

// default
Arguments args = {
    .amount = 10,
    .category = 0,
    .difficulty = "",
    .type = "",
    .formatting = true
};

int process_args(int argc, char *const argv[]) {
    int opt = 0;
    while ((opt = getopt(argc, argv, "n:c:d:t:f")) != -1) {
        switch (opt) {
            case 'n':
                if (!isdigit(*optarg)) {
                    fprintf(stderr, "Error: The argument for the number of questions must be a valid number.\n");
                    exit(EXIT_FAILURE);
                }
                int n = atoi(optarg);
                if (n <= 0 || n > 50) {
                    fprintf(stderr, "Error: Number of questions can't be smaller than 1 and bigger than 50.\n");
                    exit(EXIT_FAILURE);
                }
                args.amount = n;
                break;
            case 'c':
                if (!isdigit(*optarg)) {
                    fprintf(stderr, "Error: The argument for the ID of category must be a valid number.\n");
                    exit(EXIT_FAILURE);
                }
                int c = atoi(optarg);
                if (c <= 0 || c > 50) {
                    fprintf(stderr, "Error: Category ID must be 0 - 63.\n");
                    exit(EXIT_FAILURE);
                }
                args.category = c;
                break;
            case 'd':
                printf("TODO\n");
                break;
            case 't':
                printf("TODO\n");
                break;
            case 'f':
                args.formatting = false;
                break;
        }
    }
    return 0;
}

// print question with answers and returns correct answer number (from 0)
Question get_struct_question(const cJSON *result, bool *err) {
    init_question(new_question);

    // write type to Question struct
    cJSON *json_type = cJSON_GetObjectItemCaseSensitive(result, "question");
    if (cJSON_IsString(json_type)) {
        new_question.type = (char *)decode(json_type);
    } else {
        *err = true;
        fprintf(stderr, "Error: The question type was expected to be a string.\n");
        return new_question;
    }

    // write difficulty to Question struct
    cJSON *json_difficulty = cJSON_GetObjectItemCaseSensitive(result, "difficulty");
    if (cJSON_IsString(json_difficulty)) {
        new_question.difficulty = (char *)decode(json_difficulty);
    } else {
        *err = true;
        fprintf(stderr, "Error: The question difficulty was expected to be a string.\n");
        return new_question;
    }

    // write category to Question struct
    cJSON *json_category = cJSON_GetObjectItemCaseSensitive(result, "category");
    if (cJSON_IsString(json_category)) {
        new_question.category = (char *)decode(json_category);
    } else {
        *err = true;
        fprintf(stderr, "Error: The question category was expected to be a string.\n");
        return new_question;
    }

    // write question text to Question struct
    cJSON *json_question_text = cJSON_GetObjectItemCaseSensitive(result, "question");
    if (cJSON_IsString(json_question_text)) {
        new_question.question_text = (char *)decode(json_question_text);
    } else {
        *err = true;
        fprintf(stderr, "Error: The question text was expected to be a string.\n");
        return new_question;
    }

    // write answers to Question struct
    cJSON *correct_answer = cJSON_GetObjectItemCaseSensitive(result, "correct_answer");
    cJSON *incorrect_answers = cJSON_GetObjectItemCaseSensitive(result, "incorrect_answers");

    new_question.answers_amount = cJSON_GetArraySize(incorrect_answers) + 1;
    new_question.answers = (char **)malloc(new_question.answers_amount * sizeof(char *));
    if (new_question.answers == NULL) {
        *err = true;
        fprintf(stderr, "Error: Failed to allocate memory.\n");
        return new_question;
    }
    
    // store incorrect answers
    for (int i = 0; i < new_question.answers_amount - 1; i++) {
        cJSON *curr_incor_answer = cJSON_GetArrayItem(incorrect_answers, i);
        new_question.answers[i] = (char *)decode(curr_incor_answer);
    }

    // randomly place correct answer
    int random = rand() % new_question.answers_amount;
    new_question.corr_answ_index = random;
    new_question.answers[new_question.answers_amount - 1] = new_question.answers[random];
    new_question.answers[random] = (char *)decode(correct_answer);

    return new_question;
}

char *create_url() {
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

    sprintf(url, "https://opentdb.com/api.php?amount=%d%s%s%s&encode=base64", args.amount, category_str, difficulty_str, type_str);
    return url;
}

int process_json(cJSON *json) {
    questions = (Question *)malloc(args.amount * sizeof(Question));
    if (questions == NULL) {
        return 1;
    }

    cJSON *results = cJSON_GetObjectItemCaseSensitive(json, "results");
    const cJSON *result = NULL;
    int n = 0;
    cJSON_ArrayForEach(result, results) {
        bool err = false;
        questions[n] = get_struct_question(result, &err);
        if (err) return 1;
        n++;
    }
    return 0;
}

int print_question(Question question) {
    // print the question
    printf("Q: %s%s%s\n", args.formatting ? FORMAT_BOLD : "", question.question_text, args.formatting ? FORMAT_RESET : "");

    // print all avaible options (answers)
    for (int i = 0; i < question.answers_amount; i++) {
        printf("%c) %s%s%s%s", 'a' + i, args.formatting ? FORMAT_UNDERLINE : "", question.answers[i], args.formatting ? FORMAT_RESET : "", (question.answers_amount - 1 != i) ? ", " : "\n");
    }
    printf("\n");
    return 0;
}

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

int main(int argc, char *argv[]) {
    srand(time(NULL));

    process_args(argc, argv);

    // load json from url
    char *url = create_url();
    char *json_data = get_json(url);
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

    if (process_json(json)) return 1;
    
    cJSON_Delete(json);

    for (int i = 0; i < args.amount; i++) {
        print_question(questions[i]);
        char input = get_input();
        if (check_user_answer(questions[i], input)) {
            questions[i].correctly_answered = true;
        }

        // check input with the correct answer
        if (questions[i].correctly_answered) {
            printf("%sCorrect!%s\n\n", args.formatting ? FORMAT_CORRECT : "", args.formatting ? FORMAT_RESET : "");
        } else {
            printf("%sWrong, correct answer was: %c) %s%s%s\n\n", args.formatting ? FORMAT_WRONG : "", questions[i].corr_answ_index + 'a', args.formatting ? FORMAT_UNDERLINE : "", questions[i].answers[questions[i].corr_answ_index], args.formatting ? FORMAT_RESET : "");
        }
    }
    return 0;
}
