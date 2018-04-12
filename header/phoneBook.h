#ifndef PHONE_BOOK_H
#define PHONE_BOOK_H

#include <stdio.h>
#include "../header/linkedList.h"
#include "../header/trie.h"
#include "../header/record.h"
#include "../header/storage.h"
#include "../header/display.h"
#include "../header/validation.h"

#define FILE_NAME "records.txt"

static void initialize(void);
static char * getInformation(char * attribute, bool failed);
static void showListOption(void);
static int getListOption(void);
static void listByAttribute(struct trieNode * root, char * attribute);
static void addRecordToTries(char * firstName, char * lastName, char * phone);
static struct record * addRecord(void);
static void deleteRecord(struct record * record);
static void saveAll(void);
static void mainMenu(void);
static void addMenu(void);
static void deleteMenu(void);
static void updateMenu(void);
static void listMenu(void);
void run(void);

#endif