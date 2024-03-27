#ifndef MAIN_H
#define MAIN_H

#define FORMAT_COLOR_GREEN "\033[32m"
#define FORMAT_COLOR_YELLOW "\033[33m"
#define FORMAT_COLOR_RED "\033[31m"

#define FORMAT_RESET "\033[0m"
#define FORMAT_BOLD "\033[1m"
#define FORMAT_ITALIC "\033[3m"
#define FORMAT_UNDERLINE "\033[4m"

#define DECODE(X) b64_decode(X->valuestring, strlen(X->valuestring))
#define uint8_t unsigned char

typedef struct Arguments{
    uint8_t amount; // number of questions
    uint8_t category; // id of category, 0 is all categories
    char *difficulty; // difficulty of questions - easy / medium / hard, 0 is all difficulties
    char *type; // type of question - multiple / boolean, 0 is all types
    bool formatting; // use formatting / colors
} Arguments;

typedef struct Question{
    uint8_t index; // index of the question
    char *type; // type of the question; multiple / boolean
    char *difficulty; // difficulty of the question; easy / medium / hard
    char *category; // category of the question
    char *question_text; // question asked
    char **answers; // all answers including correct and incorrect ones
    uint8_t answers_amount; // amount of answers
    uint8_t corr_answ_index; // index number for the correct answer in 'answers'
    bool correctly_answered; // true if user answered question correctly, default is false
} Question;

#define INIT_QUESTION(X) Question X = { .index = 0, .type = NULL, .difficulty = NULL, .category = NULL, .question_text = NULL, .answers = NULL, .answers_amount = 0, .corr_answ_index = 0, .correctly_answered = false }

#endif
