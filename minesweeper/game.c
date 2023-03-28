#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "commands.h"
#include "draw.h"
#include "game.h"

int w = 25;         // board width / max x coords
int h = 15;         // board height / max y coords
int playing = 1;    // 1 - playing ; 0 - game over
int firstGuess = 1; // 1 - first game ; 0 - not first game

int **board;

int generate_board(int guessX, int guessY, int w, int h) {
  srand(time(NULL));

  // calculate number of mines to place
  int mines = w * h * 0.1;
  if (mines > (w * h)) {
    mines = w * h - 9;
  }

  // placing mines
  while (mines) {
    int tempx = rand() % w;
    int tempy = rand() % h;

    //checks if neighbor is guess
    bool hasGuessNeighbor = false;
    for (int i = tempx - 1; i <= tempx + 1 && i >= 0 && i < w; i++) {
      for (int j = tempy - 1; j <= tempy + 1 && j >= 0 && j < h; j++) {
        if (j == guessX && i == guessY) {
            hasGuessNeighbor = true;
        }
      }
    }

    if (board[tempy][tempx] != 2 && !(tempx == guessX && tempy == guessY) && !hasGuessNeighbor) {
      board[tempy][tempx] = 2;
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

int run_game() {
  // check if board size is not too small or big
  if (h < 2 || w < 2) {
    printf("\nMap size is too small.\nExiting...\n");
    return 1;
  }
  if (h > 100 || w > 100) {
    printf("\nMap size is too big.\nExiting...\n");
    return 1;
  }

  // initiation of board
  board = (int **)calloc(h, sizeof(int *));
  if (board == NULL) {
    printf("\nNot enough memory to allocate.\nExiting...\n");
    return 1;
  }
  for (int i = 0; i < h; i++) {
    board[i] = (int *)calloc(w, sizeof(int));
  }

  // set all numbers in board to 1 (unrevealed, without mines)
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      board[i][j] = 1;
    }
  }

  // main loop
  while (playing) {
    draw(w, h, board);
    process_command();
  }

  // freeing board
  for (int i = 0; i < h; i++) {
    free(board[i]);
  }
  free(board);

  printf("\n");
  return 0;
}
