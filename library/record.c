#include "../header/utility.h"
#include "../header/record.h"

static struct phone * createPhone(int * digits, int length) {

    struct phone *phone = malloc(sizeof *phone);

    phone->digits = digits;
    phone->length = length;

    return phone;
}

static void printPhone(struct phone * phone) {

    for(int i = 0; i < phone->length; i++) {

        printf("%d", phone->digits[i]);
    }
}

static void freePhone(struct phone * phone) {

    free(phone->digits);
    free(phone);
}

struct record * createRecord(char * firstName, char * lastName, int * phone, int phoneLength) {

    struct record *record = malloc(sizeof * record);

    record->firstName = copyText(firstName);
    record->lastName = copyText(lastName);
    record->phone = createPhone(phone, phoneLength);

    return record;
}

void printRecord(struct record * record) {

    printf("Name: %s, %s; Phone: ", record->firstName, record->lastName);
    printPhone(record->phone);
}

void freeRecord(struct record * record) {

    free(record->firstName);
    free(record->lastName);
    freePhone(record->phone);
    free(record);
}