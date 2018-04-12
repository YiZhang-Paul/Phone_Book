#include "../header/validation.h"

static bool isValidCharacter(char character) {

    return isdigit(character) || isalpha(character) || character == '\'';
}

bool isValidInput(char * input) {

    if(strlen(input) < 1) {

        return false;
    }

    for(int i = 0; i < strlen(input); i++) {

        if(!isValidCharacter(input[i])) {

            return false;
        }
    }

    return true;
}