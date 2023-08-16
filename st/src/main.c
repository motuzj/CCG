#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>

#include "main.h"
#include "spaceships.h"
#include "stars.h"

int columns = 80;
int rows = 25;
int warp_factor = 1; // 0 (min) - 10 (max)

int print_ship(Spaceship spaceship) {
    for (int i = 0; i < spaceship.texture_lines; i++) {
        printf("\033[%d;%dH", spaceship.row + i, spaceship.column);
        printf("%s\n", spaceship.texture[i]);
    }
    return 0;
}

int set_ship_texture(Spaceship *spaceship, char texture[][50]) {
    for (int i = 0; i < spaceship->texture_lines; i++) {
        strncpy(spaceship->texture[i], texture[i], sizeof(spaceship->texture[i]));
    }
    return 0;
}

int main() {
    srand(time(NULL));

    struct winsize ws;
    ioctl(0, TIOCGWINSZ, &ws);
    columns = ws.ws_col;  // terminal width
    rows = ws.ws_row + 1; // terminal height

    enable_raw_mode();

    printf("\033[?25l");     // hide cursor
    printf("\033[2J\033[H"); // clear screen

    init_stars();

    Spaceship enterprise = {
        .name = "USS Enterprise",
        .is_enemy = false,
        .texture = enterprise_basic,
        .texture_lines = 5,
        .shields = 1000,
        .column = 2,
        .row = (rows / 2) - 2};
    set_ship_texture(&enterprise, enterprise_basic);

    while (1) {
        for (int i = 0; i < warp_factor; i++) {
            update_stars();
        }
        draw_stars();
        print_ship(enterprise);
        int input = get_input();
        if (input > 0) {
            process_input(&enterprise, input);
        } else if (input == -1) {
            return 1;
        }
        printf("\033[2J\033[H"); // clear screen
    }
    return 0;
}
