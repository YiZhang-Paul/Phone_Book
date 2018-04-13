#include "../header/utility.h"
#include "../header/phoneBook.h"

int position; //current menu position
struct trieNode *tries[FIELDS];

static void initialize(void) {

    for(int i = 0; i < FIELDS; i++) {

        tries[i] = createTrieNode();
    }

    load(tries, FILE_NAME);
    position = 0; //default position for main menu
}

//prompt user for input
static char * getInformation(char * attribute, bool failed) {

    if(failed) {

        printf("<Invalid %s. Please Enter Again.>\n", attribute);
    }

    printf("<Enter Your %s:>", attribute);
    char *input = readLine(LINE_LENGTH);

    if(!isValidInput(input)) {

        free(input);
        //prompt until valid input is received
        return getInformation(attribute, true);
    }

    return input;
}

static void showListOption(void) {

    printf("<How Should Records be Displayed? (Enter Option Number to Proceed)>\n");
    printf("1. By Exact Entry\n");
    printf("2. By Prefix of Entries\n");
    printf("3. By Ascending Order\n");
    printf("4. By Descending Order\n");
}

//prompt for user selection of list option
static int getListOption(void) {

    char *input = readLine(LINE_LENGTH);

    if(!isValidOption(input, 1, 4)) {

        free(input);
        printf("<Invalid Option, Please Choose Again.>\n");

        return getListOption();
    }

    const int option = input[0] - '0';

    free(input);

    return option;
}

//display records by given attribute
static void listByAttribute(struct trieNode * root, char * attribute) {

    char *input;

    switch(getListOption()) {

        case 1 :

            input = getInformation(attribute, false);
            displayByKey(root, input);

            break;

        case 2 :

            input = getInformation(attribute, false);
            displayByPrefix(root, input);

            break;

        case 3 :

            displayAscending(root);

            break;

        case 4 :

            displayDescending(root);

            break;
    }

    free(input);
}

//add copies of record to all tries
static void addRecordToTries(char * firstName, char * lastName, char * phone) {

    addToTrie(tries[0], firstName, createRecord(firstName, lastName, phone));
    addToTrie(tries[1], lastName, createRecord(firstName, lastName, phone));
    addToTrie(tries[2], phone, createRecord(firstName, lastName, phone));
}

static struct record * addRecord(void) {
    //retrieve user input
    char *firstName = getInformation("First Name", false);
    char *lastName = getInformation("Last Name", false);
    char *phone = getInformation("Phone", false);

    struct trieNode *node = retrieveTrieNode(tries[2], phone);

    if(node != NULL && !isEmpty(node->dataList)) {

        printf("Record with Specified Phone Number Already Exists.\n");

        return NULL;
    }

    addRecordToTries(firstName, lastName, phone);
    //return copy of new record added
    return createRecord(firstName, lastName, phone);
}

//delete record from all tries
static void deleteRecord(struct record * record) {

    deleteFromTrie(tries[0], record->firstName, record, freeRecord);
    deleteFromTrie(tries[1], record->lastName, record, freeRecord);
    deleteFromTrie(tries[2], record->phone, record, freeRecord);
}

static void saveAll(void) {
    //overwrite existing file
    createFile(FILE_NAME);
    //save by phone number since phone numbers are unique
    save(tries[2], FILE_NAME);
}

static void quit(void) {
    //free memory allocated for all tries
    for(int i = 0; i < FIELDS; i++) {

        freeTrie(tries[i], freeRecord);
    }

    printf("<Exiting Program, Press Any Key to Proceed.>");
    getchar();
    exit(0);
}

static void mainMenu(void) {

    char *input = readLine(LINE_LENGTH);

    if(!isValidOption(input, 1, 5)) {

        printf("<Invalid Option, Please Choose Again.>\n");
        mainMenu();

        free(input);

        return;
    }
    //jump to corresponding menu position
    switch(input[0]) {

        case '1' : case '2' : case '3' : case '4' :

            position = input[0] - '0';

            break;

        case '5' :

            free(input);
            quit();

            break;
    }

    free(input);
}

