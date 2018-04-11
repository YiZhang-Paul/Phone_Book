#ifndef RECORD_H
#define RECORD_H

#include <stdio.h>
#include <stdlib.h>

struct phone {

    int *digits;
    int length;
};

struct record {

    char *firstName;
    char *lastName;
    struct phone *phone;
};

static struct phone * createPhone(int *, int);
static void printPhone(struct phone *);
static void freePhone(struct phone *);
struct record * createRecord(char *, char *, int *, int);
void printRecord(struct record *);
void freeRecord(struct record *);

#endif