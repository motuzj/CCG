# WORK IS IN PROGRESS AND THE GAME IS CURRENTLY NOT FULLY FUNCTIONAL!

# Minesweeper

![screenshot01](https://user-images.githubusercontent.com/30744041/224798463-c7e78d9d-e6f0-4a79-9809-282612bcb56f.jpeg)

## Controls

The game uses a case-sensitive command processing system. To see the available commands, type `help` or `h`.

## Building

### For Unix-based systems

The easiest way to build the game is with `make`. To get started, follow the instructions [here](../README.md#building). Note that while the game has not been tested on macOS, it should work in theory.

### For Windows

While there is no guaranteed way to build the game on Windows, you can try using the [TCC](https://bellard.org/tcc/) compiler. Keep in mind that proper UNICODE support may be lacking. To build and run the game, enter the following commands:


```
.\tcc.exe -o minesweeper.exe main.c gane.c commands.c draw.c
.\minesweeper.exe
```

## [TODO](./TODO.md)

## Help

You can type `help` to show message like this:

```
USAGE: <command> <x> <y>

COMMANDS:
  guess <x> <y> Reveals the cell at the specified coordinates.
  mark <x> <y>  Marks a cell at the specified coordinates as a potential mine.
  unmark <x><y> Unmarks a cell at the specified coordinates as a mine.
  restart or r  Stops a game and starts a new one.
  quit or exit  Quits the game.

NOTES:
  To use a command, simply type the command name followed by any required arguments. For example, to guess the cell at x (column) 3, y (row) 4, type "guess 3 4" and press enter.
  Note that all commands are case sensitive.
  You can also use one word abbreviations as: g (guess), m (mark)...
```
