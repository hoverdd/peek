CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude

SRC = $(filter-out src/main.c, $(wildcard src/*.c))
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))

MAIN_SRC = src/main.c
MAIN_OBJ = $(patsubst src/%.c, build/%.o, $(MAIN_SRC))

# tests
TESTS_SRC = $(wildcard tests/*.c)
TESTS_OBJ = $(patsubst tests/%.c, build/tests/%.o, $(TESTS_SRC))

CHECK_CFLAGS = $(shell pkg-config --cflags check)
CHECK_LIBS   = $(shell pkg-config --libs check)

PROGRAM_NAME = peek


all: $(PROGRAM_NAME)

# regular program
$(PROGRAM_NAME): $(OBJ) $(MAIN_OBJ)
	$(CC) $(CFLAGS) $^ -o $@

build/%.o: src/%.c | build # build src/
	$(CC) $(CFLAGS) -c $< -o $@

build/tests/%.o: tests/%.c | build/tests # build tests/
	$(CC) $(CFLAGS) $(CHECK_CFLAGS) $(CHECK_LIBS) -c $< -o $@

build: 
	mkdir -p build

build/tests:
	mkdir -p build/tests

test_runner: $(OBJ) $(TESTS_OBJ)
	$(CC) $(CFLAGS) $(CHECK_CFLAGS) $(CHECK_LIBS) $^ -o $@

test: test_runner
	./test_runner

install: all
	cp $(PROGRAM_NAME) /usr/local/bin

uninstall:
	rm -f /usr/local/bin/$(PROGRAM_NAME)

clean:
	rm -rf build $(PROGRAM_NAME) test_runner