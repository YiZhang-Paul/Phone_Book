#include "../header/storage.h"

void load(struct trieNode * root, char * fileName) {

    FILE *file = fopen(fileName, "r");

    if(file) {


    }

    fclose(file);
}


void save(struct trieNode * root, char * fileName) {

    if(root->isLeaf && !isEmpty(root->dataList)) {

        struct listNode *current = root->dataList;

        while(current != NULL) {

            saveRecord(current->data, fileName);
            current = current->next;
        }

        return;
    }

    for(int i = 0; i < MAX_KEYS; i++) {

        if(root->child[i] != NULL) {

            save(root->child[i], fileName);
        }
    }
}