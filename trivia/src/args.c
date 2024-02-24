#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "draw.h"
#include "opentdb.h"
#include "main.h"

int process_args(int argc, char *const argv[], Arguments *args) {
    char *str = NULL;
    int opt = 0;
    while ((opt = getopt(argc, argv, "fhln:c:d:t:")) != -1) {
        switch (opt) {
            case 'f':
                args->formatting = false;
                break;
            case 'h':
                print_help();
                exit(EXIT_SUCCESS);
            case 'l':
                opentdb_list_categories();
                exit(EXIT_SUCCESS);
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
                args->amount = n;
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
                args->category = c;
                break;
            case 'd':
                str = strdup(optarg);
                for(char *p=str; *p; ++p) *p=tolower(*p);
                if (strcmp(str, "e") == 0) {
                    args->difficulty = "easy";
                } else if (strcmp(str, "m") == 0) {
                    args->difficulty = "medium";
                } else if (strcmp(str, "h") == 0) {
                    args->difficulty = "hard";
                } else if (strcmp(str, "easy") == 0 || strcmp(str, "medium") == 0 || strcmp(str, "hard") == 0) {
                    args->difficulty = str;
                }
                break;
            case 't':
                str = strdup(optarg);
                for(char *p=str; *p; ++p) *p=tolower(*p);
                if (strcmp(str, "m") == 0) {
                    args->type = "multiple";
                } else if (strcmp(str, "b") == 0) {
                    args->type = "boolean";
                } else if (strcmp(str, "multiple") == 0 || strcmp(str, "boolean") == 0) {
                    args->type = str;
                }
                break;
        }
    }
    return 0;
}
