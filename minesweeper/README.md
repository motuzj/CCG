# WORK IS IN PROGRESS AND THE GAME IS CURRENTLY NOT FULLY FUNCTIONAL!

# Minesweeper

![screenshot01](https://user-images.githubusercontent.com/30744041/229316560-4a941874-4b31-4b40-90bd-7ffecbf83c1d.jpg)

## Controls

The game uses a case-sensitive command processing system. To see the available commands, type `help` or `h`.

## Building

### For Unix-based systems

The easiest way to build the game is with `make`. To get started, follow the instructions [here](../README.md#building). Note that while the game has not been tested on macOS, it should work in theory.

## [TODO](./TODO.md)

## Help

You can type `help` to show message like this:

```
USAGE: <command> <x> <y>

COMMANDS:
  guess <x> <y> Reveals the cell at the specified coordinates.
  mark <x> <y>  Marks a cell at the specified coordinates as a potential mine.
  status or s   View status of the game.
  restart or r  Stops a game and starts a new one.
  quit or exit  Quits the game.
  help or h     Displays this message.

NOTES:
  To use a command, simply type the command name followed by any required arguments. For example, to guess the cell at x (column) 3, y (row) 4, type "guess 3 4" and press enter.
  Note that all commands are case sensitive.
  You can also use one word abbreviations as: g (guess), m (mark)...
```
