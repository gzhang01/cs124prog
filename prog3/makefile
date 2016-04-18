CC=clang
CFLAGS=-c -Wall -g

all: kk

kk: heap.o
	$(CC) heap.o -o kk

heap.o: heap.c
	$(CC) $(CFLAGS) heap.c

clean:
	rm *.o kk