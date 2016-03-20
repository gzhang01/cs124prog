/**
 *	testSuite.c
 *	
 *	Basic testSuite for matrix calculations
 *
 *	@author: George Zhang
 *	Harvard University
 * 	CS124 - Prog 2
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "matrix.h"
#include "matrixMultiplication.h"

void testBasics(void) {
	// Testing simple creation
	matrix* m = createMatrix(5, 3);
	assert(m->totalRow == 5);
	assert(m->totalCol == 3);
	for (int i = 0; i < getRows(m); i++) {
		for (int j = 0; j < getCols(m); j++) {
			assert(getElement(m, i, j) == 0);
		}
	}

	// Testing set element
	setElement(m, 1, 2, 5);
	assert(getElement(m, 1, 2) == 5);

	// Testing splitting matrix
	matrix* matrices[4];
	splitMatrix(matrices, m);
	assert(getRows(matrices[0]) == 2);
	assert(getRows(matrices[1]) == 2);
	assert(getRows(matrices[2]) == 3);
	assert(getRows(matrices[3]) == 3);
	assert(getCols(matrices[0]) == 1);
	assert(getCols(matrices[1]) == 2);
	assert(getCols(matrices[2]) == 1);
	assert(getCols(matrices[3]) == 2);
	assert(getElement(matrices[1], 1, 1) == 5);

	// Free allocated memory
	freeSplitMatrices(matrices);
	freeMatrix(m);
}

void testAdd(void) {
	// Create matrices
	matrix* m1 = generateRandomMatrix(5, 3);
	matrix* m2 = generateRandomMatrix(5, 3);
	matrix* s1 = createMatrix(5, 3);

	// Test addition
	matrixAdd(s1, m1, m2);
	for (int i = 0; i < getRows(s1); i++) {
		for (int j = 0; j < getCols(s1); j++) {
			assert(getElement(s1, i, j) == getElement(m1, i, j) + getElement(m2, i, j));
		}
	}

	// Test add when not using complete array
	matrix* s2 = createMatrix(4, 3);
	m1->startRow = 1;
	m2->endRow = 4;
	matrixAdd(s2, m1, m2);
	printMatrix(m1);
	printMatrix(m2);
	printMatrix(s2);
	for (int i = 0; i < getRows(s2); i++) {
		for (int j = 0; j < getCols(s2); j++) {
			assert(getElement(s2, i, j) == getElement(m1, i, j) + getElement(m2, i, j));
		}
	}
	m1->startRow = 0;
	m2->endRow = 5;
	assert(getElement(s2, 0, 0) == getElement(m1, 1, 0) + getElement(m2, 0, 0));

}

int main(void) {
	testBasics();
	testAdd();
}




