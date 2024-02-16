#ifndef MAIN_H
#define MAIN_H

#define decode(x) b64_decode(x->valuestring, strlen(x->valuestring))
#define uint8_t unsigned char

typedef struct {
    uint8_t amount; // number of questions
    uint8_t category; // id of categories, 0 is all categories
    char difficulty[7]; // difficulty of questions - easy / medium / hard, 0 is all difficulties
    char type[9]; // type of question - multiple / boolean, 0 is all types
    bool formatting; // use formatting / colors
} Arguments;

#endif
