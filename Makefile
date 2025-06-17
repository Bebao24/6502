CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11

C_SOURCES := $(shell find src -name "*.c")
C_OBJECTS := $(patsubst src/%.c, build/objects/%.o, $(C_SOURCES))

C_HEADERS := $(shell find src -name "*.h")

.PHONY: all emulator clean

all: emulator

emulator: build/emulator
build/emulator: $(C_OBJECTS)
	$(CC) -o $@ $^

build/objects/%.o: src/%.c Makefile
	@ mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf build

