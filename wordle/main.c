#include <stdio.h>
#include <string.h>

//
// SOME LETTERS HAVE WRONG COLOR
//

#define WORD_LENGTH 5

int main(void) {
	char *wordle = "apple";
	while(1) {
		char guess[WORD_LENGTH + 1];
		
		printf("Guess: ");
		scanf ("%5s", guess);
		if (strlen(guess) != WORD_LENGTH) {
			printf("Incorect guess size.\n");
			continue;
		}

		if (!strcmp(wordle, guess)) {
			printf("You have won!\n");
			break;
		}

		for (int i = 0; i < strlen(guess); i++) { 
			if (guess[i] == wordle[i]) {
				printf("\e[0;32m%c\e[0m", guess[i]);
				continue;
			}

			int worlde_same_letters = 0;
			for (int j = 0; j < strlen(wordle); j++) {
				if (guess[i] == wordle[j]) {
					worlde_same_letters++;
				}
			}

			char letters_before[WORD_LENGTH];
			strncpy(letters_before, guess, i);

			int guess_same_letters = 0;
			for (int j = 0; j < i; j++) {
				if (guess[i] == letters_before[j]) {
					guess_same_letters++;
				}
			}

			if (guess_same_letters < worlde_same_letters && strchr(wordle, guess[i]) != NULL) {
				printf("\e[0;33m%c\e[0m", guess[i]);
			} else {
				printf("%c", guess[i]);
			}
		}
		printf("\n");
	}
	return 0;
}