static void addMenu(void) {

    printf("<Enter Record Details:>\n");
    struct record *record = addRecord();
    printf("%s\n\n", record == NULL ? "Failed to Add New Record." : "Record Added Successfully.");

    if(record != NULL) {

        saveAll();
    }

    position = 0;
}

static void deleteMenu(void) {

    printf("<Enter Associated Phone Number You Wish to Delete:>");
    char *input = readLine(LINE_LENGTH);

    if(!isValidInput(input)) {

        printf("<Invalid Phone Number. Please Enter Again.>\n");
        deleteMenu();

        free(input);

        return;
    }

    struct trieNode *node = retrieveTrieNode(tries[2], input);

    if(node == NULL || isEmpty(node->dataList)) {

        printf("\nRecord not Found.\n\n");
    }
    else {
        //keep old record details before deleting
        char *details = getRecordDetail(node->dataList->data);
        deleteRecord(node->dataList->data);
        printf("\nRecord: %s is Deleted Successfully.\n\n", details);
        saveAll();

        free(details);
    }

    free(input);

    position = 0;
}

static void updateMenu(void) {

    printf("<Enter Associated Phone Number You Wish to Update:>");
    char *input = readLine(LINE_LENGTH);

    if(!isValidInput(input)) {

        printf("<Invalid Phone Number. Please Enter Again.>\n");
        updateMenu();

        free(input);

        return;
    }

    struct trieNode *node = retrieveTrieNode(tries[2], input);

    if(node == NULL || isEmpty(node->dataList)) {

        printf("\nRecord not Found.\n\n");
    }
    else {
        //keep old record details before deleting
        struct record *oldRecord = copyRecord(node->dataList->data);
        deleteRecord(node->dataList->data);
        struct record *newRecord = addRecord();

        if(newRecord == NULL) {
            //add old record back when update failed
            addRecordToTries(oldRecord->firstName, oldRecord->lastName, oldRecord->phone);
            printf("\nUpdate Failed.\n\n");

            free(input);
            free(oldRecord);

            position = 0;

            return;
        }

        char *oldDetails = getRecordDetail(oldRecord);
        char *newDetails = getRecordDetail(newRecord);
        printf("\nUpdate Successful.\nOld: %s\nNew: %s\n\n", oldDetails, newDetails);
        saveAll();

        free(oldRecord);
        free(oldDetails);
        free(newDetails);
    }

    free(input);

    position = 0;
}

static void listMenu(void) {

    char *input = readLine(LINE_LENGTH);

    if(!isValidOption(input, 1, 3)) {

        printf("<Invalid Option, Please Choose Again.>\n");
        listMenu();

        free(input);

        return;
    }
    //display records
    switch(input[0]) {

        case '1' :

            showListOption();
            listByAttribute(tries[0], "First Name");

            break;

        case '2' :

            showListOption();
            listByAttribute(tries[1], "Last Name");

            break;

        case '3' :

            showListOption();
            listByAttribute(tries[2], "Phone Number");

            break;
    }

    free(input);

    position = 0;
}

void run(void) {

    initialize();
    //main loop
    while(true) {

        switch(position) {

            case 0 :

                printf("<What Would You Like to Do? (Enter Option Number to Proceed)>\n");
                printf("1. Add Record\n");
                printf("2. Delete Record\n");
                printf("3. Update Record\n");
                printf("4. Display Record(s)\n");
                printf("5. Exit Program\n");
                mainMenu();

                break;

            case 1 :

                addMenu();

                break;

            case 2 :

                deleteMenu();

                break;

            case 3 :

                updateMenu();

                break;

            case 4 :

                printf("<How Do You Want to Search the Records? (Enter Option Number to Proceed)>\n");
                printf("1. By First Name\n");
                printf("2. By Last Name\n");
                printf("3. By Phone Number\n");
                listMenu();

                break;
        }
    }
}