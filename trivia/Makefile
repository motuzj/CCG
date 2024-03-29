NAME=trivia

main:
	cc -o $(NAME) ./src/*.c ./src/extern/b64.c/*.c ./src/extern/cJSON/*.c -lcurl

run: main
	./$(NAME)
