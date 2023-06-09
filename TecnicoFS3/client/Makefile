# Makefile, versao 1
# Sistemas Operativos, DEI/IST/ULisboa 2020-21
# Client

CC   = gcc
LD   = gcc
CFLAGS =-pthread -g -Wall -std=gnu99 -I../
LDFLAGS=-lm -lpthread

# A phony target is one that is not really the name of a file
# https://www.gnu.org/software/make/manual/html_node/Phony-Targets.html
.PHONY: all clean

all: tecnicofs-client

tecnicofs-client: tecnicofs-client-api.o tecnicofs-client.o
	$(LD) $(CFLAGS) $(LDFLAGS) -o tecnicofs-client tecnicofs-client-api.o tecnicofs-client.o

tecnicofs-client.o: tecnicofs-client.c ../tecnicofs-api-constants.h tecnicofs-client-api.h
	$(CC) $(CFLAGS) -o tecnicofs-client.o -c tecnicofs-client.c

tecnicofs-client-api.o: tecnicofs-client-api.c ../tecnicofs-api-constants.h tecnicofs-client-api.h
	$(CC) $(CFLAGS) -o tecnicofs-client-api.o -c tecnicofs-client-api.c

run: tecnicofs-client
	./tecnicofs-client inputs/test1.txt /tmp/server

clean:
	@echo Cleaning...
	rm -f fs/*.o *.o tecnicofs-client
