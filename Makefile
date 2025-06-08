CC=gcc
CFLAGS=-Wall -Wextra -Iinclude
LDFLAGS=-lncurses -lpulse-simple -lpulse

SRCS=main.c sound/audio.c ui/ui.c
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

build:
	mkdir -p build

clean:
	rm -rf build
	rm -f $(BIN)
