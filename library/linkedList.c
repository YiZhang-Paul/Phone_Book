#include "../header/linkedList.h"

static struct listNode * createListNode(void * data) {

    struct listNode *node = malloc(sizeof *node);

    node->data = data;
    node->next = NULL;

    return node;
}

static void freeListNode(struct listNode * node, void freeData(void *)) {

    freeData(node->data);
    free(node);
}

static bool isEmpty(struct listNode * head) {

    return head == NULL;
}

static struct listNode * getListTail(struct listNode * head) {

    while(head != NULL && head->next != NULL) {

        head = head->next;
    }

    return head;
}

void addToList(struct listNode ** head, void * data) {

    struct listNode *node = createListNode(data);

    if(isEmpty(*head)) {

        *head = node;

        return;
    }

    getListTail(*head)->next = node;
}


void freeList(struct listNode ** head, void freeData(void *)) {

    struct listNode *current = *head;
    struct listNode *previous;

    while(current != NULL) {

        previous = current;
        current = current->next;
        freeListNode(previous, freeData);
    }

    *head = NULL;
}