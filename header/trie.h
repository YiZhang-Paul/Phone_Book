#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_KEYS 37

struct trieNode {

    struct trieNode *parent;
    struct trieNode *child[MAX_KEYS];
    bool isLeaf;
    void *data;
};

static int getChildIndex(char);
static bool isLeaf(struct trieNode *);
struct trieNode * createTrieNode(void *);
struct trieNode * retrieveTrieNode(struct trieNode *, char *);
void addToTrie(struct trieNode *, char *, void *);
void freeTrie(struct trieNode *);

#endif