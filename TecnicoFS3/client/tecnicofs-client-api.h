#ifndef API_H
#define API_H

#include <sys/socket.h>
#include <sys/un.h>
#include "tecnicofs-api-constants.h"

void errorParse(const char* error);
int setSockAddrUn(char *path, struct sockaddr_un *addr);
int allocateServer(char *serverName);
int send_receive(char *serverName, char *mensagem);
int tfsCreate(char *path, char nodeType);
int tfsDelete(char *path);
int tfsLookup(char *path);
int tfsMove(char *from, char *to);
int tfsPrint(char *outName);
int tfsMount(char *clientName);
void tfsUnmount(char *socketName);

#endif /* CLIENT_H */
