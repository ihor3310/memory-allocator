## How to setup

```
brew install gcc make cunit
git clone https://github.com/ihor3310/memory-allocator
cd memory-allocator
```
### Compile and run tests

```
make run
```

### Test leaks

```
leaks -atExit -- ./file.c
```


# Diagram
```
┌──────────────────────────────────────────────────────────┐
│                  LAYER 1: INTERFACE                      │
│           include/allocator.h (Public API)               │
│  (Defines: arena_malloc, arena_free, arena_init...)      │
└────────────────────────────┬─────────────────────────────┘
                             │
                             ▼
┌──────────────────────────────────────────────────────────┐
│                LAYER 2: IMPLEMENTATION                   │
│           src/ (Core Logic & Algorithms)                 │
│  • malloc.c (First Fit)    • free.c (Coalescing)         │
│  • utils.c (Split Block)   • realloc.c / calloc.c        │
└────────────────────────────┬─────────────────────────────┘
                             │
                             ▼
┌──────────────────────────────────────────────────────────┐
│               LAYER 3: METADATA / STATE                  │
│           struct block_t (Internal Data Structure)       │
│  (Fields: size, is_free, next, prev pointers)            │
└────────────────────────────┬─────────────────────────────┘
                             │
                             ▼
┌──────────────────────────────────────────────────────────┐
│                  LAYER 4: EXTERNAL                       │
│  • OS Kernel: sbrk() / mmap() (System Calls)             │
│  • Verification: tests/ (CUnit / Valgrind)               │
└──────────────────────────────────────────────────────────┘
```
### Functions description
```
arena_malloc:
Allocates memory by either finding a suitable free block in the list or requesting a new page from the OS.

arena_free:
Frees a block and automatically merges it with neighboring free blocks to reduce fragmentation.

arena_calloc:
Allocates memory for an array and guarantees that it is initialized to zero.

arena_realloc:
Resizes a block; if expanding in place is not possible, it moves the data to a new block.

split_block:
Splits a large free block into two: one part is used for the allocation, and the remaining part stays free.

coalesce_blocks:
Merges a freed block with its neighboring blocks (previous and next) into a single larger free space.

find_free_block:
Iterates through the list to find the first block that is large enough.
```

### Key implementation details

```
Data Structure:
A doubly linked list that tracks all memory blocks directly inside the arena (the pre-allocated heap region obtained via mmap).

Metadata (block_t):
Each block contains a header with:

size — the size of the data region;

is_free — allocation status;

next / prev — pointers to neighboring blocks.

Optimization Techniques:

Splitting:
Helps preserve memory by cutting off unused space from a large free block and forming a new smaller free block.

Coalescing:
Reduces fragmentation by merging adjacent free blocks immediately when free is called.
```
