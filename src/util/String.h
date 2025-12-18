//
// Created by Yuriko on 12/14/2025.
//

#ifndef CSTDLIB_STRING_H
#define CSTDLIB_STRING_H
#include <stddef.h>

#include "String.h"

typedef struct string_imp {
    char *Data;
    size_t Size;
} String;

String *NewString(const char *data, size_t size);

String *StringSlice(String *inpStr, size_t start, size_t end);

char StringGet(String *str, size_t index);

int StringCopy(String *inpStr, String *outStr);

int FreeString(String *str);

#endif //CSTDLIB_STRING_H
