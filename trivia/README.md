# Trivia

![Screenshot of Trivia game](https://github.com/motuzj/CCG/assets/30744041/0e70d338-f2fa-45ae-bf30-3e96c9fab48a)

Test your knowledge in an interactive Trivia game. You can choose from over 20 categories with more than 4000 questions. All questions are fetched from the [Open Trivia Database](https://opentdb.com).

## Options

- `-n <integer>`: Set the number of questions. Default is 10.
- `-c <integer>`: Set the category ID of questions, to get list of categories use option '-l'. Default is all.
- `-d <string>`: Set the difficulty of questions (easy / e, medium / m, hard / h). Default is all.
- `-t <string>`: Set the type of questions (multiple / m, boolean / b). Default is all.
- `-l`: List avaible categories.
- `-f`: Disable all escape sequences.
- `-h`: Show this help message and exit.

## Building

### Dependencies

To build this game you need to have `libcurl` installed.

On Debian/Ubuntu based systems you can install it using:

```bash
sudo apt install libcurl4-openssl-dev
```

This games also depends on libraries [b64.c](https://github.com/jwerle/b64.c) and [cJSON](https://github.com/DaveGamble/cJSON), which are already included in the source code of this game (in the extern folder). Both of these libraries are licensed under the MIT license.

### For Unix-based systems

The easiest way to build the game is with `make`. To get started, follow the instructions [here](../README.md#building). Note that while the game has not been tested on macOS, it should work in theory.
