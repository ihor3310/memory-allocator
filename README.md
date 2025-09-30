# Memory Allocator Project

## Team Members
- **Member Ihor Mykhnian** — responsible for `malloc()` implementation, testing.
- **Member Mykola Chervinchuk** — responsible for `free()` implementation, testing.
- **Member Yuriy Verbivskiy** — responsible for `realloc()` and `calloc()` implementation, testing.

## Project Name
**Memory Allocator / Heap**

## Short Description
This project implements a **memory allocator** in C that mimics the functionality of standard library functions `malloc`, `free`, `realloc`, and `calloc`. 

The allocator uses a **linked-list heap structure** to manage memory blocks and includes:
- Dynamic memory allocation (`malloc`) with block splitting and alignment.
- Memory deallocation (`free`) with coalescing and double-free protection.
- Memory resizing (`realloc`) and zero-initialized allocation (`calloc`).
