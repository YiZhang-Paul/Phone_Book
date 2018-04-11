#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdlib.h>
#include <stdbool.h>

struct listNode {

    void *data;
    struct listNode *next;
};

static struct listNode * createListNode(void *);
static void freeListNode(struct listNode *, void freeData(void *));
static struct listNode * getListTail(struct listNode *);
bool isEmpty(struct listNode *);
void addToList(struct listNode **, void *);
void freeList(struct listNode **, void freeData(void *));

#endif