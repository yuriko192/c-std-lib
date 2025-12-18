//
// Created by Yuriko on 12/14/2025.
//

#include "String.h"

#include <stdlib.h>
#include <string.h>

String* NewString(const char* data, size_t size)
{
    String* str = malloc(sizeof(String));
    if (str == NULL)
    {
        return NULL;
    }

    if (data == NULL || size == 0)
    {
        str->Size = 0;
        str->Data = NULL;
        return str;
    }

    str->Data = malloc(size + 1);
    if (str->Data == NULL)
    {
        free(str);
        return NULL;
    }

    memcpy(str->Data, data, size);
    str->Data[size] = '\0';
    str->Size = size;
    return str;
}

String* StringSlice(String* inpStr, size_t start, size_t end)
{
    if (inpStr == NULL || inpStr->Data == NULL)
    {
        return NULL;
    }
    if (start > end || end > inpStr->Size)
    {
        return NULL;
    }

    String* str = NewString(inpStr->Data + start, end - start);
    return str;
}

char StringGet(String* str, size_t idx)
{
    if (str == NULL || str->Data == NULL || idx >= str->Size)
    {
        return 0;
    }

    return str->Data[idx];
}

int StringCopy(String* inpStr, String* outStr)
{
    if (inpStr == NULL || outStr == NULL
        || inpStr->Data == NULL || outStr->Data == NULL)
    {
        return -1;
    }

    if (inpStr->Size == 0)
    {
        outStr->Size = 0;
        return 0;
    }

    for (int i = 0; i < inpStr->Size; ++i)
    {
        outStr->Data[i] = StringGet(inpStr, i);
    }
    outStr->Size = inpStr->Size;
    return 0;
}

int StringCopyFromCharPtr(String* outStr, const char* src, size_t size)
{
    if (outStr == NULL || src == NULL)
    {
        return -1;
    }

    if (outStr->Data == NULL)
    {
        outStr->Data = malloc(size + 1);
        if (outStr->Data == NULL)
        {
            return -1;
        }
    }

    if (size != 0)
    {
        memcpy(outStr->Data, src, size);
    }

    outStr->Data[size] = '\0';
    outStr->Size = size;
    return 0;
}

int FreeString(String* str)
{
    if (str == NULL)
    {
        return -1;
    }
    free(str->Data);
    str->Data = NULL;
    str->Size = 0;
    return 0;
}
