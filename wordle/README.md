# Wordle

![Screenshot_20230608_001141_2](https://github.com/motuzj/CCG/assets/30744041/bdf1e394-4026-4e9e-8c16-81c2556b4637)

## How to play

Wordle is a word-guessing game where you try to guess a five-letter word.

Read more on [Wikipedia](https://en.wikipedia.org/wiki/Wordle).

## Options

- `-d <dictionary-path>`: Specify the path to a custom dictionary file.
- `-e`: Enable endless guesses mode.
- `-k`: Disable keyboard display.
- `-h`: Display help message.

## Dictionaries

The game uses a dictionary file to validate the words entered by the player. By default, the game uses the "dict/english.txt" file as the dictionary. You can specify a different dictionary file using the -d option.

## Building

### For Unix-based systems

The easiest way to build the game is with `make`. To get started, follow the instructions [here](../README.md#building). Note that while the game has not been tested on macOS, it should work in theory.
