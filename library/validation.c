#include "../header/validation.h"

//only alphanumeric characters and single quote mark is allowed
static bool isValidCharacter(char character) {

    return isdigit(character) || isalpha(character) || character == '\'';
}

bool isValidInput(char * input) {
    //input must be between 1-30 characters
    if(strlen(input) < 1 || strlen(input) > 30) {

        return false;
    }

    for(int i = 0; i < strlen(input); i++) {

        if(!isValidCharacter(input[i])) {

            return false;
        }
    }

    return true;
}

//only single numeric characters allowed
bool isValidOption(char * option, int min, int max) {

    if(strlen(option) != 1) {

        return false;
    }

    return option[0] - '0' >= min && option[0] - '0' <= max;
}