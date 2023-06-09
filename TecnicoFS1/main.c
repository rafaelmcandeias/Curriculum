/*Rafael Candeias - 93748
  Jose Mateus - 96884
  */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/time.h> //library chamada para utilizar a funcao gettimeofday
#include "fs/operations.h"

#define MAX_COMMANDS 150000
#define MAX_INPUT_SIZE 100

pthread_t* _threads = NULL;
int _sync_flag; //0 -> nosync; 1 -> mutex; 2 -> rwlock

/*variavel que guarda o numero de threads*/
int _numberOfThreads = 0;

char _inputCommands[MAX_COMMANDS][MAX_INPUT_SIZE];
int _numberCommands = 0;
int _headQueue = 0;


FILE *_outputFile = NULL;



int insertCommand(char* data) {
    if(_numberCommands != MAX_COMMANDS) {
        strcpy(_inputCommands[_numberCommands++], data);
        return 0;
    }
    return 1;
}


/*funcao usada para correr erros*/
void errorParse(const char* error){
    /*imprime no stderr uma mensagem de erro*/
    perror(error);
    /*fecha o ficheiro output*/
    fflush(_outputFile);
    /*liberta o trinco mutex*/
    destroy();
    /*sai do programa com erro*/
    exit(EXIT_FAILURE);
}


/*funcao utilizada para retirar comandos do buffer*/
char* removeCommand() {
    int i = 0;
    /*bloqueia o trinco. impede que outras threads acedam a este pedaco de codigo*/
    mutex_lock();
    if(_numberCommands > 0){
        _numberCommands--;
        i = _headQueue;
        _headQueue++;

        /*liberta o trinco. permite o acesso por outras threads a este pedaco de codigo*/
        mutex_unlock();
        return _inputCommands[i]; 
    }
    /*liberta o trinco. permite o acesso por outras threads a este pedaco de codigo*/
    mutex_unlock();
    return NULL;
}


/*funcao verifica uns argumentos e processa o input para o buffer de comandos*/
void processInput(int argc, char* inputFile, char* of, char* nThreads){
    char line[MAX_INPUT_SIZE];
    FILE* fp = NULL;

    /*verifica se o numero de threads e >= 1 caso o programa seja mutex ou rwlock*/
    if (_sync_flag > 0 && (_numberOfThreads = atoi(nThreads)) < 1){
        errorParse("Error: invalid number of threads");
    }
    /*verifica se o numero de threads e diferente que 1 caso o programa seja nosync*/
    if (_sync_flag == 0 && (_numberOfThreads = atoi(nThreads)) != 1){
        errorParse("Error: invalid number of threads");
    }

    /*abre o ficheiro input*/
    if ((fp = fopen(inputFile, "r")) == NULL){
    	errorParse("Error: can't open input file");
    }
    /*abre o ficheiro output*/
    if ((_outputFile = fopen(of, "w")) == NULL){
    	errorParse("Error: can't create output file");
    }

    while (fgets(line, sizeof(line)/sizeof(char), fp)) {
        char token, type;
        char name[MAX_INPUT_SIZE];

        int numTokens = sscanf(line, "%c %s %c", &token, name, &type);
        
        /* perform minimal validation */
        if (numTokens < 1) {
            continue;
        }
        switch (token) {
            case 'c':
                if(numTokens != 3)
                    errorParse("Error: command c invalid");
                if (!insertCommand(line))
                    continue;
                return;
            
            case 'l':
                if(numTokens != 2)
                    errorParse("Error: command l invalid");
                if (!insertCommand(line))
                    continue;
                return;
            
            case 'd':
                if(numTokens != 2)
                    errorParse("Error: command d invalid");
                if (!insertCommand(line))
                    continue;
                return;
            
            case '#':
                continue;
            
            default:/* error */
                errorParse("Error: command invalid");
        }
    }
    /*liberta memoria do ponteiro para o ficheiro input*/
    fclose(fp);
}


