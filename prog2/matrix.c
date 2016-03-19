/**
 *	matrix.c
 *	
 *	Implements basic operations with matrices
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

#define NUMSPLIT 4

matrix* generateRandomMatrix(int r, int c);
matrix* createMatrix(int r, int c);
void freeMatrix(matrix* mtx);
int getElement(matrix* mtx, int i, int j);
void setElement(matrix* mtx, int i, int j, int e);
void checkElement(matrix* mtx, int i, int j);
int getRows(matrix* mtx);
int getCols(matrix* mtx);
void splitMatrix(matrix** matrices, matrix* mtx);
void freeSplitMatrices(matrix** matrices);
void matrixAdd(matrix* s, matrix* m1, matrix* m2);
void matrixSubtract(matrix* s, matrix* m1, matrix* m2);
void matrixAddAsserts(matrix* s, matrix* m1, matrix* m2);
void printMatrix(matrix* mtx);


// Generates a random r by c matrix with entries 0, 1, or -1
matrix* generateRandomMatrix(int r, int c) {
	// Seed RNG
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand((unsigned) tv.tv_usec);

    // Generate random matrix by populating with -1, 0, 1
	matrix* mtx = createMatrix(r, c);
	for (int i = 0; i < r; i++) {
		for (int j = 0; j < c; j++) {
			int num = rand() % 3 - 1;
			setElement(mtx, i, j, num);
		}
	}
	return mtx;
}

// Creates a matrix with r rows and c columns
matrix* createMatrix(int r, int c) {
	matrix* mtx = malloc(sizeof(matrix));
	mtx->startRow = 0;
	mtx->startCol = 0;
	mtx->endRow = r;
	mtx->endCol = c;
	mtx->totalRow = r;
	mtx->totalCol = c;
	mtx->m = calloc(r * c, sizeof(int));
	return mtx;
}

// Frees matrix mtx
void freeMatrix(matrix* mtx) {
	free(mtx->m);
	free(mtx);
}

// Gets the element from matrix mtx at row i and column j
int getElement(matrix* mtx, int i, int j) {
	checkElement(mtx, i, j);
	return mtx->m[(i + mtx->startRow) * mtx->totalCol + j + mtx->startCol];
}

// Sets the element in matrix mtx at row i and column j to e
void setElement(matrix* mtx, int i, int j, int e) {
	checkElement(mtx, i, j);
	mtx->m[(i + mtx->startRow) * mtx->totalCol + j + mtx->startCol] = e;
}

// Basic checks regarding get/set elements
void checkElement(matrix* mtx, int i, int j) {
	assert (i < mtx->endRow - mtx->startRow && i >= 0 && "index out of bounds");
	assert (j < mtx->endCol - mtx->startCol && j >= 0 && "index out of bounds");
}

// Gets number of rows in matrix
int getRows(matrix* mtx) {
	return mtx->endRow - mtx->startRow;
}

// Gets number of columns in matrix
int getCols(matrix* mtx) {
	return mtx->endCol - mtx->startCol;
}

// Splits current matrix (mtx) of side length n into four submatrices of side length n / 2
// Stores result in matrix* array matrices
//		 	|  A   B  |
//	M -->	|		  |
//			|  C   D  |
void splitMatrix(matrix** matrices, matrix* mtx) {
	for (int i = 0; i < NUMSPLIT; i++) {
		matrices[i] = malloc(sizeof(matrix));

		// Total rows and array stay the same
		matrices[i]->m = mtx->m;
		matrices[i]->totalRow = mtx->totalRow;
		matrices[i]->totalCol = mtx->totalCol;
		
		// First two take upper half; second two take lower half
		if (i / 2 == 0) {
			matrices[i]->startRow = mtx->startRow;
			matrices[i]->endRow = mtx->startRow + (getRows(mtx)) / 2;
		} else {
			matrices[i]->startRow = mtx->startRow + (getRows(mtx)) / 2;
			matrices[i]->endRow = mtx->endRow;
		}

		// Evens take left half; odds take right half
		if (i % 2 == 0) {
			matrices[i]->startCol = mtx->startCol;
			matrices[i]->endCol = mtx->startCol + (getCols(mtx)) / 2;
		} else {
			matrices[i]->startCol = mtx->startCol + (getCols(mtx)) / 2;
			matrices[i]->endCol = mtx->endCol;
		}
	}
}

// Frees matrices allocated during split
void freeSplitMatrices(matrix** matrices) {
	for (int i = 0; i < NUMSPLIT; i++) {
		free(matrices[i]);
	}
}

// Adds two matrices (m1 + m2) and stores result in s
void matrixAdd(matrix* s, matrix* m1, matrix* m2) {
	// Matrix addition checks
	matrixAddAsserts(s, m1, m2);

	// Add elements individually
	for (int i = 0; i < getRows(m1); i++) {
		for (int j = 0; j < getCols(m1); j++) {
			setElement(s, i, j, getElement(m1, i, j) + getElement(m2, i, j));
		}
	}
}

// Subtracts two matrices (m1 - m2) and stores result in s
void matrixSubtract(matrix* s, matrix* m1, matrix* m2) {
	// Matrix addition checks
	matrixAddAsserts(s, m1, m2);

	// Subtract elements individually
	for (int i = 0; i < getRows(m1); i++) {
		for (int j = 0; j < getCols(m1); j++) {
			setElement(s, i, j, getElement(m1, i, j) - getElement(m2, i, j));
		}
	}
}

// Sanity checks for matrix addition
void matrixAddAsserts(matrix* s, matrix* m1, matrix* m2) {
	assert (getRows(m1) == getRows(m2) && "Dimensions for matrix addition do not match!");
	assert (getCols(m1) == getCols(m2) && "Dimensions for matrix addition do not match!");
	assert (getRows(m1) == getRows(s) && "Dimensions for matrix addition do not match!");
	assert (getCols(m1) == getCols(s) && "Dimensions for matrix addition do not match!");
}


// Pretty prints matrix to console
void printMatrix(matrix* mtx) {
	for (int i = 0; i < mtx->endRow - mtx->startRow; i++) {
		for (int j = 0; j < mtx->endCol - mtx->startCol; j++) {
			printf("%3i", getElement(mtx, i, j));
		}
		printf("\n");
	}
	printf("\n");
}


