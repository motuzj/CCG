#include <stdio.h>

int welcome_message() {
    // game name
    char ascii_name[300] = "  SSSS   NN  NN   AAAA   KK  KK  EEEEEE   SSSS  \n SS      NNN NN  AA  AA  KK KK   EE      SS     \n  SSSS   NN NNN  AAAAAA  KKKK    EEEE     SSSS  \n     SS  NN  NN  AA  AA  KK KK   EE          SS \n  SSSS   NN  NN  AA  AA  KK  KK  EEEEEE   SSSS";
    printf("\033[32m%s\033[0m\n\n", ascii_name);

    printf("\033[4mVISUALS\033[0m\n\n");
    printf("Player 1\t\033[32moooooooooO\033[0m\n"); // Player 1        oooooooooO
    printf("Player 2\t\033[92moooooooooO\033[0m\n"); // Player 2        oooooooooO
    printf("Fruits\t\t\033[41mX\033[0m\n");          // Fruits          X
    printf("Wall\t\t#\n\n");                         // Wall            #

    printf("\033[4mDEFAULT CONTROLS\033[0m\n\n");
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

    printf("q\tQuit game\n\n\n");

    printf("\033[4mLAUNCH OPTIONS\033[0m\n\n");
    printf("  -b\tDisable borders\n\n");

    printf("Press [ENTER] to continue. ");
    getchar();

    return 0;
}
