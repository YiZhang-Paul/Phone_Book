#include "../header/display.h"

//display all records in a linked list
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

//display record with exact attribute value
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
    //display all records with given prefix
    displayAscending(node);
}

//display all records in ascending order
void displayAscending(struct trieNode * root) {

    tryDisplay(root);

    if(root->isLeaf) {

        return;
    }
    //traverse from lexicographically smallest to largest character key
    for(int i = 0; i < MAX_KEYS; i++) {

        if(root->child[i] != NULL) {

            displayAscending(root->child[i]);
        }
    }
}

//display all records in descending order
void displayDescending(struct trieNode * root) {

    tryDisplay(root);

    if(root->isLeaf) {

        return;
    }
    //traverse from lexicographically largest to smallest character key
    for(int i = MAX_KEYS - 1; i >= 0; i--) {

        if(root->child[i] != NULL) {

            displayDescending(root->child[i]);
        }
    }
}