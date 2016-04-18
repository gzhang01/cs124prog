CC=clang
CFLAGS=-c -Wall -g

all: kk

kk: heap.o kk.o solution.o
	$(CC) heap.o kk.o solution.o -o kk

heap.o: heap.c
	$(CC) $(CFLAGS) heap.c

kk.o: kk.c
	$(CC) $(CFLAGS) kk.c

solution.o: solution.c
	$(CC) $(CFLAGS) solution.c

clean:
	rm *.o kk