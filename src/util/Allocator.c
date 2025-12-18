//
// Created by Yuriko on 12/14/2025.
//

#include "Allocator.h"

#include <stdlib.h>


Arena NewArena(size_t capacity)
{
    if (capacity == 0)
    {
        return (Arena){
            .Capacity = 0,
            .Offset = 0,
            .Memory = NULL
        };
    }

    void* memory = malloc(capacity);
    // ReSharper disable once CppDFAMemoryLeak
    return (Arena){
        .Capacity = capacity,
        .Offset = 0,
        .Memory = memory
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
