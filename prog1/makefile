CC=clang
CFLAGS=-c -Wall -g

all: randmst

randmst: mst.o creategraph.o node.o
	$(CC) mst.o creategraph.o node.o -o randmst

mst.o: mst.c
	$(CC) $(CFLAGS) mst.c

creategraph.o: creategraph.c
	$(CC) $(CFLAGS) creategraph.c

node.o: node.c
	$(CC) $(CFLAGS) node.c

clean: 
	rm *.o randmst