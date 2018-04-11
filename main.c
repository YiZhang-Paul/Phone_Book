#include <stdio.h>
#include <stdlib.h>
#include "header/record.h"
#include "header/trie.h"
#include "header/display.h"

int main(void) {

    struct record *record1 = createRecord("Yi", "Zhang", "6472428108");
    struct record *record2 = createRecord("Jim", "Raynor", "9056231226");
    struct trieNode *trie = createTrieNode(NULL);

    addToTrie(trie, "zhang", record1);
    addToTrie(trie, "jim", record2);

    displayByKey(trie, "zhang");
    printf("\n");
    displayByKey(trie, "jim");
    printf("\n");

    displayAscending(trie);
    displayDescending(trie);

    freeRecord(record1);
    freeRecord(record2);

    return 0;
}