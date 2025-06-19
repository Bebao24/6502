CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c11

C_SOURCES := $(shell find src -name "*.c")
C_OBJECTS := $(patsubst src/%.c, build/objects/%.o, $(C_SOURCES))

C_HEADERS := $(shell find src -name "*.h")

.PHONY: all emulator clean programs

all: emulator programs

emulator: build/emulator
build/emulator: $(C_OBJECTS)
	$(CC) -o $@ $^

build/objects/%.o: src/%.c Makefile $(C_HEADERS)
	@ mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

programs: programs/test.out
programs/test.out: programs/test.asm
	vasm6502_oldstyle -Fbin -dotdir $< -o $@

clean:
	rm -rf build

