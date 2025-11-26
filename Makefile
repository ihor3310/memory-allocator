CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Iinclude -I/opt/homebrew/include
LIBS = -L/opt/homebrew/lib -lcunit

SOURCES = src/arena_malloc.c src/free.c src/realloc.c src/calloc.c src/utils.c
TEST_FREE = tests/test_free.c
TEST_FREE_BIN = test_free

TEST_CALLOC = tests/test_calloc.c
TEST_CALLOC_BIN = test_calloc

TEST_REALLOC = tests/test_realloc.c
TEST_REALLOC_BIN = test_realloc

all: $(TEST_FREE_BIN)

$(TEST_FREE_BIN): $(SOURCES) $(TEST_FREE)
	$(CC) $(CFLAGS) -o $(TEST_FREE_BIN) $(SOURCES) $(TEST_FREE) $(LIBS)

$(TEST_CALLOC_BIN): $(SOURCES) $(TEST_CALLOC)
	$(CC) $(CFLAGS) -o $(TEST_CALLOC_BIN) $(SOURCES) $(TEST_CALLOC) $(LIBS)

$(TEST_REALLOC_BIN): $(SOURCES) $(TEST_REALLOC)
	$(CC) $(CFLAGS) -o $(TEST_REALLOC_BIN) $(SOURCES) $(TEST_REALLOC) $(LIBS)

run: $(TEST_FREE_BIN)
	./$(TEST_FREE_BIN)
	./$(TEST_CALLOC_BIN)
	./$(TEST_REALLOC_BIN)

clean:
	rm -f $(TEST_FREE_BIN) $(TEST_CALLOC_BIN) $(TEST_REALLOC_BIN) *.o *.out
run: $(TEST_FREE_BIN)
	./$(TEST_FREE_BIN)

clean:
	rm -f $(TEST_FREE_BIN) *.o *.out

.PHONY: all run clean
