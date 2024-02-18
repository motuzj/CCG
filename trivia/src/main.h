#ifndef MAIN_H
#define MAIN_H

#define decode(x) b64_decode(x->valuestring, strlen(x->valuestring))
#define uint8_t unsigned char

typedef struct Arguments{
    uint8_t amount; // number of questions
    uint8_t category; // id of categories, 0 is all categories
    char difficulty[7]; // difficulty of questions - easy / medium / hard, 0 is all difficulties
    char type[9]; // type of question - multiple / boolean, 0 is all types
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

#define init_question(x) Question x = { .index = 0, .type = NULL, .difficulty = NULL, .category = NULL, .question_text = NULL, .answers = NULL, .answers_amount = 0, .corr_answ_index = 0, .correctly_answered = false }

Question *questions;

#endif
