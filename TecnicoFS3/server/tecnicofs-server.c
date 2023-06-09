/*Rafael Candeias - 93748
  Jose Mateus - 96884*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <unistd.h>
#include "fs/operations.h"

#define MAX_COMMANDS 30
#define MAX_INPUT_SIZE 100

struct sockaddr_un _server_addr;
socklen_t _addrlen;

pthread_t* _threads = NULL;
pthread_t _inicial;

/* variavel que guarda o numero de threads*/
int _numberOfThreads = 0;
/* guarda o file descriptor para o socket criado*/
int _sockfd;



/* funcao usada para correr erros*/
void errorParse(const char* error){
    //imprime no stderr uma mensagem de erro/
    perror(error);
    //sai do programa com erro/
    exit(EXIT_FAILURE);
}


int setSockAddrUn(char *path, struct sockaddr_un *addr) {
    if (addr == NULL)
        return 0;

    bzero((char *)addr, sizeof(struct sockaddr_un));
    addr->sun_family = AF_UNIX;
    strcpy(addr->sun_path, path);

    return SUN_LEN(addr);
}


void criaSocket(char *nomesocket) {
    // cria um socket
    if ((_sockfd = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
        errorParse("Error: can't create socket");

    unlink(nomesocket);

    _addrlen = setSockAddrUn(nomesocket, &_server_addr);

    // associa ao socket o nomeseocket
    if (bind(_sockfd, (struct sockaddr *) &_server_addr, _addrlen) < 0)
        errorParse("Error: bind error");
}


/* funcao que verifica os argumentos inicias do programa
 * e trata do socket*/
void parseArguments(int argc, char* nThreads) {

    /* verifica se o numero de argumentos do input esta correto*/
    if (argc != 3)
        errorParse("Error: invalid number of commands");

    // verifica se o numero de threads e positivo e nao nulo
    if ((_numberOfThreads = atoi(nThreads)) <= 0)
        errorParse("Error: invalid number of threads");
}


//recebe um comando e aplica esse comando chamando as respectivas funcoes/
int applyCommand(char* command){
    char token, type;
    char name[MAX_INPUT_SIZE], new_path[MAX_INPUT_SIZE];
    char command_copy[MAX_INPUT_SIZE];
    strcpy(command_copy, command);
    
    if (sscanf(command_copy, "%c %s %c", &token, name, &type) < 2)
        errorParse("Error: reading from command in applyCommand went wrong");

    int searchResult;
    switch (token) {
        case 'c':
            switch (type) {
                case 'f':
                    printf("Create file: %s\n", name);
                    return create(name, T_FILE);
                case 'd':
                    printf("Create directory: %s\n", name);
                    return create(name, T_DIRECTORY);
                default:
                    errorParse("Error: invalid node type");
            }
        
        case 'l':
            searchResult = lookup(name);
            if (searchResult >= 0){
                printf("Search: %s found\n", name);
                return SUCCESS;
            }
            else{
                printf("Search: %s not found\n", name);
                return TECNICOFS_ERROR_FILE_NOT_FOUND;
            }

        case 'd':
            printf("Delete: %s\n", name);
            return delete(name);
        
        case 'm':
            sscanf(command_copy, "%c %s %s", &token, name, new_path);
            if (lookup(name) == FAIL) {
                printf("Error: 1st argument of m doesn't exist\n");
                return FAIL;
            }
            if (lookup(new_path) != FAIL) {
                printf("Error: 2nd argument of m already exists\n");
                return FAIL;
            }
            if (move(name, new_path) == FAIL) {
                printf("Error: move function failed\n");
                return FAIL;
            }
            return SUCCESS;

        case 'p':
            
            singleLock(FS_ROOT, 'w');
            print_tecnicofs_tree(name);
            singleUnlock(FS_ROOT);

            return SUCCESS;
        
        default: { /* error */
            errorParse("Error: command to apply");
        }
    }
    return FAIL;
}


void *startServer() {
    while(1) {
        struct sockaddr_un client_addr;
        char command[MAX_INPUT_SIZE];
        int c, resultMessage;
        _addrlen = sizeof(struct sockaddr_un);
        

        c = recvfrom(_sockfd, command, sizeof(command)-1, 0, &client_addr, &_addrlen);
        if (c == -1)
            errorParse("Error: recvfrom function went wrong");
        command[c] = '\0';

        resultMessage = applyCommand(command);

        c = sendto(_sockfd, &resultMessage, sizeof(resultMessage)+1, 0, &client_addr, _addrlen);
        if (c == -1)
            errorParse("Error: sendto function went wrong");
    }
}


/* Creates the pool of threads with how many threads the user choose
 * Input:
 *  - path: the path to split. ATENTION: the function may alter this parameter
 *  - parent: reference to a char*, to store parent path
 *  - child: reference to a char*, to store child file name
 */
void start_threads() {
    // aloca memoria para varias threads/
    _threads = malloc(sizeof(pthread_t)* _numberOfThreads);

    // Cria o numero pretendido de tarefas escravas para que recebam os pedidos do cliente 
    for (int i = 0; i < _numberOfThreads; i++){
        if (pthread_create(&_threads[i], NULL, startServer, NULL) != 0)
            errorParse("Error: can't create thread");
    }

    for (int i = 0; i < _numberOfThreads; i++){
        if (pthread_join(_threads[i], NULL) != 0)
            errorParse("Error: can't join thread");
    }
    
    //liberta a memoria alocada na criacao das threads/
    free(_threads);
}


int main(int argc, char* argv[]) {
    /* init program */
    init_fs();

    /* verifica os argumentos iniciais do programa*/
    parseArguments(argc, argv[1]);
    // cria o socket
    criaSocket(argv[2]);
    // inicia as threads
    start_threads();

    /* release allocated memory */
    destroy_fs();
    
    exit(EXIT_SUCCESS);
}







