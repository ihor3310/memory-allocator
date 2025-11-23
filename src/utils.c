#include "allocator.h"

void split_block(block_t *block, size_t size) {
    size_t min_block_size = sizeof(block_t) + 8;

    if (block->size >= size + min_block_size) {
        
        block_t *new_block = (block_t*)((char*)block + sizeof(block_t) + size);
        
        new_block->size = block->size - size - sizeof(block_t);
        new_block->is_free = 1;
        new_block->next = block->next;
        new_block->prev = block;

        block->size = size;
        block->next = new_block;

        if (new_block->next != NULL) {
            new_block->next->prev = new_block;
        }

        coalesce_blocks(new_block);
    }
}