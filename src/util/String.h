//
// Created by Yuriko on 12/14/2025.
//

#ifndef CSTDLIB_STRING_H
#define CSTDLIB_STRING_H
#include <stddef.h>

typedef struct string_imp {
    char *Data;
    size_t Size;
    size_t Capacity;
} String;

String *NewStringFromChar(const char *data, size_t size);

String *NewStringWithCapacity(size_t capacity);

String *StringSlice(String *inpStr, size_t start, size_t end);

char StringGet(String *str, size_t index);

int StringCopy(String *inpStr, String *outStr);

int StringCopyFromCharPtr(String *outStr, const char *src, size_t size);

int FreeString(String *str);

#endif //CSTDLIB_STRING_H
