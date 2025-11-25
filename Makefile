CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Iinclude -I/opt/homebrew/include
LIBS = -L/opt/homebrew/lib -lcunit

SOURCES = src/malloc.c src/free.c src/realloc.c src/calloc.c src/utils.c
TEST_FREE = tests/test_free.c
TEST_FREE_BIN = test_free

all: $(TEST_FREE_BIN)

$(TEST_FREE_BIN): $(SOURCES) $(TEST_FREE)
	$(CC) $(CFLAGS) -o $(TEST_FREE_BIN) $(SOURCES) $(TEST_FREE) $(LIBS)

run: $(TEST_FREE_BIN)
	./$(TEST_FREE_BIN)

clean:
	rm -f $(TEST_FREE_BIN) *.o *.out

.PHONY: all run clean
