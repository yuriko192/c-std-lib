//
// Created by Yuriko on 12/14/2025.
//

#include "String.h"

#include <stdlib.h>
#include <string.h>

String* NewString(const char* data, size_t size)
{
    String* str = malloc(sizeof(String));
    if (data == NULL || size == 0)
    {
        str->Size = 0;
        str->Data = NULL;
        return str;
    }

    str->Data = malloc(size + 1);
    memcpy(str->Data, data, size);
    str->Data[size] = '\0';
    str->Size = size;
    return str;
}

String* StringSlice(String* inpStr, size_t start, size_t end)
{
    String* str = NewString(inpStr->Data + start, end - start);
    return str;
}

char StringGet(String* str, size_t idx)
{
    if (idx < str->Size)
    {
        return str->Data[idx];
    }
    return 0;
}

int StringCopy(String* inpStr, String* outStr)
{
    for (int i = 0; i < inpStr->Size; ++i)
    {
        outStr->Data[i] = StringGet(inpStr, i);
        if (outStr->Data[i] == 0)
        {
            outStr->Size = i;
            return -1;
        }
    }
    outStr->Size = inpStr->Size;
    return 0;
}

int FreeString(String* str)
{
    free(str->Data);
    return 0;
}
