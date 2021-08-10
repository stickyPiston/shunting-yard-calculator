SRCS := src/main.c src/parse.c src/lex.c src/vector.c src/evaluate.c src/error.c
FLGS := -Wall -Wextra -Wpedantic -Werror -Iinclude -g -lm
CC   := clang

all:
	mkdir -p bin
	$(CC) $(SRCS) -o bin/out $(FLGS)
