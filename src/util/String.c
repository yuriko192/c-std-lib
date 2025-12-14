//
// Created by Yuriko on 12/14/2025.
//

#include "String.h"

#include <stdlib.h>
#include <string.h>

String *NewString(char *data)
{
    String *str = malloc(sizeof(String));
    str->Data = data;
    str->Size = strlen(data);
    return str;
}

String *StringSlice(String *inpStr, size_t start, size_t end)
{
    String *str = NewString(inpStr->Data + start);
    str->Size = end - start;
    return str;
}
