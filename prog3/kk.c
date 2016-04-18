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
#include "heap.h"

// Returns residue based on Karmarkar-Karp algorithm for array nums of length n
uint64_t kk(uint64_t* nums, int n) {
	// Initialize heap
	heap* h = createHeap(n);
	for (int i = 0; i < n; i++) {
		insert(h, nums[i]);
	}

	while (getSize(h) > 1) {
		printHeap(h);
		insert(h, pop(h) - pop(h));
	}

	printHeap(h);
	return pop(h);
}


int main(void) {
	uint64_t arr[10] = {10, 15, 6, 5};
	printf("%lld\n", kk(arr, 4));
}