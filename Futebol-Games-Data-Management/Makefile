# The compiler: defined as gcc for C
CC = gcc

# compiler flags:
#  -g         - this flag adds debugging information to the executable file
#  -Wall      - this flag is used to turn on most compiler warnings
#  -Wextra    - this flag enables some extra warnings not turned on by -Wall
#  -Werror 	  - all warnings become errors
#  -ansi      - 
#  -pedantic  - this flag issues all warnings demanded by strict ISO C++ rules
CFLAGS = -Wall -Wextra -Werror -ansi -pedantic

.PHONY: all
all: main

# Debug rules
debug: CFLAGS += -g -fsanitize=address -DDEBUG
debug: all

# Executables
main: main.o lib.o
	$(CC) $(CFLAGS) -o $@ $^

main.o: main.c
	$(CC) $(CFLAGS) -c $<

# Libraries
lib.o: lib.c
	$(CC) $(CFLAGS) -c $<

# Rule to clean files
clean:
	rm -r *.o main foo*