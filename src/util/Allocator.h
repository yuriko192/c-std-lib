//
// Created by Yuriko on 12/14/2025.
//

#ifndef CSTDLIB_ALLOCATOR_H
#define CSTDLIB_ALLOCATOR_H
#include <stddef.h>

typedef struct arena
{
    size_t Capacity;
    size_t Offset;
    void *Memory;
} Arena;

Arena* NewArena(size_t capacity);
void* Allocate(Arena* arena, size_t size);
void FreeArena(Arena* arena);

#endif //CSTDLIB_ALLOCATOR_H