#include <ctype.h>
#include <poll.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

int board_row;
int board_col;

enum Direction {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT
};

struct Pad {
    int x;
    int y;
    int dir;
    const int key_up;
    const int key_down;
    const int key_left;
    const int key_right;
};

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

int get_input(struct Pad *player) {
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

int place_fruit(bool fruits[]) {
    srand(time(NULL));

    int rand_row;
    int rand_col;

    do {
        rand_col = rand() % board_col;
        rand_row = rand() % board_row;
    } while (fruits[rand_row * board_col + rand_col] == true);
    fruits[rand_row * board_col + rand_col] = true;

    return 0;
}

int process_input(struct Pad *player, int input) {
    if (input == player->key_up || input == toupper(player->key_up)) {
        player->dir = UP;
    } else if (input == player->key_down || input == toupper(player->key_down)) {
        player->dir = DOWN;
    } else if (input == player->key_left || input == toupper(player->key_left)) {
        player->dir = LEFT;
    } else if (input == player->key_right || input == toupper(player->key_right)) {
        player->dir = RIGHT;
    }
    return 0;
}

int set_to_boundaries(struct Pad *player) {
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    if (player->y < 1) {
        player->y = 1;
    } else if (player->y > board_row - 3) {
        player->y = board_row - 3;
    } else if (player->x < 1) {
        player->x = 1;
    } else if (player->x > board_col - 2) {
        player->x = board_col - 2;
    }
    return 0;
}

int move(struct Pad *player) {
    switch (player->dir) {
        case UP: {
            player->y -= 1;
            break;
        }
        case DOWN: {
            player->y += 1;
            break;
        }
        case LEFT: {
            player->x -= 1;
            break;
        }
        case RIGHT: {
            player->x += 1;
            break;
        }
    }
    set_to_boundaries(player);
    return 0;
}

int draw(struct Pad player1, struct Pad player2, bool fruits[], int frames) {
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);

    for (int i = 0; i < board_row - 1; i++) {
        for (int j = 0; j < board_col; j++) {
            // make this better!!!!
            if (i == 0 && j == 0) {
                printf("%5d", frames);
                continue;
            }
            if (i == 0 && j <= 4) {
                continue;
            }
            if (i == 0 || i == board_row - 2 || j == 0 || j == board_col - 1) {
                printf("#");
            } else if ((i == player1.y && j == player1.x) || (i == player2.y && j == player2.x)) {
                printf("O");
            } else if (fruits[i * board_col + j] == true) {
                printf("X");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}

int main() {
    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    board_col = ws.ws_col;
    board_row = ws.ws_row;

    bool fruits[board_col * board_row]; // if the cell is true it contains a fruit
    for (int i = 0; i < board_col * board_row; i++) {
        fruits[i] = false;
    }

    struct Pad player1 = {board_col / 3, board_row / 2, NONE, 'w', 's', 'a', 'd'};
    struct Pad player2 = {board_col / 3 * 2, board_row / 2, NONE, 'i', 'k', 'j', 'l'};

    enableRawMode();

    int frames = 0;

    while (1) {
        if (frames % 100 == 0) {
            place_fruit(fruits);
        }
        int input = get_input(&player1);
        process_input(&player1, input);
        process_input(&player2, input);
        draw(player1, player2, fruits, frames);
        move(&player1);
        move(&player2);
        frames++;
    }
    return 0;
}