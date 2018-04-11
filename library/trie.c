#include "../header/trie.h"

static int getChildIndex(char key) {

    if(isdigit(key)) {

        return key - '0';
    }

    if(isalpha(key)) {

        return tolower(key) - 'a' + 10;
    }

    return 36;
}

struct trieNode * createTrieNode(void * data) {

    struct trieNode *trie = malloc(sizeof *trie);

    trie->parent = NULL;
    trie->isLeaf = false;
    trie->data = data;

    return trie;
}

void addToTrie(struct trieNode * root, char * keys, void * data) {

    struct trieNode *current = root;

    for(int i = 0; i < strlen(keys); i++) {

        struct trieNode *child = createTrieNode(NULL);
        current->child[getChildIndex(keys[i])] = child;
        child->parent = current;
        current = child;
    }

    current->data = data;
    current->isLeaf = true;
}

void freeTrie(struct trieNode * root) {

    
}