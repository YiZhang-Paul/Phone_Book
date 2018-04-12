#ifndef STORAGE_H
#define STORAGE_H

#include <stdio.h>
#include "../header/trie.h"
#include "../header/linkedList.h"
#include "../header/record.h"

#define LINE_LENGTH 256

void load(struct trieNode **, char *);
void save(struct trieNode *, char *);

#endif