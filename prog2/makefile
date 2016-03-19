CC=clang
CFLAGS=-c -Wall -g

all: strassen

strassen: matrix.o main.o matrixMultiplication.o
	$(CC) matrix.o main.o matrixMultiplication.o -o strassen

matrixMultiplication.o: matrixMultiplication.c
	$(CC) $(CFLAGS) matrixMultiplication.c

matrix.o: matrix.c
	$(CC) $(CFLAGS) matrix.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm *.o strassen