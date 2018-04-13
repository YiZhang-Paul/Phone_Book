#include "../header/utility.h"

//read single line of input from standard input
char * readLine(int length) {

    char *line = malloc(length);
    line = fgets(line, length, stdin);
    line[strlen(line) - 1] = '\0';

    return line;
}

bool isSameText(char * text1, char * text2) {

    if(strlen(text1) != strlen(text2)) {

        return false;
    }

    for(int i = 0; i < strlen(text1); i++) {

        if(text1[i] != text2[i]) {

            return false;
        }
    }

    return true;
}

//count total number of characters in a collection of character sequences
int countTotalLength(char ** splitted, int total) {

    int length = 0;

    for(int i = 0; i < total; i++) {

        length += strlen(splitted[i]);
    }

    return length;
}

char * copyText(char * text) {

    char *copy = malloc(strlen(text) + 1);

    return strcpy(copy, text);
}

char * getSubstring(char * text, int start, int end) {

    const int length = end - start + 1;
    char *substring = malloc(length + 1);
    substring[length] = '\0';

    return memcpy((void *)substring, (void *)&text[start], length);
}

char ** split(char * text, const char delimiter, int * total) {

    char **splitted = malloc(sizeof *splitted);
    const int length = strlen(text);

    for(int i = 0, start = 0; i < length; i++) {
        //include remaining portion of characters if there is any
        const bool onEnd = i == length - 1 && start < length;

        if(text[i] == delimiter || onEnd) {
            //add splitted substrings into collection
            splitted = realloc(splitted, sizeof *splitted * (*total + 1));
            splitted[(*total)++] = getSubstring(text, start, onEnd ? i : MAX(start, i - 1));
            start = i + 1;
        }
    }

    return splitted;
}

//join collection of character sequences together with given character
char * join(char ** splitted, const char character, int total) {
    //include memory space for delimiters
    const int length = countTotalLength(splitted, total) + total - 1;
    char *joined = malloc(length + 1);

    for(int i = 0, counter = 0; i < total; i++) {

        for(int j = 0; j < strlen(splitted[i]); j++) {

            joined[counter++] = splitted[i][j];
        }

        joined[counter++] = character;
    }

    joined[length] = '\0';

    return joined;
}

void createFile(char * fileName) {

    FILE *file = fopen(fileName, "w");

    fclose(file);
}