/*funcao que vai buscar comandos ao buffer e executa os*/
void *applyCommands(){
    while (_numberCommands > 0){
        const char* command = removeCommand();
        if (command == NULL){
            continue;
        }

        char token, type;
        char name[MAX_INPUT_SIZE];
        int numTokens = sscanf(command, "%c %s %c", &token, name, &type);
        if (numTokens < 2) {
            errorParse("Error: invalid command in Queue");
        }

        int searchResult;
        switch (token) {
            case 'c':
                switch (type) {
                    case 'f':
                        printf("Create file: %s\n", name);
                        create(name, T_FILE);
                        break;
                    case 'd':
                        printf("Create directory: %s\n", name);	
                        create(name, T_DIRECTORY);
                        break;
                    default:
                        errorParse("Error: invalid node type");
                }
                break;
            case 'l':
                searchResult = lookup(name);
                if (searchResult >= 0)
                    printf("Search: %s found\n", name);
                else
                    printf("Search: %s not found\n", name);
                break;
            case 'd':
                printf("Delete: %s\n", name);
                delete(name);
                break;
            default: { /* error */
                errorParse("Error: command to apply");
            }
        }
    }
    return 0;
}


/* Creates the pool of threads with how many threads the user choose
 * Input:
 *  - path: the path to split. ATENTION: the function may alter this parameter
 *  - parent: reference to a char*, to store parent path
 *  - child: reference to a char*, to store child file name
 */
void start_threads(){
    /*cria duas variaveis do tipo timeval*/
    struct timeval start, end;

    /*inicializa-se a estrutura start*/
    if (gettimeofday(&(start), NULL) == -1){
        errorParse("Error: reading time");
    }

    /*caso seja mutex ou rwlock*/
    if (_sync_flag > 0){
        /*aloca memoria para varias threads*/
        _threads = malloc(sizeof(pthread_t)* _numberOfThreads);

        /* Create the threads */
        for (int i = 0; i < _numberOfThreads; i++){
    		if (pthread_create(&_threads[i], NULL, applyCommands, NULL) != 0){
    			errorParse("Error: can't create thread");
    		}
    	}

        /* Wait for threads to finish */
    	for (int i = 0; i < _numberOfThreads; i++){
    		if (pthread_join(_threads[i], NULL) != 0){
    			errorParse("Error: can't join thread");
    		}
    	}
    }

    /*caso flag nosync*/
    else{
        applyCommands();
    }

    /*inicializa-se a estrutura end*/
    if (gettimeofday(&(end), NULL) == -1){
        errorParse("Error: reading time");
    }

    /*subtraiem-se os valores dos segundos e mili-segudos de cada uma das variaveis, para obter o tempo demorado*/
    float t = (end.tv_sec  + (end.tv_usec / 1000000.0)) - (start.tv_sec + (start.tv_usec / 1000000.0));
    /*imprime o resultado do tempo*/
    printf("TecnicoFS completed in %.4f seconds.\n", t);
	
    /*liberta a memoria alocada na criacao das threads*/
    free(_threads);
}


/*funcao para inicializar a flag de sincronizacao*/
void init_sync_flag(int argc, char* syncStrat){
    /* verifica se o numero de argumentos do input esta correto*/
    if (argc != 5){
    	errorParse("Error: invalid number of commands");
    }

    /*verifica se o ultimo argumento do input corresponde a nosync*/
    if (!strcmp(syncStrat, "nosync")){
        /*flag do sync fica 0*/
        _sync_flag = 0;
    }
    /*verifica se o ultimo argumento do input corresponde a mutex*/
    else if (!strcmp(syncStrat, "mutex")){
        /*flag do sync fica 1*/
        _sync_flag = 1;
    }
    /*verifica se o ultimo argumento do input corresponde a rwlock*/
    else if (!strcmp(syncStrat, "rwlock")){
        /*flag do sync fica 2*/
        _sync_flag = 2;
    }
    /*devolve um erro casa a flag do sync nao corresponda a 0, 1 ou 2*/
    else{
        errorParse("Error: Invalid sync strategy");
    }
    return;
}

int main(int argc, char* argv[]) {
    /* init program */
    init_sync_flag(argc, argv[4]);
    init_fs();

    /* process input*/
    processInput(argc, argv[1], argv[2], argv[3]);
    /*inicia as threads*/
    start_threads();
    /*imprime a base de dados para o ficheiro output*/
    print_tecnicofs_tree(_outputFile);


    /* release allocated memory */
    destroy_fs();
    /*fecha o ficheiro output*/
    fclose(_outputFile);
    
    exit(EXIT_SUCCESS);
}