//
// Created by Yuriko on 12/14/2025.
//

#include "Allocator.h"

#include <stdlib.h>


Arena* NewArena(size_t capacity)
{
    Arena* arena = malloc(sizeof(Arena));
    if (arena == NULL)
    {
        return NULL;
    }

    if (capacity == 0)
    {
        arena->Capacity = 0;
        arena->Offset = 0;
        arena->Memory = NULL;
        return arena;
    }

    void* memory = malloc(capacity);
    if (memory == NULL)
    {
        free(arena);
        return NULL;
    }

    arena->Capacity = capacity;
    arena->Offset = 0;
    arena->Memory = memory;
    return arena;
}

void* Allocate(Arena* arena, size_t size)
{
    if (arena->Capacity - arena->Offset < size)
    {
        return NULL;
    }

    void* ptr = arena->Memory + arena->Offset;
    arena->Offset += size;
    return ptr;
}

void FreeArena(Arena* arena)
{
    if (arena == NULL)
    {
        return;
    }
    free(arena->Memory);
    free(arena);
}
