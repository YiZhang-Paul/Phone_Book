#ifndef RECORD_H
#define RECORD_H

#include <stdio.h>
#include <stdlib.h>

struct record {

    char *firstName;
    char *lastName;
    char *phone;
};

struct record * createRecord(char *, char *, char *);
void printRecord(struct record *);
void saveRecord(struct record *, char *);
void freeRecord(void *);

#endif