//
// Created by Yuriko on 12/14/2025.
//

#include "String.h"

#include <stdlib.h>
#include <string.h>

String *NewString(char *data) {
    String *str = malloc(sizeof(String));
    if (data == NULL) {
        str->Size = 0;
        return str;
    }

    str->Data = data;
    str->Size = strlen(data);
    return str;
}

String *StringSlice(String *inpStr, size_t start, size_t end) {
    String *str = NewString(inpStr->Data + start);
    str->Size = end - start;
    return str;
}

char StringGet(String *str, size_t idx) {
    if (idx < str->Size) {
        return str->Data[idx];
    }
    return 0;
}

int StringCopy(String *inpStr, String *outStr) {
    for (int i = 0; i < inpStr->Size; ++i) {
        outStr->Data[i] = StringGet(inpStr, i);
        if (outStr->Data[i] == 0) {
            outStr->Size = i;
            return -1;
        }
    }
    outStr->Size = inpStr->Size;
    return 0;
}

int FreeString(String *str) {
    free(str->Data);
}
