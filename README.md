# CCG

This is my collection of CLI C Games.

## Building

You can compile it with `make` and `clang`, so make sure you have them installed on your system before building it. 

For example, on Debian/Ubuntu based systems you can install them using:
```bash
sudo apt update && sudo apt install clang make
```

The building of any game ~~is~~ probably will be pretty much the same:
```bash
git clone https://github.com/motuzj/CCG.git
cd CCG
cd {game-name}
mkdir build
make
./{game-name}.o
```
or you can use `make run` to build and run the game and `make clean` to remove the build files.
