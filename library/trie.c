#include "../header/trie.h"

static int getChildIndex(char key) {

    if(isdigit(key)) {

        return key - '0';
    }

    if(isalpha(key)) {

        return tolower(key) - 'a' + 10;
    }

    return MAX_KEYS - 1;
}

static bool isPrefix(struct trieNode * root, char * keys) {

    return retrieveTrieNode(root, keys) != NULL;
}

static bool isLeaf(struct trieNode * root) {

    for(int i = 0; i < MAX_KEYS; i++) {

        if(root->child[i] != NULL) {

            return false;
        }
    }

    return true;
}

struct trieNode * createTrieNode() {

    struct trieNode *trie = malloc(sizeof *trie);

    trie->parent = NULL;
    trie->isLeaf = false;
    trie->dataList = NULL;

    for(int i = 0; i < MAX_KEYS; i++) {

        trie->child[i] = NULL;
    }

    return trie;
}

struct trieNode * retrieveTrieNode(struct trieNode * root, char * keys) {

    struct trieNode *current = root;

    for(int i = 0; i < strlen(keys); i++) {

        const int index = getChildIndex(keys[i]);

        if(current->child[index] == NULL) {

            return NULL;
        }

        current = current->child[index];
    }

    return current;
}

void addToTrie(struct trieNode * root, char * keys, void * data) {

    struct trieNode *current = root;

    for(int i = 0; i < strlen(keys); i++) {

        const int index = getChildIndex(keys[i]);

        if(current->child[index] == NULL) {

            struct trieNode *child = createTrieNode(NULL);
            child->parent = current;
            current->child[index] = child;
        }

        current = current->child[index];
        current->isLeaf = false;
    }

    addToList(&(current->dataList), data);
    current->isLeaf = isLeaf(current);
}

void freeTrie(struct trieNode * root) {


}