CC = gcc
SRC = src/*.c
OUT = bin/ircbot
FLAGS = -Wall -Wextra -Wshadow 

all:
	mkdir bin
	$(CC) $(SRC) -o $(OUT) $(FLAGS)
rebuild:
	$(CC) $(SRC) -o $(OUT) $(FLAGS)
debug:
	mkdir bin
	$(CC) $(SRC) -o $(OUT) $(FLAGS) -g
clean:
	rm -rf bin
