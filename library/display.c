#include "../header/display.h"

void displayByKey(struct trieNode * root, char * keys) {

    struct trieNode *node = retrieveTrieNode(root, keys);

    if(node == NULL) {

        printf("Record not Found.");

        return;
    }

    printRecord(node->data);
}

void displayAscending(struct trieNode * root) {

    if(root->isLeaf) {

        
    }
}

void displayDescending(struct trieNode * root) {


}