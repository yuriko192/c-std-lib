#include <stdio.h>

#include "util/List.h"
#include "util/network/Http.h"

int main(void) {
    List *list = NewList();
    ListAdd(list, "Hello");

    printf("Hello, World!\n");
    printf("%s\n", list->Head->Data);
    printf("\n");

    String *output = (String *)NewString(nullptr);
    CreateHttpRequest(output, GET, NewString("127.0.0.1"), NewString("/application/health"));
    printf("%s\n", output->Data);
    return 0;
}
