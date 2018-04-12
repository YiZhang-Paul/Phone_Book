#include "../header/utility.h"
#include "../header/storage.h"

void load(struct trieNode ** tries, char * fileName) {

    FILE *file = fopen(fileName, "r");
    char *line = malloc(LINE_LENGTH);

    if(file) {

        line = fgets(line, LINE_LENGTH, file);

        while(!feof(file)) {

            line[strlen(line) - 1] = '\0';
            int total = 0;
            char **keys = split(line, '|', &total);
            struct record *record = createRecord(keys[0], keys[1], keys[2]);

            for(int i = 0; i < total; i++) {

                addToTrie(tries[i], keys[i], record);
            }

            line = fgets(line, LINE_LENGTH, file);
        }
    }

    free(line);

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