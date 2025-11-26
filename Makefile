CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g -Iinclude -I/opt/homebrew/include
LIBS = -L/opt/homebrew/lib -lcunit

SOURCES = src/arena_malloc.c src/free.c src/realloc.c src/calloc.c src/utils.c

# Тести
TEST_FREE = tests/test_free.c
TEST_CALLOC = tests/test_calloc.c
TEST_REALLOC = tests/test_realloc.c
TEST_MALLOC = tests/malloc_test.c

# Бінарники
TEST_FREE_BIN = test_free
TEST_CALLOC_BIN = test_calloc
TEST_REALLOC_BIN = test_realloc
TEST_MALLOC_BIN = test_malloc

all: $(TEST_FREE_BIN) $(TEST_CALLOC_BIN) $(TEST_REALLOC_BIN) $(TEST_MALLOC_BIN)

$(TEST_FREE_BIN): $(SOURCES) $(TEST_FREE)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(TEST_FREE) $(LIBS)

$(TEST_CALLOC_BIN): $(SOURCES) $(TEST_CALLOC)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(TEST_CALLOC) $(LIBS)

$(TEST_REALLOC_BIN): $(SOURCES) $(TEST_REALLOC)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(TEST_REALLOC) $(LIBS)

$(TEST_MALLOC_BIN): $(SOURCES) $(TEST_MALLOC)
	$(CC) $(CFLAGS) -o $@ $(SOURCES) $(TEST_MALLOC) $(LIBS)

run:
	./$(TEST_FREE_BIN)
	./$(TEST_CALLOC_BIN)
	./$(TEST_REALLOC_BIN)
	./$(TEST_MALLOC_BIN)

clean:
	rm -f $(TEST_FREE_BIN) $(TEST_CALLOC_BIN) $(TEST_REALLOC_BIN) $(TEST_MALLOC_BIN) *.o *.out

.PHONY: all run clean
