//
// Created by Yuriko on 12/14/2025.
//

#include "List.h"

#include <stdlib.h>

Node* NewNode(void* data)
{
    Node* node = malloc(sizeof(Node));
    node->Data = data;
    return node;
}

List* NewList()
{
    List* list = malloc(sizeof(List));
    list->Size = 0;
    return list;
}

void ListAdd(List* list, void* data)
{
    Node* node = NewNode(data);
    list->Size++;
    if (list->Size == 1)
    {
        list->Head = node;
        list->Tail = node;
        return;
    }

    list->Tail->Next = node;
    list->Tail = node;
    return;
}
