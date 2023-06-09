/*Rafael Candeias - 93748
  Jose Mateus - 96884*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <sys/time.h> //library chamada para utilizar a funcao gettimeofday
#include "fs/operations.h"



#define MAX_COMMANDS 10
#define MAX_INPUT_SIZE 100

pthread_t* _threads = NULL;
pthread_t _produtora;
pthread_mutex_t mutex;
pthread_cond_t podeProd, podeCons; 

/* variavel que guarda o numero de threads*/
int _numberOfThreads = 0;


int hasEnded  = 0;                                     //Usado para avisar os consumidores que nao ha mais comandos
char _inputCommands[MAX_COMMANDS][MAX_INPUT_SIZE];     //Buffer ciclico de comandos 
int _numberCommands = 0;                               //Saber quantos comandos tenho por fazer
int _currentIndex = 0;                                 //Saber a posicao atual do buffer

/* variaveis que guardam os ficheiros de entrada e saida*/
FILE* _inputFile = NULL;
FILE* _outputFile = NULL;





//Adiciona uma linha ao buffer e incrementa as respectivas variaveis
void insertCommand(char* data) {
    int index = (_currentIndex + _numberCommands) % MAX_COMMANDS;
    _numberCommands++;
    strcpy(_inputCommands[index], data);   
}

//Vai buscar a proxima linha ao bugger
char* getCommand(){
    if (_numberCommands == 0) 
        return NULL;
    if (_numberCommands > 0)
        _numberCommands--;
    if(_currentIndex == MAX_COMMANDS){                    //Tornar a lista ciclica
        _currentIndex = 0;
    }
    return _inputCommands[_currentIndex++];
}

/* funcao usada para correr erros*/
void errorParse(const char* error){
    //imprime no stderr uma mensagem de erro/
    perror(error);
    //fecha o ficheiro output/
    fflush(_outputFile);

    //sai do programa com erro/
    exit(EXIT_FAILURE);
}


/* funcao que verifica os argumentos inicias do programa
 * e cria os ficheiros input e output*/
void parseArguments(int argc, char* inputFile, char* outputFile, char* nThreads) {
    /* verifica se o numero de argumentos do input esta correto*/
    if (argc != 4){
        errorParse("Error: invalid number of commands");
    }
    
    //abre o ficheiro input/
    if ((_inputFile = fopen(inputFile, "r")) == NULL){
        errorParse("Error: can't open input file");
    }
    //abre o ficheiro output/
    if ((_outputFile = fopen(outputFile, "w")) == NULL){
        errorParse("Error: can't create output file");
    }

    //verifica se o numero de threads e >= 1 caso o programa seja mutex ou rwlock/
    if ((_numberOfThreads = atoi(nThreads)) == 0){
        errorParse("Error: invalid number of threads");
    }
}


/* funcao que processa o input*/
char* processInput(char* line){
    
    char token, type;
    char name[MAX_INPUT_SIZE];

    int numTokens = sscanf(line, "%c %s %c", &token, name, &type);
        
    /* perform minimal validation */
    if (numTokens < 1) {
        errorParse("Error: invalid number of commands");
    }
    switch (token) {
        case 'c':
            if(numTokens != 3)
                errorParse("Error: command c invalid");
            return line;
            
        case 'l':
            if(numTokens != 2)
                errorParse("Error: command l invalid");
            return line;
        
        case 'd':
            if(numTokens != 2)
                errorParse("Error: command d invalid");
            return line;
            
        case 'm':
            if (numTokens != 3)
                errorParse("Error: command m invalid");
            return line;
        case '#':
            break;
        
        default:/* error */
            errorParse("Error: command invalid");
    }
    return NULL;
}




//recebe um comando e aplica esse comando chamando as respectivas funcoes/
void applyCommands(const char* command){
    char token, type;
    char name[MAX_INPUT_SIZE], new_path[MAX_INPUT_SIZE];
    char command_copy[MAX_INPUT_SIZE];
    strcpy(command_copy, command);
    int numTokens = sscanf(command_copy, "%c %s %c", &token, name, &type);
    
    if (numTokens < 2) {
        errorParse("Error: invalid command in Queue");
    }

    int searchResult;
    switch (token) {
        case 'c':
            switch (type) {
                case 'f':
                    fprintf(_outputFile, "Create file: %s\n", name);
                    create(name, T_FILE);
                    break;
                case 'd':
                    fprintf(_outputFile, "Create directory: %s\n", name);   
                    create(name, T_DIRECTORY);
                    break;
                default:
                    errorParse("Error: invalid node type");
            }
        break;
        case 'l':
            searchResult = lookup(name);
            if (searchResult >= 0)
                fprintf(_outputFile, "Search: %s found\n", name);
            else
                fprintf(_outputFile, "Search: %s not found\n", name);
            break;
        case 'd':
            fprintf(_outputFile, "Delete: %s\n", name);
            delete(name);
            break;
        case 'm':
            sscanf(command_copy, "%c %s %s", &token, name, new_path);
            if (lookup(name) == FAIL) {
                printf("Error: 1st argument of m doesn't exist\n");
                break;
            }
            if (lookup(new_path) != FAIL) {
                printf("Error: 2nd argument of m already exists \n");
                break;
            }
            if (move(name, new_path) == FAIL) {
                printf("Error: move function failed \n");                  
                break;
            }
            break;
        default: { /* error */
            errorParse("Error: command to apply");
        }
    }
}

