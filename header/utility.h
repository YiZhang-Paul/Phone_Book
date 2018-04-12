#ifndef UTILITY_H
#define UTILITY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

char * readLine(int);
bool isSame(char *, char *);
int countTotalLength(char **, int);
char * copyText(char *);
char * getSubstring(char *, int, int);
char ** split(char *, const char, int *);
char * join(char **, const char, int);
void createFile(char *);

#endif