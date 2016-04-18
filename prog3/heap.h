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
	uint64_t* arr;
	int size;
	int capacity;
} heap;

// Creates a heap with given capacity
heap* createHeap(int capacity);
// Gets size of heap
int getSize(heap* h);
// Inserts value v to heap h
void insert(heap* h, uint64_t v);
// Pops off the max element in the heap
uint64_t pop(heap* h);
// Frees heap
void freeHeap(heap* h);
// Pretty prints the heap as an array
void printHeap(heap* h);