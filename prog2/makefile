CC=clang
CFLAGS=-c -Wall -g

all: strassen

strassen: matrix.o main.o
	$(CC) matrix.o main.o -o strassen

matrix.o: matrix.c
	$(CC) $(CFLAGS) matrix.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm *.o strassen