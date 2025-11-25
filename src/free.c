#include <stdio.h>
#include <stdlib.h>
#include "../include/allocator.h"

void arena_free(void *ptr) {
    if (ptr == NULL) return;
    block_t *block = (block_t*)ptr - 1;
    if (block->is_free) {
        fprintf(stderr, "Error: Double-free detected\n");
        return;
    }
    block->is_free = 1;
    coalesce_blocks(block);
}

void coalesce_blocks(block_t *block) {
    if (block == NULL) return;
    if (block->next != NULL && block->next->is_free) {
        block->size += sizeof(block_t) + block->next->size;
        if (block->next->next != NULL) block->next->next->prev = block;
        block->next = block->next->next;
    }
    if (block->prev != NULL && block->prev->is_free) {
        block->prev->size += sizeof(block_t) + block->size;
        if (block->next != NULL) block->next->prev = block->prev;
        block->prev->next = block->next;
    }
}
