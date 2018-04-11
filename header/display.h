#ifndef DISPLAY_H
#define DISPLAY_H

#include "../header/linkedList.h"
#include "../header/trie.h"
#include "../header/record.h"

static void tryDisplay(struct trieNode *);
void displayByKey(struct trieNode *, char *);
void displayByPrefix(struct trieNode *, char *);
void displayAscending(struct trieNode *);
void displayDescending(struct trieNode *);

#endif