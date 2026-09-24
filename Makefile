CC=gcc

CFLAGS=-Iinclude

SRC=src/main.c src/game.c src/board.c src/piece.c

OUTPUT=blockforge


all:
	$(CC) $(SRC) $(CFLAGS) -o $(OUTPUT)


run:
	./$(OUTPUT)


clean:
	rm $(OUTPUT)