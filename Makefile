CC = gcc
SRC = src/*.c
OUT = bin/ircbot.o
FLAGS = -Wall -Wextra -Wshadow 

all:
	@echo "[+] Release Mode..."
	mkdir bin
	$(CC) $(SRC) -o $(OUT) $(FLAGS)
debug:
	@echo "[#] Debug Mode..."
	mkdir bin
	$(CC) $(SRC) -o $(OUT) $(FLAGS) -g
clean:
	@echo "[i] Cleaning Up..."
	rm -rf bin
