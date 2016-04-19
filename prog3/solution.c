/**
 *	solution.c
 *	
 *	Contains useful functions for manipulating solutions
 * 	for Number Partition problem
 *
 *	@author: George Zhang
 *	Harvard University, CS124
 *
 */

#include <stdio.h>
#include <sys/time.h>
#include <stdint.h>
#include <stdlib.h>

// Generates a random sequence of -1/+1 to denote solution set
// NOTE: need to free returned array
int* sequenceGenerate(int n) {
	// Seed RNG
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand((unsigned) tv.tv_usec);

    // Allocate space for sequence
	int* s = malloc(sizeof(int) * n);

	// Assign randomly to sets
	for (int i = 0; i < n; i++) {
		int set = rand() & 1;
		s[i] = (set == 1) ? 1 : -1;
	}

	return s;
}

// Produces a random neighbor of a sequence
// Returns mutated sequence
int* sequenceNeighbor(int* s, int n) {
	// Produce neighbor
	int* neighbor = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		neighbor[i] = s[i];
	}

	// Change sequence
	int i = rand() % n;
	neighbor[i] = -neighbor[i];

	// Change second one with probability 0.5
	if ((double) rand() / RAND_MAX > 0.5) {
		int j = i;
		while (j == i) {
			j = rand() % n;
		}
		neighbor[j] = -neighbor[j];
	}

	return neighbor;
}

// Generates a random prepartitioning (using [0, n))
// NOTE: need to free returned array
int* partitionGenerate(int n) {
	// Seed RNG
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand((unsigned) tv.tv_usec);

    // Allocate space for sequence
    int* s = malloc(sizeof(int) * n);

    // Assign randomly to partition
    for (int i = 0; i < n; i++) {
    	s[i] = rand() % n;
    }

    return s;
}

// Produces a random neighbor of a sequence
// Returns mutated sequence
int* partitionNeighbor(int* s, int n) {
	// Produce neighbor
	int* neighbor = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		neighbor[i] = s[i];
	}

	// Produce neighbor
	int i = rand() % n;
	int j = neighbor[i];

	// Ensure that different number gets assigned
	while (j == neighbor[i]) {
		j = rand() % n;
	}

	neighbor[i] = j;

	return neighbor;
}

// Converts a sequence solution into a partition solution
int* sequenceToPartition(int* s, int n) {
	int* p = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		p[i] = (s[i] == 1) ? 1 : 0;
	}
	return p;
}

// Prints set passed in, whether solution or prepartition
void printSolution(int* s, int n) {
	for (int i = 0; i < n; i++) {
		printf("%4i ", s[i]);
	}
	printf("\n");
}