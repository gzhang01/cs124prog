CC=clang
CFLAGS=-c -Wall

all: creategraph

creategraph: creategraph.o
	$(CC) creategraph.o -o creategraph

creategraph.o: creategraph.c
	$(CC) $(CFLAGS) creategraph.c

clean: 
	rm *.o creategraph