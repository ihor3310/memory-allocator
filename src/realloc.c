#include <string.h>
#include "allocator.h"

void* arena_realloc(void *ptr, size_t size) {
    if (ptr == NULL) {
        return arena_malloc(size);
    }

    if (size == 0) {
        arena_free(ptr);
        return NULL;
    }

    block_t *block = (block_t*)ptr - 1;

    if (block->size >= size) {
        split_block(block, size);
        return ptr;
    }

    void *new_ptr = arena_malloc(size);
    if (!new_ptr) {
        return NULL;
    }

    memcpy(new_ptr, ptr, block->size);
    arena_free(ptr);

    return new_ptr;
}
