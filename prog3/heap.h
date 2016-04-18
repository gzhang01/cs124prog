/**
 *	heap.h
 *	
 *	Implements a max heap
 *
 *	@author: George Zhang
 *	Harvard University, CS124
 *
 */

#include <stdint.h>

typedef struct {
	int64_t* arr;
	int size;
	int capacity;
} heap;

// Creates a heap with given capacity
heap* createHeap(int capacity);
// Inserts value v to heap h
void insert(heap* h, int64_t v);
// Pops off the max element in the heap
int64_t pop(heap* h);
// Frees heap
void freeHeap(heap* h);