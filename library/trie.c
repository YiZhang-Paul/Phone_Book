#include "../header/trie.h"

//calculate index of child node with given character key
static int getChildIndex(char key) {

    if(isdigit(key)) {

        return key - '0';
    }

    if(isalpha(key)) {

        return tolower(key) - 'a' + 10;
    }
    //index for single quote mark
    return MAX_KEYS - 1;
}

//check if given node is a leaf node
static bool isLeaf(struct trieNode * root) {

    for(int i = 0; i < MAX_KEYS; i++) {

        if(root->child[i] != NULL) {

            return false;
        }
    }

    return true;
}

struct trieNode * createTrieNode(void) {

    struct trieNode *trie = malloc(sizeof *trie);

    trie->parent = NULL;
    trie->isLeaf = false;
    trie->dataList = NULL;
    //initialize child array with null values
    for(int i = 0; i < MAX_KEYS; i++) {

        trie->child[i] = NULL;
    }

    return trie;
}

static void freeTrieNode(struct trieNode * node, void freeData(void *)) {

    if(node->parent == NULL) {

        return;
    }
    //free all data
    freeList(&(node->dataList), freeData);
    free(node);
}

//traverse the trie with given key
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
        //create new node when child does not exist
        if(current->child[index] == NULL) {

            struct trieNode *child = createTrieNode();
            child->parent = current;
            current->child[index] = child;
        }

        current = current->child[index];
        //overwrite leaf node indicator
        current->isLeaf = false;
    }

    addToList(&(current->dataList), data);
    current->isLeaf = isLeaf(current);
}

void deleteFromTrie(struct trieNode * root, char * keys, struct record * record, void freeData(void *)) {

    struct trieNode *node = retrieveTrieNode(root, keys);

    if(node != NULL && !isEmpty(node->dataList)) {

        struct listNode *current = node->dataList;
        //when record is on list head
        if(isSameRecord(current->data, record)) {

            node->dataList = current->next;
            freeListNode(current, freeData);

            return;
        }

        struct listNode *previous = current;
        current = current->next;
        //when record is in the middle or at the end of list
        while(current != NULL) {

            if(isSameRecord(current->data, record)) {

                previous->next = current->next;
                freeListNode(current, freeData);

                break;
            }

            previous = current;
            current = current->next;
        }
    }
}

//free memory allocated for trie recursively from bottom to top
void freeTrie(struct trieNode * root, void freeData(void *)) {

    if(root->isLeaf) {

        freeTrieNode(root, freeData);

        return;
    }

    for(int i = 0; i < MAX_KEYS; i++) {

        if(root->child[i] != NULL) {

            freeTrie(root->child[i], freeData);
        }
    }
    //free current node after all child nodes are freed
    freeTrieNode(root, freeData);
}