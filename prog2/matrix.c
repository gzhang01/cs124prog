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

matrix* generateRandomMatrix(int r, int c);
matrix* createMatrix(int r, int c);
void freeMatrix(matrix* mtx);
int getElement(matrix* mtx, int i, int j);
void setElement(matrix* mtx, int i, int j, int e);
void printMatrix(matrix* mtx);
void matrixMultiplicationStandard(matrix* p, matrix* m1, matrix* m2);


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
	mtx->rows = r;
	mtx->cols = c;
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
	assert (i < mtx->rows && "index out of bounds");
	assert (j < mtx->cols && "index out of bounds");
	return mtx->m[i * mtx->cols + j];
}

// Sets the element in matrix mtx at row i and column j to e
void setElement(matrix* mtx, int i, int j, int e) {
	assert (i < mtx->rows && "index out of bounds");
	assert (j < mtx->cols && "index out of bounds");
	mtx->m[i * mtx->cols + j] = e;
}

// Pretty prints matrix to console
void printMatrix(matrix* mtx) {
	for (int i = 0; i < mtx->rows; i++) {
		for (int j = 0; j < mtx->cols; j++) {
			printf("%3i", getElement(mtx, i, j));
		}
		printf("\n");
	}
	printf("\n");
}

// Multiplies two matrices (m1 x m2) using standard matrix multiplication
// Puts result in matrix p
// NOTE: unexpected results may occur if p points to same matrix as m1, m2
void matrixMultiplicationStandard(matrix* p, matrix* m1, matrix* m2) {
	assert (m1->cols == m2->rows && "Matrix dimensions do not match!");
	for (int i = 0; i < m1->rows; i++) {
		for (int j = 0; j < m1->cols; j++) {
			for (int k = 0; k < m2->cols; k++) {
				setElement(p, i, k, getElement(p, i, k) + getElement(m1, i, j) * getElement(m2, j, k));
			}
		}
	}
}





