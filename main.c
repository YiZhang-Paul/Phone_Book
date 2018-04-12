#include <stdio.h>
#include <stdlib.h>
#include "header/utility.h"
#include "header/record.h"
#include "header/trie.h"
#include "header/display.h"
#include "header/storage.h"

int main(void) {

    struct trieNode *trie = createTrieNode(NULL);

    load(trie, 1, "records.txt");

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

    freeTrie(trie, freeRecord);

    return 0;
}