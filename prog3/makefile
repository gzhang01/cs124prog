CC=clang
CFLAGS=-c -Wall -g

all: kk

kk: heap.o main.o solution.o
	$(CC) heap.o main.o solution.o -o kk

heap.o: heap.c
	$(CC) $(CFLAGS) heap.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

solution.o: solution.c
	$(CC) $(CFLAGS) solution.c

clean:
	rm *.o kk