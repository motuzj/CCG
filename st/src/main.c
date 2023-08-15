#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "spaceships.h"
#include "stars.h"

int columns = 80;
int rows = 25;

struct termios original_termios;

typedef struct {
    const char *name;
    const bool is_enemy;
    char texture; // texture of spaceship from spaceships.h
    int shields;
    int column; // spaceships column (top left corner)
    int row;    // spaceship row (top left corner)
} Spaceship;

int init_termios() {
    tcgetattr(STDIN_FILENO, &original_termios);
    struct termios new_termios = original_termios;
    new_termios.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
    return 0;
}

int print_ship(const char ship[][50], int lines) {
    for (int i = 0; i < lines; i++) {
        printf("%s\n", ship[i]);
    }
}

int main() {
    print_ship(enterprise, 5);
    print_ship(klingons, 6);
    return 0;

    srand(time(NULL));

    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    columns = ws.ws_col; // terminal width
    rows = ws.ws_row;    // terminal height

    init_termios();

    printf("\033[?25l");     // hide cursor
    printf("\033[2J\033[H"); // clear screen

    init_stars();

    while (1) {
        update_stars();
        draw_stars();
        usleep(100000);          // 100ms
        printf("\033[2J\033[H"); // clear screen
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &original_termios);
    return 0;
}
