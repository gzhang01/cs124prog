/**
 *	heap.c
 *	
 *	Implements a max heap
 *
 *	@author: George Zhang
 *	Harvard University, CS124
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include "heap.h"

heap* createHeap(int capacity);
int getSize(heap* h);
void insert(heap* h, int64_t v);
int64_t pop(heap* h);
void freeHeap(heap* h);
void maxHeapify(heap* h, int i);
void swap(int64_t* a, int64_t* b);
int getLeftChild(heap* h, int i);
int getRightChild(heap* h, int i);
int getParent(heap* h, int i);
void printHeap(heap* h);

// Creates a heap with given capacity
heap* createHeap(int capacity) {
	heap* h = malloc(sizeof(heap));
	h->arr = calloc(capacity, sizeof(int64_t));
	h->size = 0;
	h->capacity = capacity;
	return h;
}

// Gets size of heap
int getSize(heap* h) {
	return h->size;
}

// Inserts value v to heap h
void insert(heap* h, int64_t v) {
	// If size has reached capacity, expand array
	if (h->size >= h->capacity) {
		h->arr = realloc(h->arr, h->capacity * 2);
		h->capacity *= 2;
	}

	// Insert v and keep track of index of v
	h->arr[h->size] = v;
	int i = h->size;
	h->size++;

	// Move to appropriate position through swaps
	while (i != 0 && h->arr[getParent(h, i)] < h->arr[i]) {
		swap(&(h->arr[getParent(h, i)]), &(h->arr[i]));
		i = getParent(h, i);
	}
}

// Pops off the max element in the heap
int64_t pop(heap* h) {
	assert(h->size != 0);
	h->size--;
	int64_t max = h->arr[0];

	// Assign last node to root and reheapify
	h->arr[0] = h->arr[h->size];
	maxHeapify(h, 0);

	return max;
}

// Frees heap
void freeHeap(heap* h) {
	free(h->arr);
	free(h);
}

// Rearranges heap rooted at index i to be a max heap
// Requires children of i to each be a max heap
void maxHeapify(heap* h, int i) {
	// Get left, right children
	int left = getLeftChild(h, i);
	int right = getRightChild(h, i);

	// Find largest element of root, left, and right
	int largest = i;
	if (left != -1 && h->arr[left] > h->arr[largest]) {
		largest = left;
	}
	if (right != -1 && h->arr[right] > h->arr[largest]) {
		largest = right;
	}

	// If root is not largest, swap
	if (largest != i) {
		swap(&(h->arr[i]), &(h->arr[largest]));
		maxHeapify(h, largest);
	}
}

// Swaps two values in heap
void swap(int64_t* a, int64_t* b) {
	int64_t tmp = *a;
	*a = *b;
	*b = tmp;
}

// Gets left child of node at index i
int getLeftChild(heap* h, int i) {
	return (2 * i + 1 <= h->capacity) ? 2 * i + 1 : -1;
}

// Gets right child of node at index i
int getRightChild(heap* h, int i) {
	return (2 * i + 2 <= h->capacity) ? 2 * i + 2 : -1;
}

// Gets parent of node at index i
int getParent(heap* h, int i) {
	return (i == 0) ? -1 : (i - 1) / 2;
}

// Pretty prints the heap as an array
void printHeap(heap* h) {
	for (int i = 0; i < h->size; i++) {
		printf("%lld ", h->arr[i]);
	}
	printf("\n");
}
