#include <string.h>
#include <stdint.h>
#include "allocator.h"

void* arena_calloc(size_t nmemb, size_t size) {
    if (nmemb == 0 || size == 0) {
        return NULL;
    }

    size_t total_size = nmemb * size;

    if (nmemb != 0 && total_size / nmemb != size) {
        return NULL;
    }

    void *ptr = arena_malloc(total_size);

    if (ptr != NULL) {
        memset(ptr, 0, total_size);
    }

    return ptr;
}