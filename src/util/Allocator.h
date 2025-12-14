//
// Created by Yuriko on 12/14/2025.
//

#ifndef CSTDLIB_ALLOCATOR_H
#define CSTDLIB_ALLOCATOR_H
#include "String.h"

typedef struct arena
{
    size_t Capacity;
    size_t Offset;
    void *Memory;
} Arena;

#endif //CSTDLIB_ALLOCATOR_H