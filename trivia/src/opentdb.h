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

char *opentdb_error_code_to_string(int err_code);
char *opentdb_create_url(Arguments args);
int opentdb_process_json(cJSON *json, Question **questions, Arguments args);
int opentdb_list_categories();

#endif