//Funcao produtora, 
void *produtor(){
    char line[MAX_INPUT_SIZE];
    char* command = NULL;
    while(fgets(line, sizeof(line)/sizeof(char), _inputFile)){
        if ((command = processInput(line)) != NULL){    //aqui vamos buscar a linha
            
            //printf("MAIN MUTEX LOCKED \n");
            pthread_mutex_lock(&mutex);     
            while(_numberCommands >= MAX_COMMANDS){          //Garantir que tenho espaco no buffer
                
                //printf("[DEBUG] Lista esta cheia, a espera que consumam \n");
                pthread_cond_wait(&podeProd, &mutex); //Caso contrario esperar ate ter espaco
            }
            
            //printf("[DEBUG] P command = %s", command);
            insertCommand(command);
            pthread_cond_signal(&podeCons);                 //Avisar que adicionei um comando
            pthread_mutex_unlock(&mutex);
            
            //printf("MAIN MUTEX UNLOCK \n");
        }
    }
    
    //printf("This means that there was no more command to read \n");
    pthread_mutex_lock(&mutex);     
    hasEnded = 1;
    pthread_cond_broadcast(&podeCons);                 //Avisar que adicionei um comando
    pthread_mutex_unlock(&mutex);

    
    //printf("Acabei com todos os comandos \n");
    return 0;
}

void *consumidor(){
    const char* command;
    
    while (1){
        pthread_mutex_lock(&mutex);        
        while (_numberCommands == 0){
            if(hasEnded){
                pthread_mutex_unlock(&mutex);
                return 0;
            }            
            pthread_cond_wait(&podeCons,&mutex);
        }
        command = getCommand(); 
                    
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&podeProd);
        applyCommands(command);

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
    //cria duas variaveis do tipo timeval/
    struct timeval start, end;

    //7inicializa-se a estrutura start/
    if (gettimeofday(&(start), NULL) == -1)
        errorParse("Error: reading time");

    //aloca memoria para varias threads/
    _threads = malloc(sizeof(pthread_t)* _numberOfThreads);

    /* Create the threads */
    if (pthread_create(&_produtora, NULL, produtor, NULL) != 0)
        errorParse("Error: can't create thread produtora");
    for (int i = 0; i < _numberOfThreads; i++){
        if (pthread_create(&_threads[i], NULL, consumidor, NULL) != 0)
            errorParse("Error: can't create thread");
    }
    /* Wait for threads to finish */
    if (pthread_join(_produtora, NULL) != 0)
        errorParse("Error: can't join produtora");
    for (int i = 0; i < _numberOfThreads; i++){
        if (pthread_join(_threads[i], NULL) != 0)
            errorParse("Error: can't join thread");
    }

    //inicializa-se a estrutura end/
    if (gettimeofday(&(end), NULL) == -1)
        errorParse("Error: reading time");

    //subtraiem-se os valores dos segundos e mili-segudos de cada uma das variaveis, para obter o tempo demorado/
    float t = (end.tv_sec  + (end.tv_usec / 1000000.0)) - (start.tv_sec + (start.tv_usec / 1000000.0));
    //imprime o resultado do tempo/
    printf("TecnicoFS completed in %.4f seconds.\n", t);
    
    //liberta a memoria alocada na criacao das threads/
    free(_threads);
}


void terminate() {
    if (fclose(_inputFile) != 0)
        errorParse("Error: Closing inputfile");
    if (fclose(_outputFile) != 0)
        errorParse("Error: Closing outputfile");
}


int main(int argc, char* argv[]) {
    /* init program */
    init_fs();

    /* verifica os argumentos iniciais do programa*/
    parseArguments(argc, argv[1], argv[2], argv[3]);
    //inicia as threads/
    start_threads();
    //imprime a base de dados para o ficheiro output/
    print_tecnicofs_tree(_outputFile);

    /* release allocated memory */
    destroy_fs();
    //fecha os ficheiros stdio/
    terminate();
    
    exit(EXIT_SUCCESS);
}