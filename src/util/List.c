//
// Created by Yuriko on 12/14/2025.
//

#include "List.h"

#include <stdlib.h>

Node* NewNode(void* data)
{
    Node* node = malloc(sizeof(Node));
    if (node == NULL) {
        return NULL;
    }

    node->Data = data;
    node->Next = NULL;
    return node;
}

List* NewList()
{
    List* list = malloc(sizeof(List));
    if (list == NULL) {
        return NULL;
    }

    list->Size = 0;
    list->Head = NULL;
    list->Tail = NULL;
    return list;
}

void ListAdd(List* list, void* data)
{
    Node* node = NewNode(data);
    if (node == NULL) {
        return;
    }

    list->Size++;
    if (list->Size == 1)
    {
        list->Head = node;
        list->Tail = node;
        return;
    }

    list->Tail->Next = node;
    list->Tail = node;
}

void FreeList(List* list)
{
    if (list == NULL) {
        return;
    }

    Node* current = list->Head;
    while (current != NULL) {
        Node* next = current->Next;
        free(current);
        current = next;
    }

    free(list);
}