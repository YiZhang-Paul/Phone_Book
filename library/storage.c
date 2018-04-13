#include "../header/utility.h"
#include "../header/storage.h"

//load existing records from a file to all tries
void load(struct trieNode ** tries, char * fileName) {

    FILE *file = fopen(fileName, "r");
    char *line = malloc(LINE_LENGTH);

    if(file) {

        line = fgets(line, LINE_LENGTH, file);

        while(!feof(file)) {
            //remove newline character
            line[strlen(line) - 1] = '\0';
            int total = 0;
            char **keys = split(line, '|', &total);
            //load records to all tries
            for(int i = 0; i < total; i++) {

                addToTrie(tries[i], keys[i], createRecord(keys[0], keys[1], keys[2]));
            }

            line = fgets(line, LINE_LENGTH, file);
        }
    }

    free(line);

    fclose(file);
}

//save all records in a given trie to file
void save(struct trieNode * root, char * fileName) {

    if(root->isLeaf && !isEmpty(root->dataList)) {

        struct listNode *current = root->dataList;
        //save all records in linked list
        while(current != NULL) {

            saveRecord(current->data, fileName);
            current = current->next;
        }

        return;
    }
    //traverse to leaf node
    for(int i = 0; i < MAX_KEYS; i++) {

        if(root->child[i] != NULL) {

            save(root->child[i], fileName);
        }
    }
}