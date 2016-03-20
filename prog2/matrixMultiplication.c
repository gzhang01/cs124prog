/**
 *	matrixMultiplication.c
 *	
 *	Implements multiplication with matrices
 *
 *	@author: George Zhang
 *	Harvard University
 * 	CS124 - Prog 2
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <assert.h>
#include "matrix.h"
#include "matrixMultiplication.h"

#define NUMSPLIT 4

void matrixMult(matrix* p, matrix* m1, matrix* m2, int t);
void matrixMultiplicationStandard(matrix* p, matrix* m1, matrix* m2);
void matrixMultiplicationStrassen(matrix* p, matrix* m1, matrix* m2, int t);
void matrixMultiplicationAsserts(matrix* p, matrix* m1, matrix* m2);


// Modified Strassen's algorithm -- use Strassen's until threshold t; then use standard
// Multiplies two matrices (m1 x m2) and puts result in matrix p
// NOTE: unexpected results will occur if p points to same matrix as m1, m2
void matrixMult(matrix* p, matrix* m1, matrix* m2, int t) {
	matrixMultiplicationAsserts(p, m1, m2);

	// If one dimension reaches threshold, use traditional
	if (getRows(m1) <= t || getCols(m1) <= t || getCols(m2) <= t) {
		matrixMultiplicationStandard(p, m1, m2);
		return;
	}

	// Getting split matrices
	matrix* matrices1[NUMSPLIT];
	matrix* matrices2[NUMSPLIT];
	splitMatrix(matrices1, m1);
	splitMatrix(matrices2, m2);

	printMatrix(m1);
	for (int i = 0; i < NUMSPLIT; i++) {
		printMatrix(matrices1[i]);
	}
	printMatrix(m2);
	for (int i = 0; i < NUMSPLIT; i++) {
		printMatrix(matrices2[i]);
	}

	freeSplitMatrices(matrices1);
	freeSplitMatrices(matrices2);
}

// Multiplies two matrices (m1 x m2) using standard matrix multiplication
// Puts result in matrix p
// NOTE: unexpected results will occur if p points to same matrix as m1, m2
void matrixMultiplicationStandard(matrix* p, matrix* m1, matrix* m2) {
	// Check dimensions of given matrices
	matrixMultiplicationAsserts(p, m1, m2);

	// Calculate product based on traditional matrix mult
	for (int i = 0; i < getRows(m1); i++) {
		for (int j = 0; j < getCols(m1); j++) {
			for (int k = 0; k < getCols(m2); k++) {
				setElement(p, i, k, getElement(p, i, k) + getElement(m1, i, j) * getElement(m2, j, k));
			}
		}
	}
}

// Multiplies two matrices (m1 x m2) using Strassen's
// Puts result in matrix p
// NOTE: unexpected results will occur if p points to same matrix as m1, m2
// NOTE: only works for powers of 2
void matrixMultiplicationStrassen(matrix* p, matrix* m1, matrix* m2, int t) {
	matrixMult(p, m1, m2, 1);
}

// Basic checks regarding matrix multiplication (correct dimensions, etc.)
void matrixMultiplicationAsserts(matrix* p, matrix* m1, matrix* m2) {
	assert (getCols(m1) == getRows(m2) && "Matrix dimensions do not match!");
	assert (getRows(p) == getRows(m1) && "Product matrix and input matrix dimensions do not match!");
	assert (getCols(p) == getCols(m2) && "Product matrix and input matrix dimensions do not match!");
}
