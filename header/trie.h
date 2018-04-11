#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct trieNode {

    struct trieNode *parent;
    struct trieNode *child[37];
    bool isLeaf;
    void *data;
};

static int getChildIndex(char);
struct trieNode * createTrieNode(void *);
void addToTrie(struct trieNode *, char *, void *);
void freeTrie(struct trieNode *);

#endif