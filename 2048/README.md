# 2048

![Screenshot_20230613_193500](https://github.com/motuzj/CCG/assets/30744041/e1c07642-8426-49f2-a416-ca9326bf7539)

## How to play

2048 is game where you goal is to reach a 2048 tile/cell. You can do that by moving and merging cells with a same values together.

To move tiles to different directions use arrow keys, w/a/s/d or h/j/k/l.

Read more on [Wikipedia](https://en.wikipedia.org/wiki/2048_(video_game)).

## Options

- `-s <side-length>`: Lenght of the sides of the game board (must be bigger than 1).
- `-e`: Enable endless mode - the game doesn't end at 2048.
- `-m`: Minimalist mode - hide side informations (score, game name).

## Building

### For Unix-based systems

The easiest way to build the game is with `make`. To get started, follow the instructions [here](../README.md#building). Note that while the game has not been tested on macOS, it should work in theory.
