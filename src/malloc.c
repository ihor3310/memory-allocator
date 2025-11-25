#include "../headers/malloc.h"
#include <sys/mman.h>
#include <stddef.h>
#include <stdint.h>

#define ALIGN8(x) (((x) + 7) & ~(size_t)7)

void *malloc(size_t size) {
    if (!size) return NULL;
    size = ALIGN8(size);
    void *p = mmap(NULL, size, PROT_READ | PROT_WRITE,
                   MAP_ANON | MAP_PRIVATE, -1, 0);
    if (p == (void*)-1) return NULL;
    return p;
}
