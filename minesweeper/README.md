# Minesweeper

![screenshot01](https://user-images.githubusercontent.com/30744041/230983647-76ded59f-91eb-4af3-a0a6-c3b2b24fc5c5.png)

## Controls

Use the arrow keys to move the cursor around the game board. Press `g` to guess and `f` to flag a mine. For a complete list of available controls, press `?` or `h`.

## Options

- `-s <seed>`: Set a speciffic seed. See [Seed](#seed) section for more details.
- `-m`: Minimalist mode - hide all text messages, errors, warnings, status and display only board.
- `-w`: Set board width.
- `-h`: Set board height.

## Seed

Seed consist of following parts:

Example of seed: `10x10n13c7x12#648B1415`

* `10x10`: width and height.
* `n13`: number of mines.
* `c7x12`: cursor coordinates (x, y).
* `648B1415`: random hexadecimal number used to generate board.

To obtain the seed during gameplay, press s.

## Building

### For Unix-based systems

The easiest way to build the game is with `make`. To get started, follow the instructions [here](../README.md#building). Note that while the game has not been tested on macOS, it should theoretically work.

## Help

You can press `?` to show message like this:

```
CONTROLS:
  Arrow keys            Move the cursor around
  Space, Enter, g       Reveal a cell
  f, m                  Flag a cell as mine
  s                     View status of the game and game seed
  r                     Stops a game and starts a new one
  q                     Quits the game
  h, ?                  Displays this message
```
