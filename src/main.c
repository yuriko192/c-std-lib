#include <stdio.h>
#include <string.h>

#include "util/List.h"
#include "util/network/Http.h"

int main(void) {
    List *list = NewList();
    ListAdd(list, "Hello");

    printf("Hello, World!\n");
    printf("%s\n", (char*)list->Head->Data);
    printf("\n");

    String *output = (String *)NewString("", 0);
    const char *host = "127.0.0.1";
    const char *endpoint = "/application/health";
    CreateHttpRequest(output, GET, NewString(host, strlen(host)), NewString(endpoint, strlen(endpoint)));
    printf("%s\n", output->Data);
    return 0;
}
