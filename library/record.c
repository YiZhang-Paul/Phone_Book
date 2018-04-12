#include "../header/utility.h"
#include "../header/record.h"

struct record * createRecord(char * firstName, char * lastName, char * phone) {

    struct record *record = malloc(sizeof * record);

    record->firstName = copyText(firstName);
    record->lastName = copyText(lastName);
    record->phone = copyText(phone);

    return record;
}

struct record * copyRecord(struct record * record) {

    return createRecord(record->firstName, record->lastName, record->phone);
}

char * getRecordDetail(struct record * record) {

    char *details[5] = { "Name:", record->firstName, record->lastName, "Phone:", record->phone };

    return join(details, ' ', 5);
}

void printRecord(struct record * record) {

    char *details = getRecordDetail(record);
    printf("%s", details);

    free(details);
}

void saveRecord(struct record * record, char * fileName) {

    FILE *file = fopen(fileName, "a");

    if(file) {

        char *information[] = { record->firstName, record->lastName, record->phone };

        fprintf(file, "%s\n", join(information, '|', 3));
    }

    fclose(file);
}

void freeRecord(void * record) {

    struct record *toFree = (struct record *)record;

    free(toFree->firstName);
    free(toFree->lastName);
    free(toFree->phone);
    free(toFree);
}