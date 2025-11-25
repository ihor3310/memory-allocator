#include "../headers/malloc.h"
#include <sys/mman.h>
#include <stddef.h>
#include <stdint.h>

#define ARENA_SIZE (1024*1024)
#define ALIGN8(x) (((x)+7)&~(size_t)7)

typedef struct block {
    size_t size;
    int free;
    struct block *next;
} block_t;

static void *arena = NULL;
static size_t arena_offset = 0;
static block_t *head = NULL;

static block_t *find_free_block(size_t size) {
    block_t *b = head;
    while (b) {
        if (b->free && b->size >= size) return b;
        b = b->next;
    }
    return NULL;
}

static void split_block(block_t *b, size_t size) {
    if (b->size >= size + sizeof(block_t) + 8) {
        block_t *nb = (block_t*)((char*)b + sizeof(block_t) + size);
        nb->size = b->size - size - sizeof(block_t);
        nb->free = 1;
        nb->next = b->next;
        b->next = nb;
        b->size = size;
    }
}

void *malloc(size_t size) {
    if (!size) return NULL;
    size = ALIGN8(size);

    if (!arena) {
        arena = mmap(NULL, ARENA_SIZE, PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, -1, 0);
        if (arena == (void*)-1) return NULL;
        arena_offset = 0;
        head = NULL;
    }

    block_t *b = find_free_block(size);
    if (b) {
        b->free = 0;
        split_block(b, size);
        return (char*)b + sizeof(block_t);
    }

    if (arena_offset + sizeof(block_t) + size > ARENA_SIZE) return NULL;

    b = (block_t*)((char*)arena + arena_offset);
    b->size = size;
    b->free = 0;
    b->next = NULL;
    arena_offset += sizeof(block_t) + size;

    if (!head) head = b;
    else {
        block_t *last = head;
        while (last->next) last = last->next;
        last->next = b;
    }

    return (char*)b + sizeof(block_t);
}
