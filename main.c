#include <stdio.h>
#include <stdlib.h>
#include "header/record.h"
#include "header/trie.h"
#include "header/display.h"

int main(void) {

    struct record *record1 = createRecord("Yi", "Zhang", "6472428108");
    struct record *record2 = createRecord("Jim", "Raynor", "9056231226");
    struct record *record3 = createRecord("Pimp", "Aha", "1655234231");
    struct record *record4 = createRecord("Jack", "Zhen", "1441231233");
    struct trieNode *trie = createTrieNode(NULL);

    addToTrie(trie, "zhang", record1);
    addToTrie(trie, "raynor", record2);
    addToTrie(trie, "aha", record3);
    addToTrie(trie, "zhen", record4);

    displayByKey(trie, "zhang");
    displayByKey(trie, "raynor");
    displayByKey(trie, "aha");
    displayByKey(trie, "zhen");
    displayByKey(trie, "zh");
    printf("\n");

    displayByPrefix(trie, "zh");
    displayByPrefix(trie, "j");
    displayByPrefix(trie, "ra");
    printf("\n");

    displayAscending(trie);
    printf("\n");
    displayDescending(trie);
    printf("\n");

    freeRecord(record1);
    freeRecord(record2);
    freeRecord(record3);
    freeRecord(record4);

    return 0;
}