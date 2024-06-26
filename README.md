# CCG
![Logo](./_assets/logo.png)

This is my collection of **CLI C Games**. Currently [minesweeper](./minesweeper/README.md), [wordle](./wordle/README.md), [2048](./2048/README.md), [snakes](./snakes/README.md) and [trivia](./trivia/README.md) games are available.

## Building

You can compile it with `make` and c compiler (tested on GCC and clang), so make sure you have them installed on your system before building it.

For example, on Debian/Ubuntu based systems you can install them using:

```bash
sudo apt update && sudo apt install gcc make
```

The building process of any game is pretty much the same ([with the exception of trivia game](./trivia/README.md#building)):

```bash
git clone https://github.com/motuzj/CCG.git
cd CCG
cd {game-name}
make
./{game-name}
```

or you can use `make run` to build and run immediately.
