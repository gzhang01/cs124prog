CC=clang
CFLAGS=-c -Wall -g

all: strassen

strassen: main.o matrix.o matrixMultiplication.o
	$(CC) main.o matrix.o matrixMultiplication.o -o strassen

test: testSuite.o matrix.o matrixMultiplication.o
	$(CC) testSuite.o matrix.o matrixMultiplication.o -o test

matrixMultiplication.o: matrixMultiplication.c
	$(CC) $(CFLAGS) matrixMultiplication.c

matrix.o: matrix.c
	$(CC) $(CFLAGS) matrix.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

testSuite.o: testSuite.c
	$(CC) $(CFLAGS) testSuite.c

clean:
	rm *.o strassen