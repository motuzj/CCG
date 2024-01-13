#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char *get_word(const char *dict) {
    FILE *file = fopen(dict, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Can't open file. Does it really exist?\n");
        return NULL;
    }

    if (fgetc(file) == EOF) {
        fprintf(stderr, "Error: File is empty\n");
        return NULL;
    }

    // count all newlines in file
    int line_count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n') {
            line_count++;
        }
    }

    rewind(file);

    srand(time(NULL));
    int random_line = rand() % line_count;

    char *line = NULL;
    size_t line_length = 0;
    long read;

    // save lines to 'read' until a random_line is reached
    for (int current_line = 0; current_line <= random_line; current_line++) {
        read = getline(&line, &line_length, file);
        if (read == -1) {
            fprintf(stderr, "Error: Can't read file\n");
            return NULL;
        }
    }

    fclose(file);

    // remove newline from 'line'
    line[strlen(line) - 1] = '\0';

    return line;
}

int is_word_in_dict(const char *word, const char *dict) {
    FILE *file = fopen(dict, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Can't open file. Does it really exist?\n");
        fclose(file);
        return -1;
    }

    if (fgetc(file) == EOF) {
        fprintf(stderr, "Error: File is empty\n");
        fclose(file);
        return -1;
    }

    char temp[6];

    while (fgets(temp, sizeof(temp), file)) {
        if (!strcmp(temp, word)) {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

bool char_exists(char ch, char arr[]) {
    for (int i = 0; i < strlen(arr); i++) {
        if (arr[i] == ch) {
            return true;
        }
    }
    return false;
}

bool copy_char_to_array(char ch, char *array) {
    if (char_exists(ch, array)) {
        return false;
    }
    int length = strlen(array);
    array[length] = ch;
    array[length + 1] = '\0';
    return true;
}
