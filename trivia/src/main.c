#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "extern/cJSON/cJSON.h"
#include "network.h"
#include "extern/b64.c/b64.h"

#define decode(x) b64_decode(x->valuestring, strlen(x->valuestring))

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

int main() {
    srand(time(NULL));

    // load json
    char *json_data = get_json("https://opentdb.com/api.php?amount=10&type=multiple&encode=base64");
    
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

    process_json(json);
    
    cJSON_Delete(json);
    return 0;
}
