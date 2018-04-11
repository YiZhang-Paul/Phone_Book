#include "../header/display.h"

static void tryDisplay(struct trieNode * node) {

    if(isEmpty(node->dataList)) {

        return;
    }

    struct listNode *head = node->dataList;

    while(head != NULL) {

        printRecord(head->data);
        printf("\n");
        head = head->next;
    }
}

void displayByKey(struct trieNode * root, char * keys) {

    struct trieNode *node = retrieveTrieNode(root, keys);

    if(node == NULL || isEmpty(node->dataList)) {

        printf("Record not Found.\n");

        return;
    }

    tryDisplay(node);
}

void displayByPrefix(struct trieNode * root, char * prefix) {

    struct trieNode *node = retrieveTrieNode(root, prefix);

    if(node == NULL) {

        printf("No Records Found.\n");

        return;
    }

    displayAscending(node);
}

void displayAscending(struct trieNode * root) {

    tryDisplay(root);

    if(root->isLeaf) {

        return;
    }

    for(int i = 0; i < MAX_KEYS; i++) {

        if(root->child[i] != NULL) {

            displayAscending(root->child[i]);
        }
    }
}

void displayDescending(struct trieNode * root) {

    tryDisplay(root);

    if(root->isLeaf) {

        return;
    }

    for(int i = MAX_KEYS - 1; i >= 0; i--) {

        if(root->child[i] != NULL) {

            displayDescending(root->child[i]);
        }
    }
}