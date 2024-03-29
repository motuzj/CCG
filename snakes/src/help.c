#include <stdio.h>

int welcome_message() {
    printf("\033[4mVISUALS\033[0m\n");
    printf("Player 1\t\033[32moooooooooO\033[0m\n"); // Player 1        oooooooooO
    printf("Player 2\t\033[92moooooooooO\033[0m\n"); // Player 2        oooooooooO
    printf("Fruits\t\t\033[41mX\033[0m\n");          // Fruits          X
    printf("Wall\t\t#\n\n");                         // Wall            #

    printf("\033[4mDEFAULT CONTROLS\033[0m\n");
    printf("Player movement (case sensitive):\n\n");

    printf("\t\t^\n");
    printf("\t\tw\n");
    printf("Player 1    < a   d >\n");
    printf("\t\ts\n");
    printf("\t\tv\n\n");

    printf("\t\t^\n");
    printf("\t\ti\n");
    printf("Player 2    < j   l >\n");
    printf("\t\tk\n");
    printf("\t\tv\n\n");

    printf("q\tQuit game\n\n");

    printf("Press [ENTER] to continue. ");
    getchar();

    return 0;
}

int display_help() {
    printf("usage: snakes [-h] [-b] [-s]\n\n");
    printf("Snake game implementation in C for one or two players.\n\n");
    printf("options:\n");
    printf("  -h\t\tshow this help message and exit\n");
    printf("  -b\t\tdisable borders\n");
    printf("  -s [SPEED]\tspeed of a player, 1 (max) - 10 (min), default 5\n");

    return 0;
}
