#include <stdio.h>
#include <stdlib.h>
#include "header/utility.h"
#include "header/record.h"
#include "header/trie.h"
#include "header/display.h"
#include "header/storage.h"

int main(void) {

    struct trieNode *firstNames = createTrieNode(NULL);
    struct trieNode *lastNames = createTrieNode(NULL);
    struct trieNode *phones = createTrieNode(NULL);
    struct trieNode *tries[3] = { firstNames, lastNames, phones };

    load(tries, "records.txt");

    displayByKey(lastNames, "zhang");
    displayByKey(lastNames, "raynor");
    displayByKey(lastNames, "aha");
    displayByKey(lastNames, "zhen");
    displayByKey(lastNames, "zh");
    printf("\n");

    displayByPrefix(lastNames, "zh");
    displayByPrefix(lastNames, "j");
    displayByPrefix(lastNames, "ra");
    printf("\n");

    displayByPrefix(firstNames, "zh");
    displayByPrefix(firstNames, "ja");
    displayByPrefix(firstNames, "ra");
    printf("\n");

    displayAscending(lastNames);
    printf("\n");
    displayDescending(lastNames);
    printf("\n");

    freeTrie(firstNames, freeRecord);
    freeTrie(lastNames, freeRecord);
    freeTrie(phones, freeRecord);

    return 0;
}