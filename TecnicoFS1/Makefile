# Makefile, versao 1
# Sistemas Operativos, DEI/IST/ULisboa 2020-21

CC   = gcc
LD   = gcc
CFLAGS = -Wall -std=gnu99 -I../ -g
LDFLAGS = -lm -pthread	#Flag para compilar com threads

# A phony target is one that is not really the name of a file
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY: all clean

all: tecnicofs



#TECNICOFS:
#compilacao do ficheiro locks.o
fs/locks.o: fs/locks.c fs/locks.h
	$(CC) $(CFLAGS) -o fs/locks.o -c fs/locks.c

#compilacao do ficheiro state.o
fs/state.o: fs/state.c fs/state.h fs/locks.h tecnicofs-api-constants.h
	$(CC) $(CFLAGS) -o fs/state.o -c fs/state.c

#compilacao do ficheiro operations.o
fs/operations.o: fs/operations.c fs/operations.h fs/state.h tecnicofs-api-constants.h
	$(CC) $(CFLAGS) -o fs/operations.o -c fs/operations.c

#compilacao do ficheiro main.o
main.o: main.c fs/operations.h fs/state.h fs/locks.h tecnicofs-api-constants.h
	$(CC) $(CFLAGS) -o main.o -c main.c

#criacao do ficheiro executavel tecnicofs
tecnicofs: fs/locks.o fs/state.o fs/operations.o main.o
	$(LD) $(CFLAGS) $(LDFLAGS) -o tecnicofs fs/locks.o fs/state.o fs/operations.o main.o

clean:
	@echo Cleaning...
	rm -f fs/*.o *.o *.txt tecnicofs
