#include "../header/utility.h"
#include "../header/record.h"

struct record * createRecord(char * firstName, char * lastName, char * phone) {

    struct record *record = malloc(sizeof * record);

    record->firstName = copyText(firstName);
    record->lastName = copyText(lastName);
    record->phone = copyText(phone);

    return record;
}

void printRecord(struct record * record) {

    printf("Name: %s, %s; Phone: %s", record->firstName, record->lastName, record->phone);
}

void freeRecord(struct record * record) {

    free(record->firstName);
    free(record->lastName);
    free(record->phone);
    free(record);
}