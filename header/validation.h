#ifndef VALIDATION_H
#define VALIDATION_H

#include <string.h>
#include <stdbool.h>
#include <ctype.h>

static bool isValidCharacter(char);
bool isValidInput(char *);
bool isValidOption(char *, int, int);

#endif