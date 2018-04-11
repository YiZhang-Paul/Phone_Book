#include "../header/utility.h"

char * copyText(char * text) {

    char *copy = malloc(strlen(text) + 1);

    return strcpy(copy, text);
}