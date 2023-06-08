# CCG
![Logo](./assets/logo.png)

This is my collection of **CLI C Games**. Currently [minesweeper](./minesweeper/README.md) and [wordle](./wordle/README.md) games are available. 

## Building

You can compile it with `make` and `gcc`, so make sure you have them installed on your system before building it.

For example, on Debian/Ubuntu based systems you can install them using:

```bash
sudo apt update && sudo apt install gcc make
```

The building of any game probably will be pretty much the same:

```bash
git clone https://github.com/motuzj/CCG.git
cd CCG
cd {game-name}
make
./{game-name}
```

or you can use `make run` to build and run the game and `make clean` to remove the build files.  
You can also build games using `clang`, just change the first line in the `Makefile` to `CC = clang`.
