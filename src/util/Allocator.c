//
// Created by Yuriko on 12/14/2025.
//

#include "allocator.h"

#include <stdlib.h>


Arena NewArena(size_t capacity)
{
    return (Arena){
        .Capacity = capacity,
        .Offset = 0,
        .Memory = malloc(capacity)
    };
}

void* Allocate(Arena* arena, size_t size)
{
    if (arena->Capacity - arena->Offset < size) {
        return NULL;
    }

    void* ptr = arena->Memory + arena->Offset;
    arena->Offset += size;
    return ptr;
}

void FreeArena(Arena arena)
{
    free(arena.Memory);
}


