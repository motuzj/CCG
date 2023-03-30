CC = gcc
CFLAGS = -Wall -Wextra

SRCS = commands.c draw.c game.c main.c

OBJS = $(addprefix build/, $(SRCS:.c=.o))

TARGET = minesweeper

all: build_dir $(TARGET)

run: all
	./$(TARGET)

clean:
	rm -rf build $(TARGET)

build_dir:
	mkdir -p build

build/%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@
