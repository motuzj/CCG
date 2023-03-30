#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#include "commands.h"
#include "draw.h"
#include "game.h"

int w = 15;                     // board width / max x coords
int h = 15;                     // board height / max y coords
double minesPercentage = 0.13;  // percentage of mines
int mines;
int playing = 1;                // 1 - playing ; 0 - game over
int firstGuess = 1;             // 1 - first game ; 0 - not first game

int **board;

int generate_board(int guessX, int guessY, int w, int h) {
  srand(time(NULL));

  // check if minesPercentage is in valid format
  if (minesPercentage < 0.0 || minesPercentage > 1.0) {
    printf("Warning: Percentage of mines is not valid percetage number, setting it to 13%%.");
    minesPercentage = 0.13;
  }

  // calculate number of mines to place
  mines = (int) w * h * minesPercentage;
  if (mines > (w * h)) {
    mines = w * h - 9;
  }

  // placing mines
  while (mines) {
    int x = rand() % w;
    int y = rand() % h;

    // checks if neighbor is guess
    bool hasGuessNeighbor = false;
    for (int i = x - 1; i <= x + 1 && i >= 0 && i < w; i++) {
      for (int j = y - 1; j <= y + 1 && j >= 0 && j < h; j++) {
        if (j == guessX && i == guessY) {
          hasGuessNeighbor = true;
        }
      }
    }

    if (board[y][x] != 2 && !(x == guessX && y == guessY) && !hasGuessNeighbor) {
      board[y][x] = 2;
      mines--;
    }
  }
  return 0;
}

int reveal_empty_cells(int x, int y) {
  // detect if cell was revealed or is out of board
  if (x < 0 || x >= w || y < 0 || y >= h || board[y][x] != 1) {
    return 0;
  }
  board[y][x] = 0;

  if (count_mines(board, y, x, w, h) > 0) {
    return 0;
  }

  // test for all empty cells
  for (int i = x - 1; i <= x + 1; i++) {
    for (int j = y - 1; j <= y + 1; j++) {
      if (i == x && j == y)
        continue;               // skip the current cell
      reveal_empty_cells(i, j); // reveal the neighboring cell
    }
  }

  return 0;
}

int count_mines(int **board, int x, int y, int w, int h) {
  int minesCounter = 0;

  for (int k = x - 1; k <= x + 1; k++) {
    for (int l = y - 1; l <= y + 1; l++) {
      // Skip out-of-bounds cells
      if (k < 0 || k >= h || l < 0 || l >= w) {
        continue;
      }
      // Check if the cell has a mine
      if (board[k][l] == 2 || board[k][l] == 4 || board[k][l] == 6 ||
          board[k][l] == 7) {
        minesCounter++;
      }
    }
  }

  return minesCounter;
}

int set_board_size() {
  char input[10];
  char *endptr;

  while (1) {
    printf("Width: ");
    // write stdin to input
    fgets(input, sizeof(input), stdin);
    // remove \n newline character from `input`
    input[strcspn(input, "\n")] = 0;

    // convert string to int
    w = strtol(input, &endptr, 10);
    if (*endptr != '\0' || w < 2 || w > 99) {
      printf("Make sure the size is valid number from 2 to 99!\n");
      continue;
    }
    break;
  }
  while (1) {
    printf("Height: ");
    // write stdin to input
    fgets(input, sizeof(input), stdin);
    // remove \n newline character from `input`
    input[strcspn(input, "\n")] = 0;

    // convert string to int
    h = strtol(input, &endptr, 10);
    if (*endptr != '\0' || h < 2 || h > 99) {
      printf("Make sure the size is valid number from 2 to 99!\n");
      continue;
    }
    break;
  }
  return 0;
}

int initialize_board() {
  set_board_size();

  // initiation of board
  board = (int **)calloc(h, sizeof(int *));
  if (board == NULL) {
    printf("\nNot enough memory to allocate.\nExiting...\n");
    return 1;
  }
  for (int i = 0; i < h; i++) {
    board[i] = (int *)calloc(w, sizeof(int));
  }
  if (board == NULL) {
    printf("\nNot enough memory to allocate.\nExiting...\n");
    return 1;
  }

  // set all numbers in board to 1 (unrevealed, without mines)
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      board[i][j] = 1;
    }
  }
  return 0;
}



int run_game() {
  initialize_board();

  // main loop
  while (playing) {
    draw(w, h, board);
    process_command();

    // checks if there are any remaining mines
    int markedMines = 0;
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (board[i][j] == 4) {
          markedMines++;
        }
      }
    }
    mines = (int) w * h * minesPercentage;
    if (markedMines >= mines) {
      playing = 0;
      printf("You've won!!");
    }

    // when 
    if (!playing) {
      char answer;
      printf("\nDo you want to play again? (Y/n) ");
      scanf("%c", &answer);
      if (answer == 'y' || answer == 'Y' || answer == '\n') {
        playing = 1;
        firstGuess = 1;
        initialize_board();
      } else if (answer == 'n' || answer == 'N') {
        printf("Bye!\n");
      }
    }
  }

  // freeing board
  for (int i = 0; i < h; i++) {
    free(board[i]);
  }
  free(board);

  printf("\n");
  return 0;
}
