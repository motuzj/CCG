# Minesweeper

![screenshot01](https://user-images.githubusercontent.com/30744041/230983647-76ded59f-91eb-4af3-a0a6-c3b2b24fc5c5.png)

## Controls

Use the arrow keys to move the cursor around the game board. Press `SPACE` or `g` to guess and `f` to flag a mine. For a complete list of available controls, see [Help](#help).

## Options

- `-r <num>`: Set number of rows.
- `-c <num>`: Set number of columns.
- `-s <seed>`: Set a specific seed. See [Seed](#seed) section for more details.
- `-m`: Minimalist mode - hide all text messages, errors, warnings, status and display only board.
- `-n`: Disables colors.
- `-h`: Display help message.

## Seed

Seed consist of following parts:

Example of seed: `10x10n13c7x12#648B1415`

* `10x10`: Width and height.
* `n13`: Number of mines.
* `c7x12`: Cursor coordinates (x, y).
* `648B1415`: Random hexadecimal number used to generate board.

To obtain the seed during gameplay, press s.

## Building

### For Unix-based systems

The easiest way to build the game is with `make`. To get started, follow the instructions [here](../README.md#building). Note that while the game has not been tested on macOS, it should theoretically work.

## Help

You can press `?` in-game to show message like this:

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
