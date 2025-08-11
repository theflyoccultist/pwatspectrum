CC=gcc
CFLAGS=-g -O0 -Wall -Wextra -fsanitize=address -Iinclude
LDFLAGS=-lncurses -lpulse-simple -lpulse -lfftw3 -lm

SRCS=main.c sound/audio.c ui/ui.c processing/processing.c
OBJ=$(SRCS:.c=.o)
OBJ_BUILD=$(addprefix build/,$(notdir $(OBJ)))
BIN=audio_visualizer

all: $(BIN)

$(BIN): $(OBJ_BUILD)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJ_BUILD) $(LDFLAGS)

build/%.o: %.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: sound/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: ui/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build/%.o: processing/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build
	rm -f $(BIN)
