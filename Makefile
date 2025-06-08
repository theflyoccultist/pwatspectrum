CC=gcc
CFLAGS=-Wall -Wextra -Iinclude
LDFLAGS=-lncurses -lpulse-simple -lpulse

SRCS=main.c sound/audio.c ui/ui.c
OBJ=$(SRCS:.c=.o)
BIN=audio_visualizer


$(BIN): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ) $(LDFLAGS)

clean:
	rm -f $(OBJ) $(BIN)
