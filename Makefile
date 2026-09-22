CC=gcc

CFLAGS=-Iinclude

SRC=src/main.c src/game.c src/board.c

OUTPUT=blockforge


all:
	$(CC) $(SRC) $(CFLAGS) -o $(OUTPUT)


run:
	./$(OUTPUT)


clean:
	rm $(OUTPUT)