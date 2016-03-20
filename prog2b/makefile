CC=clang
CFLAGS=-c -Wall -g

all: strassen

strassen: prog2trace.o
	$(CC) prog2trace.o -o strassen

prog2trace.o: prog2trace.c
	$(CC) $(CFLAGS) prog2trace.c

clean:
	rm *.o strassen