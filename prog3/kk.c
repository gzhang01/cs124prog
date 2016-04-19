/**
 *	kk.c
 *	
 *	Implementation of Karmarkar-Karp algorithm using max heap
 *
 *	@author: George Zhang
 *	Harvard University, CS124
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "heap.h"
#include "solution.h"

#define MAX_ITER 10


// Returns residue based on Karmarkar-Karp algorithm for array nums of length n
uint64_t kk(uint64_t* nums, int n) {
	// Initialize heap
	heap* h = createHeap(n);
	for (int i = 0; i < n; i++) {
		insert(h, nums[i]);
	}

	// Run algorithm
	while (getSize(h) > 1) {
		insert(h, pop(h) - pop(h));
	}

	// Return final element
	return pop(h);
}

// Calculates residue for a sequence solution
uint64_t sequenceResidue(uint64_t* nums, int* s, int n) {
	int64_t residue = 0;
	for (int i = 0; i < n; i++) {
		residue += s[i] * nums[i];
	}
	return (residue < 0) ? -1 * residue : residue;
}

// Calculates residue for a prepartition solution
uint64_t partitionResidue(uint64_t* nums, int* s, int n) {
	// Calculate new numbers based on prepartition
	uint64_t* newNums = calloc(n, sizeof(uint64_t));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (s[j] == i) {
				newNums[i] += nums[j];
			}
		}
	}

	// Get residue
	uint64_t residue = kk(newNums, n);
	free(newNums);
	return residue;
}

// Uses repeated random to find a solution to number partition
int* repeatedRandom(uint64_t* nums, int* start, int n, int isSequence) {
	int* s = malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		s[i] = start[i];
	}

	if (isSequence) {
		uint64_t bestResidue = sequenceResidue(nums, s, n);
		for (int i = 0; i < MAX_ITER; i++) {
			// Obtain random solution
			int* randomSolution = sequenceGenerate(n);
			uint64_t residue = sequenceResidue(nums, randomSolution, n);

			// If better, replace
			if (residue < bestResidue) {
				bestResidue = residue;
				free(s);
				s = randomSolution;
			} else {
				free(randomSolution);
			}
		}
	} else {
		uint64_t bestResidue = partitionResidue(nums, s, n);
		for (int i = 0; i < MAX_ITER; i++) {
			// Obtain random solution
			int* randomSolution = partitionGenerate(n);
			uint64_t residue = partitionResidue(nums, randomSolution, n);

			// If better, replace
			if (residue < bestResidue) {
				bestResidue = residue;
				free(s);
				s = randomSolution;
			} else {
				free(randomSolution);
			}
		}
	}

	return s;
}


int main(void) {
	 uint64_t arr[10] = {26, 19, 34, 22, 56, 11, 20, 3};
	// printf("%lld\n", kk(arr, 8));

	int n = 8;
	int* s = partitionGenerate(n);
	printSolution(s, n);
	printf("%lld\n", partitionResidue(arr, s, n));
	int* better = repeatedRandom(arr, s, n, 0);
	printSolution(better, n);
	printf("%lld\n", partitionResidue(arr, better, n));
	free(s);
	free(better);
	
	
}