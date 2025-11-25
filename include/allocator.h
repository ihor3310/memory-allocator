#ifndef ALLOCATOR_H
#define ALLOCATOR_H
#include <stddef.h>

typedef struct block {
    size_t size;
    int is_free;
    struct block *next;
    struct block *prev;
} block_t;

void* arena_malloc(size_t size);
void arena_free(void *ptr);
void coalesce_blocks(block_t *block);
void* arena_realloc(void *ptr, size_t size);
void* arena_calloc(size_t nmemb, size_t size);
void arena_init(void);
void arena_cleanup(void);
void split_block(block_t *block, size_t size);
block_t* find_free_block(size_t size);
block_t* request_new_block(size_t size);
void print_memory_blocks(void);

#endif
