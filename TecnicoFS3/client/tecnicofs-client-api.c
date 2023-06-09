#include "tecnicofs-client-api.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include <stdio.h>

int _sockfd;
char *_serverName = NULL;

/* funcao usada para correr erros*/
void errorParse(const char* error){
    free(_serverName);
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


//Verifies if the server exists and saves its name
int allocateServer(char *serverName) {
  _serverName = malloc(sizeof(char)*(strlen(serverName) + 1));
  if(access(serverName, F_OK) == 0){                          //Means the server exists
    strcpy(_serverName, serverName);
    return 1;

  }
  return -1;
}


int send_receive(char *serverName, char *mensagem) {
	socklen_t servlen;
	struct sockaddr_un serv_addr;
	int resultMessage;
  int send_to_flag;
	servlen = setSockAddrUn(serverName, &serv_addr);

  send_to_flag = sendto(_sockfd, mensagem, strlen(mensagem)+1, 0, (struct sockaddr *) &serv_addr, servlen);

  if (send_to_flag < 0)
    return TECNICOFS_ERROR_NO_OPEN_SESSION;
      
  if (recvfrom(_sockfd, &resultMessage, sizeof(resultMessage)+1, 0, 0, 0) < 0)
   	errorParse("Error: recvfrom error");

  return resultMessage;
}


int tfsCreate(char *filename, char nodeType) {
  int filelen = strlen(filename);
  int size = sizeof(char)*(filelen+5);
  char *message = malloc(size);
  snprintf(message, size, "c %s %c", filename, nodeType);
  int resultMessage = send_receive(_serverName, message);

  free(message);

  return resultMessage;
}


int tfsDelete(char *path) {
	int filelen = strlen(path);
  int size = sizeof(char)*(filelen+3);
  char *message = malloc(size);
  snprintf(message, size, "d %s ", path);

  int resultMessage = send_receive(_serverName, message);

  free(message);

  return resultMessage;
}


int tfsMove(char *from, char *to) {
  int len = strlen(from) + strlen(to);
  int size = sizeof(char)*(len+5);
  char *message = malloc(size);
  snprintf(message, size, "m %s %s", from, to);

  int resultMessage = send_receive(_serverName, message);
  free(message);

  return resultMessage;
}

// Send the following to the server
int tfsLookup(char *path) {
 	int filelen = strlen(path);
  int size = sizeof(char)*(filelen+3);
  char *message = malloc(size);
  
  snprintf(message, size, "l %s ", path);
  int resultMessage = send_receive(_serverName, message);

  free(message);

  return resultMessage;
}

// send the following to the server
// p filename
int tfsPrint(char *outName) {
  int filelen = strlen(outName);
  int size = sizeof(char)*(filelen+3);
  char *message = malloc(size);

  snprintf(message, size, "p %s ", outName);
  int resultMessage = send_receive(_serverName, message);

  free(message);

  return resultMessage;
}

//Mount the client socket, it is used for the server to communicate with the client
int tfsMount(char *clientName) {
  socklen_t clilen;
	struct sockaddr_un client_addr;

	if ((_sockfd = socket(AF_UNIX, SOCK_DGRAM, 0) ) < 0)
   	errorParse("Error: can't open socket");

  unlink(clientName);

  clilen = setSockAddrUn (clientName, &client_addr);
  if (bind(_sockfd, (struct sockaddr *) &client_addr, clilen) < 0)
   	errorParse("Error: bind error");

  return 0;
}

//Close the client's socket
void tfsUnmount(char *socketName ) {
	if (close(_sockfd) != 0)
		errorParse("Error: can't close socket");
	
  free(socketName);
  free(_serverName);
}
