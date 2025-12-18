//
// Created by Yuriko on 12/14/2025.
//

#ifndef CSTDLIB_LIST_H
#define CSTDLIB_LIST_H
#include <stddef.h>

typedef struct node
{
    void *Data;
    struct node *Next;
} Node;

typedef struct list
{
    size_t Size;
    Node *Head;
    Node *Tail;
} List;

Node *NewNode(void *data);
List *NewList();

void ListAdd(List *list, void *data);
void FreeList(List *list);

#endif //CSTDLIB_LIST_H