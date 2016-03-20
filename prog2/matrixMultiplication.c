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
#define SUB -1
#define ADD 1

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

	// Pieces for Strassen's (index 0 left blank) and temporary matrices from addition
	matrix* pt[8];
	for (int i = 1; i < 8; i++) {
		pt[i] = createMatrix(getRows(p) / 2);
	}
	matrix* tmp1 = createMatrix(getRows(p) / 2);
	matrix* tmp2 = createMatrix(getRows(p) / 2);

	// Calculating pieces
	matrixMult(pt[1], matrices1[0], matrixAdd(tmp1, matrices2[1], matrices2[3], SUB), t);
	matrixMult(pt[2], matrixAdd(tmp1, matrices1[0], matrices1[1], ADD), matrices2[3], t);
	matrixMult(pt[3], matrixAdd(tmp1, matrices1[2], matrices1[3], ADD), matrices2[0], t);
	matrixMult(pt[4], matrices1[3], matrixAdd(tmp1, matrices2[2], matrices2[0], SUB), t);
	matrixMult(pt[5], matrixAdd(tmp1, matrices1[0], matrices1[3], ADD), matrixAdd(tmp2, matrices2[0], matrices2[3], ADD), t);
	matrixMult(pt[6], matrixAdd(tmp1, matrices1[1], matrices1[3], SUB), matrixAdd(tmp2, matrices2[2], matrices2[3], ADD), t);
	matrixMult(pt[7], matrixAdd(tmp1, matrices1[0], matrices1[2], SUB), matrixAdd(tmp2, matrices2[0], matrices2[1], ADD), t);

	// Calculating final product
	// Manipulates dimensions and start to fill in quadrants
	p->dim = getRows(p) / 2;
	matrixAdd(p, pt[5], matrixAdd(tmp1, pt[4], matrixAdd(tmp2, pt[6], pt[2], SUB), ADD), ADD);
	p->startCol = p->dim;
	matrixAdd(p, pt[1], pt[2], ADD);
	p->startRow = p->dim;
	matrixAdd(p, pt[5], matrixAdd(tmp1, pt[1], matrixAdd(tmp2, pt[3], pt[7], ADD), SUB), ADD);
	p->startCol = 0;
	matrixAdd(p, pt[3], pt[4], ADD);
	p->startRow = 0;
	p->dim = getRows(p) * 2;

	// Freeing everything allocated
	freeMatrix(tmp1);
	freeMatrix(tmp2);
	for (int i = 1; i < 8; i++) {
		freeMatrix(pt[i]);
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
