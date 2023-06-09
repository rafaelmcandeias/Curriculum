#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> 

#include "tecnicofs-client-api.h"
#include "../tecnicofs-api-constants.h"

#define MAX_INPUT_SIZE 100

FILE* inputFile;
char* socketName;

//Used to remeber the user of the correct format to run the program
static void displayUsage (const char* appName) {
    printf("Usage: %s inputfile server_socket_name\n", appName);
    exit(EXIT_FAILURE);
}

//Used to clear memory when exiting with error
//freeFlag >  0 -> need to close the file
//freeFlag <  0 -> need to free socketName
//freeFlag =  0 -> need to free both
//freeFlag = -2 -> nothing to free
void exitError(char* Error, int freeFlag){
    if(freeFlag == -2){
        errorParse(Error);
    }
    if(freeFlag >= 0){
        fclose(inputFile);
    }
    if(freeFlag <= 0){
        free(socketName);
    }
    errorParse(Error);
}

//format: inputFile serverSocketName
static void parseArgs (long argc, char* const argv[]) {

    if (argc != 3) {
        fprintf(stderr, "Invalid format:\n");
        free(socketName);
        displayUsage(argv[0]);
    }
    
    if(allocateServer(argv[2]) == -1){
        exitError("Error: Server does not exist \n", -1);
    }

    inputFile = fopen(argv[1], "r");
    if (inputFile == NULL){
        exitError("Error: cannot open input file\n", 0);
    }

    
}

void *processInput() {
    char line[MAX_INPUT_SIZE];

    while (fgets(line, sizeof(line)/sizeof(char), inputFile)) {
        char op;
        char arg1[MAX_INPUT_SIZE], arg2[MAX_INPUT_SIZE];
        int res;
        int numTokens = sscanf(line, "%c %s %s", &op, arg1, arg2);

        /* perform minimal validation */
        if (numTokens < 1)
            continue;
        
        switch (op) {
            case 'c':
                if(numTokens != 3) {
                    exitError("Error: invalid input for tfsCreate", 0);
                    break;
                }
                switch (arg2[0]) {
                    case 'f':
                        res = tfsCreate(arg1, 'f');
                        if (!res)
                          printf("Created file: %s\n", arg1);
                        else
                          printf("Unable to create file: %s\n", arg1);
                        break;
                    
                    case 'd':
                        res = tfsCreate(arg1, 'd');
                        if (!res)
                          printf("Created directory: %s\n", arg1);
                        else
                          printf("Unable to create directory: %s\n", arg1);
                        break;
                    
                    default:
                        fprintf(stderr, "Error: invalid node type\n");
                }
                break;
            
            case 'l':
                if(numTokens != 2)
                    exitError("Error: invalid input for tfsLookup", 0);
                res = tfsLookup(arg1);
                if (res >= 0)
                    printf("Search: %s found\n", arg1);
                else
                    printf("Search: %s not found\n", arg1);
                break;
            
            case 'd':
                if(numTokens != 2)
                    exitError("Error: invalid input for tfsDelete", 0);
                res = tfsDelete(arg1);
                if (!res)
                  printf("Deleted: %s\n", arg1);
                else
                  printf("Unable to delete: %s\n", arg1);
                break;
            
            case 'm':
                if(numTokens != 3)
                    exitError("Error: invalid input for tfsMove", 0);
                res = tfsMove(arg1, arg2);
                if (!res)
                  printf("Moved: %s to %s\n", arg1, arg2);
                else
                  printf("Unable to move: %s to %s\n", arg1, arg2);
                break;
            
            case 'p':
                printf("Got a p \n");
                res = tfsPrint(arg1);
                if (!res)
                  printf("Print: tecnicoFs printed into %s\n", arg1);
                else
                  printf("Unable to print into %s\n", arg1);
                break;

            case '#':
                break;
           
            default:
                exitError("Error: invalid line in input file", 0);
        }
    }
    fclose(inputFile);
    return NULL;
}


// socket name will be /tmp/cliPID
int main(int argc, char* argv[]) {
    //Generate unique socket name
    int pid = getpid();
    int size = sizeof(char)*(3+7+1+5);
    socketName = malloc(size);
    snprintf(socketName, size, "/tmp/cli%d", pid); 
    
    parseArgs(argc, argv);
    
    if (tfsMount(socketName) == 0)
      printf("Mounted! (socket = %s)\n", socketName);

    processInput();

    tfsUnmount(socketName);

    exit(EXIT_SUCCESS);
}



