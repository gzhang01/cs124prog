CC=clang
CFLAGS=-c -Wall -g

all: kk

kk: heap.o kk.o
	$(CC) heap.o kk.o -o kk

heap.o: heap.c
	$(CC) $(CFLAGS) heap.c

kk.o: kk.c
	$(CC) $(CFLAGS) kk.c

clean:
	rm *.o kk