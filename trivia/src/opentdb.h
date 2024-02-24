#ifndef OPENTDB_H
#define OPENTDB_H

#include "main.h"
#include "extern/cJSON/cJSON.h"

typedef enum {
    SUCCESS = 0,
    NO_RESULT = 1,
    INVALID_PARAMETER = 2,
    TOKEN_NOT_FOUND = 3,
    TOKEN_EMPTY = 4,
    RATE_LIMIT = 5
} opentdb_error_enum;

// print question with answers and returns correct answer number (from 0)
Question opentdb_json_to_struct_question(cJSON *result, bool *err);
char *opentdb_create_url(Arguments args);
int opentdb_process_json(cJSON *json, Question **questions, Arguments args);
int opentdb_list_categories();

#endif
