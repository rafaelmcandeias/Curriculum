# Makefile, versao 1
# Sistemas Operativos, DEI/IST/ULisboa 2020-21
# Servidor

CC   = gcc
LD   = gcc
CFLAGS = -pthread -Wall -std=gnu99 -I../
LDFLAGS = -lm -lpthread	#Flag para compilar com threads

# A phony target is one that is not really the name of a file
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY: all clean

all: tecnicofs-server

#TECNICOFS-server:
#compilacao do ficheiro locks.o
fs/locks.o: fs/locks.c fs/locks.h
	$(CC) $(CFLAGS) -o fs/locks.o -c fs/locks.c

#compilacao do ficheiro state.o
fs/state.o: fs/state.c fs/state.h fs/locks.h tecnicofs-api-constants.h
	$(CC) $(CFLAGS) -o fs/state.o -c fs/state.c

#compilacao do ficheiro operations.o
fs/operations.o: fs/operations.c fs/operations.h fs/state.h tecnicofs-api-constants.h
	$(CC) $(CFLAGS) -o fs/operations.o -c fs/operations.c

#compilacao do ficehiro tecnicofs-server
tecnicofs-server.o: tecnicofs-server.c fs/operations.h fs/state.h fs/locks.h tecnicofs-api-constants.h
	$(CC) $(CFLAGS) -o tecnicofs-server.o -c tecnicofs-server.c

tecnicofs-server: tecnicofs-server.o fs/operations.o fs/state.o fs/locks.o
	$(LD) $(CFLAGS) $(LDFLAGS) -o tecnicofs-server tecnicofs-server.o fs/operations.o fs/state.o fs/locks.o

run: tecnicofs-server
	./tecnicofs-server 2 /tmp/server

clean:
	@echo Cleaning...
	rm -f fs/*.o *.o tecnicofs-server