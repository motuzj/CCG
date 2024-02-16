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

// default
Arguments args = {
    .amount = 10,
    .category = 0,
    .difficulty = "",
    .type = "multiple",
    .formatting = false
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
                printf("TODO\n");
                break;
        }
    }
    return 0;
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
    cJSON *results = cJSON_GetObjectItemCaseSensitive(json, "results");
    const cJSON *result = NULL;
    cJSON_ArrayForEach(result, results) {
        cJSON *question = cJSON_GetObjectItemCaseSensitive(result, "question");
        cJSON *correct_answer = cJSON_GetObjectItemCaseSensitive(result, "correct_answer");
        cJSON *incorrect_answers = cJSON_GetObjectItemCaseSensitive(result, "incorrect_answers");

        // print the question
        if (cJSON_IsString(question)) printf("Question: %s\n", decode(question));

        printf("Options: ");
        int n = cJSON_GetArraySize(incorrect_answers) + 1; // number of all answers
        char **answers = (char **)malloc(n * sizeof(char *));
        if (answers == NULL) {
            fprintf(stderr, "Error: Failed to allocate memory.\n");
            return 1;
        }
        
        // store incorrect answers
        for (int i = 0; i < n - 1; i++) {
            cJSON *curr_incor_answer = cJSON_GetArrayItem(incorrect_answers, i);
            answers[i] = decode(curr_incor_answer);
        }

        // randomly place correct answer
        int random = rand() % n;
        answers[n - 1] = answers[random];
        answers[random] = decode(correct_answer);

        // print all avaible options (answers)
        for (int i = 0; i < n; i++) {
            printf("%c) %s%s", 'a' + i, answers[i], (n - 1 != i) ? ", " : "\n");
        }

        // get user input
        char input[255];
        printf("Your answer: ");
        scanf("%255s", input);

        // check input with the correct answer
        if (input[0] - 'a' == random) {
            printf("Correct!\n");
        }
        printf("\n");

        // free all answers
        for (int i = 0; i < n; i++) {
            free(answers[i]);
        }
        free(answers);
    }
    return 0;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    process_args(argc, argv);

    // load json from url
    
    char *url = create_url();
    char *json_data = get_json(url);
    
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
    free(url);
    return 0;
}
