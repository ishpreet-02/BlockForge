CC = gcc

CFLAGS = -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=200809L -Iinclude

TARGET = blockforge

SOURCES = src/main.c \
          src/game.c \
          src/board.c \
          src/piece.c \
          src/input.c \
          src/collision.c \
          src/score.c

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)