#include "../header/utility.h"
#include "../header/phoneBook.h"

int position;
struct trieNode *tries[3];

static void initialize(void) {

    for(int i = 0; i < FIELDS; i++) {

        tries[i] = createTrieNode();
    }

    load(tries, FILE_NAME);
    position = 0;
}

static char * readLine(void) {

    char *line = malloc(LINE_LENGTH);
    line = fgets(line, LINE_LENGTH, stdin);
    line[strlen(line) - 1] = '\0';

    return line;
}

static void quit(void) {

    printf("<Exiting Program, Press Any Key to Proceed.>");
    getchar();
    exit(0);
}

static char * getInformation(char * type, bool failed) {

    if(failed) {

        printf("<Invalid %s. Please Enter Again.>\n", type);
    }

    printf("<Enter Your %s:>", type);
    char *input = readLine();

    if(!isValidInput(input)) {

        free(input);

        return getInformation(type, true);
    }

    return input;
}

static struct record * addRecord(void) {

    char *firstName = getInformation("First Name", false);
    char *lastName = getInformation("Last Name", false);
    char *phone = getInformation("Phone", false);

    struct trieNode *node = retrieveTrieNode(tries[2], phone);

    if(node != NULL && !isEmpty(node->dataList)) {

        printf("Record with Specified Phone Number Already Exists.\n");

        return NULL;
    }

    addToTrie(tries[0], firstName, createRecord(firstName, lastName, phone));
    addToTrie(tries[1], lastName, createRecord(firstName, lastName, phone));
    addToTrie(tries[2], phone, createRecord(firstName, lastName, phone));

    return createRecord(firstName, lastName, phone);
}

static void deleteRecord(struct record * record) {

    deleteFromTrie(tries[0], record->firstName, record, freeRecord);
    deleteFromTrie(tries[1], record->lastName, record, freeRecord);
    deleteFromTrie(tries[2], record->phone, record, freeRecord);
}

static void saveAll(void) {

    createFile(FILE_NAME);
    save(tries[2], FILE_NAME);
}

static void getMainOption(void) {

    char *input = readLine();

    if(!isValidOption(input, 1, 5)) {

        printf("<Invalid Option, Please Choose Again.>\n");
        getMainOption();

        free(input);

        return;
    }

    switch(input[0]) {

        case '1' : case '2' : case '3' : case '4' :

            position = input[0] - '0';

            break;

        case '5' :

            quit();

            break;
    }

    free(input);
}

static void getAddOption(void) {

    printf("<Enter Record Details:>\n");
    struct record *record = addRecord();
    printf("%s\n\n", record == NULL ? "Failed to Add New Record." : "Record Added Successfully.");

    if(record != NULL) {

        saveAll();
    }

    position = 0;
}

static void getDeleteOption(void) {

    printf("<Enter Associated Phone Number You Wish to Delete:>");
    char *input = readLine();

    if(!isValidInput(input)) {

        printf("<Invalid Phone Number. Please Enter Again.>\n");
        getDeleteOption();

        free(input);

        return;
    }

    struct trieNode *node = retrieveTrieNode(tries[2], input);

    if(node == NULL || isEmpty(node->dataList)) {

        printf("\nRecord not Found.\n\n");
    }
    else {

        char *details = getRecordDetail(node->dataList->data);
        deleteRecord(node->dataList->data);
        printf("\nRecord: %s is Deleted Successfully.\n\n", details);
        saveAll();

        free(details);
    }

    free(input);

    position = 0;
}

void getUpdateOption(void) {

    printf("<Enter Associated Phone Number You Wish to Update:>");
    char *input = readLine();

    if(!isValidInput(input)) {

        printf("<Invalid Phone Number. Please Enter Again.>\n");
        getUpdateOption();

        free(input);

        return;
    }

    struct trieNode *node = retrieveTrieNode(tries[2], input);

    if(node == NULL || isEmpty(node->dataList)) {

        printf("\nRecord not Found.\n\n");
    }
    else {

        char *details = getRecordDetail(node->dataList->data);
        deleteRecord(node->dataList->data);
        struct record *newRecord = addRecord();

        if(newRecord == NULL) {

            printf("\nUpdate Failed.\n\n");

            free(details);
            free(input);

            position = 0;

            return;
        }

        char *newDetails = getRecordDetail(newRecord);
        printf("\nUpdate Successful.\nOld: %s\nNew: %s\n\n", details, newDetails);
        saveAll();

        free(details);
        free(newDetails);
    }

    free(input);

    position = 0;
}

void run(void) {

    initialize();

    while(true) {

        switch(position) {

            case 0 :

                printf("<What Would You Like to Do? (Enter Option Number to Proceed)>\n");
                printf("1. Add Record\n");
                printf("2. Delete Record\n");
                printf("3. Update Record\n");
                printf("4. Display Record(s)\n");
                printf("5. Exit Program\n");
                getMainOption();

                break;

            case 1 :

                getAddOption();

                break;

            case 2 :

                getDeleteOption();

                break;

            case 3 :

                getUpdateOption();

                break;

            case 4 :

                break;
        }
    }
}