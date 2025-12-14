#include <stdio.h>

#include "util/List.h"

int main(void)
{
    List *list = NewList();
    ListAdd(list, "Hello");

    printf("Hello, World!\n");
    printf("%s\n", list->Head->Data);
    return 0;
}
