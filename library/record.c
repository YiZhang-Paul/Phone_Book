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

bool isSameRecord(struct record * record1, struct record * record2) {

    char *details1 = getRecordDetail(record1);
    char *details2 = getRecordDetail(record2);
    bool result = isSame(details1, details2);

    free(details1);
    free(details2);

    return result;
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