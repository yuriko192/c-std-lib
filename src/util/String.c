//
// Created by Yuriko on 12/14/2025.
//

#include "String.h"

#include <stdlib.h>
#include <string.h>

String* NewStringWithCapacity(size_t capacity)
{
    String* str = malloc(sizeof(String));
    if (str == NULL)
    {
        return NULL;
    }

    str->Size = 0;
    str->Capacity = capacity;
    if (capacity == 0)
    {
        str->Data = NULL;
        return str;
    }

    str->Data = malloc(capacity);
    if (str->Data == NULL)
    {
        free(str);
        return NULL;
    }
    str->Data[0] = '\0';
    return str;
}

String* NewStringFromChar(const char* data, size_t size)
{
    if (data == NULL || size == 0)
    {
        return NewStringWithCapacity(0);
    }

    String* str = NewStringWithCapacity(size + 1);
    if (str == NULL)
    {
        return NULL;
    }

    memcpy(str->Data, data, size);
    str->Data[size] = '\0';
    str->Size = size;
    return str;
}


String* NewStringFromChar_WithCapacity(const char* data, size_t size, size_t capacity)
{
    size_t actualCapacity = capacity;
    if (data != NULL && capacity < size + 1)
    {
        actualCapacity = size + 1;
    }

    String* str = NewStringWithCapacity(actualCapacity);
    if (str == NULL)
    {
        return NULL;
    }

    if (data == NULL)
    {
        return str;
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

    String* str = NewStringFromChar(inpStr->Data + start, end - start);
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
    if (inpStr == NULL || outStr == NULL)
    {
        return -1;
    }

    if (inpStr->Data == NULL || inpStr->Size == 0)
    {
        outStr->Size = 0;
        return 0;
    }

    return StringCopyFromCharPtr(outStr, inpStr->Data, inpStr->Size);
}

int StringCopyFromCharPtr(String* outStr, const char* src, size_t size)
{
    if (outStr == NULL || src == NULL)
    {
        return -1;
    }

    if (outStr->Data == NULL || outStr->Capacity < size + 1)
    {
        if (outStr->Data != NULL)
        {
            free(outStr->Data);
        }

        outStr->Capacity = size + 1;
        outStr->Data = malloc(outStr->Capacity);
        if (outStr->Data == NULL)
        {
            outStr->Capacity = 0;
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
    str->Capacity = 0;
    return 0;
}
