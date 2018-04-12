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

static void quit(void) {

    getchar();
    printf("<Exiting Program, Press Any Key to Proceed.>");
    getchar();
    exit(0);
}

static void saveAll(void) {

    createFile(FILE_NAME);
    save(tries[2], FILE_NAME);
}

static void getMainMenuOption(void) {

    char input = getchar();

    switch(input) {

        case '1' : case '2' : case '3' : case '4' :

            position = input - '0';

            break;

        case '5' :

            quit();

            break;

        default :

            if(input != '\n') {

                printf("<(Option %c) Invalid Option, Please Choose Again.>\n", input);
            }

            getMainMenuOption();
    }
}

void run(void) {

    initialize();

    while(true) {

        switch(position) {

            case 0 :

                printf("<What would you like to do? (enter option number to proceed)>\n");
                printf("1. Add Record\n");
                printf("2. Delete Record\n");
                printf("3. Update Record\n");
                printf("4. Display Record(s)\n");
                printf("5. Exit Program\n");
                getMainMenuOption();
        }

        break;
    }
}