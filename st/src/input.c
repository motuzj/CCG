#include <ctype.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

#include "main.h"

struct termios original_termios;

void disable_raw_mode(int signum) {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
    printf("\033[2J\033[H"); // clear screen
    printf("\033[?25h");     // restore cursor
    exit(0);
}

void enable_raw_mode(void) {
    tcgetattr(STDIN_FILENO, &original_termios);
    atexit((void (*)(void))disable_raw_mode);
    signal(SIGINT, disable_raw_mode);
    struct termios new_termios = original_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &new_termios);
}

int get_input(void) {
    struct pollfd fds[1];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    int temp = poll(fds, 1, 50);
    if (temp == -1) {
        perror("poll");
        exit(-1);
    } else if (temp > 0) {
        char input;
        if (read(STDIN_FILENO, &input, 1) == -1) {
            return 0;
        }
        return input;
    }
    return 0;
}

int process_input(Spaceship *spaceship, int key) {
    if (key == 'w' || key == 'W') {
        spaceship->row--;
        if (spaceship->row < 1) {
            spaceship->row = 1;
        }
    } else if (key == 's' || key == 'S') {
        spaceship->row++;
        if (spaceship->row + spaceship->texture_lines + 1 > rows) {
            spaceship->row = rows - spaceship->texture_lines;
        }
    } else if (key == 'q' || key == 'Q') {
        exit(0);
    }
    return 0;
}
