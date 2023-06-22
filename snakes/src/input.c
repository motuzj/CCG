#include <ctype.h>
#include <poll.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>

#include "main.h"

struct termios origTermios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &origTermios);
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &origTermios);
    atexit(disableRawMode);

    struct termios raw = origTermios;
    raw.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int get_input(struct Player *player) {
    struct pollfd fds[1];
    fds[0].fd = STDIN_FILENO;
    fds[0].events = POLLIN;

    int temp = poll(fds, 1, 50);
    if (temp == -1) {
        perror("poll");
        return -1;
    } else if (temp > 0) {
        char input;
        if (read(STDIN_FILENO, &input, 1) == -1) {
            return 0;
        }
        return input;
    }
    return 0;
}

int process_input(struct Player *player, int key) {
    if ((key == player->key_up || key == toupper(player->key_up)) && player->dir != DOWN) {
        player->dir = UP;
    } else if ((key == player->key_down || key == toupper(player->key_down)) && player->dir != UP) {
        player->dir = DOWN;
    } else if ((key == player->key_left || key == toupper(player->key_left)) && player->dir != RIGHT) {
        player->dir = LEFT;
    } else if ((key == player->key_right || key == toupper(player->key_right)) && player->dir != LEFT) {
        player->dir = RIGHT;
    } else if (key == 'q' || key == 'Q') {
        exit(0);
    }
    return 0;
}
