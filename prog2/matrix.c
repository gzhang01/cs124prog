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

matrix* generateRandomMatrix(int d);
matrix* createMatrix(int d);
void freeMatrix(matrix* mtx);
int getElement(matrix* mtx, int i, int j);
void setElement(matrix* mtx, int i, int j, int e);
void checkElement(matrix* mtx, int i, int j);
int getRows(matrix* mtx);
int getCols(matrix* mtx);
void splitMatrix(matrix** matrices, matrix* mtx);
void freeSplitMatrices(matrix** matrices);
void matrixAdd(matrix* s, matrix* m1, matrix* m2, int f);
void matrixAddAsserts(matrix* s, matrix* m1, matrix* m2);
void printMatrix(matrix* mtx);


// Generates a random d by d matrix with entries 0, 1, or -1
matrix* generateRandomMatrix(int d) {
	// Seed RNG
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand((unsigned) tv.tv_usec);

    // Generate random matrix by populating with -1, 0, 1
	matrix* mtx = createMatrix(d);
	for (int i = 0; i < d; i++) {
		for (int j = 0; j < d; j++) {
			int num = rand() % 3 - 1;
			setElement(mtx, i, j, num);
		}
	}
	return mtx;
}

// Creates a matrix with side length d
matrix* createMatrix(int d) {
	matrix* mtx = malloc(sizeof(matrix));
	mtx->startRow = 0;
	mtx->startCol = 0;
	mtx->dim = d;
	mtx->m = malloc(sizeof(int*) * d);
	for (int i = 0; i < d; i++) {
		mtx->m[i] = calloc(d, sizeof(int));
	}
	return mtx;
}

// Frees matrix mtx
void freeMatrix(matrix* mtx) {
	for (int i = 0; i < mtx->dim; i++) {
		free(mtx->m[i]);
	}
	free(mtx->m);
	free(mtx);
}

// Gets the element from matrix mtx at row i and column j
int getElement(matrix* mtx, int i, int j) {
	checkElement(mtx, i, j);
	return mtx->m[mtx->startRow + i][mtx->startCol + j];
}

// Sets the element in matrix mtx at row i and column j to e
void setElement(matrix* mtx, int i, int j, int e) {
	checkElement(mtx, i, j);
	mtx->m[mtx->startRow + i][mtx->startCol + j] = e;
}

// Basic checks regarding get/set elements
void checkElement(matrix* mtx, int i, int j) {
	assert (i < getRows(mtx) && i >= 0 && "index out of bounds");
	assert (j < getCols(mtx) && j >= 0 && "index out of bounds");
}

// Gets number of rows in matrix
int getRows(matrix* mtx) {
	return mtx->dim;
}

// Gets number of columns in matrix
int getCols(matrix* mtx) {
	return mtx->dim;
}

// Splits current matrix (mtx) of side length n into four submatrices of side length n / 2
// Stores result in matrix* array matrices
//		 	|  A   B  |
//	M -->	|		  |
//			|  C   D  |
void splitMatrix(matrix** matrices, matrix* mtx) {
	for (int i = 0; i < NUMSPLIT; i++) {
		matrices[i] = malloc(sizeof(matrix));

		// Array stays the same
		matrices[i]->m = mtx->m;
		
		// Dimension halved
		matrices[i]->dim = mtx->dim / 2;
		
		// First two take upper half; second two take lower half
		if (i / 2 == 0) {
			matrices[i]->startRow = mtx->startRow;
		} else {
			matrices[i]->startRow = mtx->startRow + getRows(mtx) / 2;
		}

		// Evens take left half; odds take right half
		if (i % 2 == 0) {
			matrices[i]->startCol = mtx->startCol;
		} else {
			matrices[i]->startCol = mtx->startCol + getCols(mtx) / 2;
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
// Input f = 1 for addition, -1 for subtraction
void matrixAdd(matrix* s, matrix* m1, matrix* m2, int f) {
	// Matrix addition checks
	matrixAddAsserts(s, m1, m2);

	// Add elements individually
	for (int i = 0; i < getRows(m1); i++) {
		for (int j = 0; j < getCols(m1); j++) {
			setElement(s, i, j, getElement(m1, i, j) + f * getElement(m2, i, j));
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
	for (int i = 0; i < getRows(mtx); i++) {
		for (int j = 0; j < getCols(mtx); j++) {
			printf("%3i", getElement(mtx, i, j));
		}
		printf("\n");
	}
	printf("\n");
}


