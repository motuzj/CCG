#ifndef OPENTDB_H
#define OPENTDB_H

#include "main.h"
#include "extern/cJSON/cJSON.h"

#define OPENTDB_URL_API "https://opentdb.com/api.php"
#define OPENTDB_URL_CATEGORIES "https://opentdb.com/api_category.php"

char *opentdb_create_url(Arguments args);
int opentdb_process_json(cJSON *json, Question **questions, Arguments args);
int opentdb_list_categories();

#endif
