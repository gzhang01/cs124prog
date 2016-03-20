/**
 *	main.c
 *
 *	Runs the implementation of modified Strassen's algorithm
 *
 *	@author: George Zhang
 *	Harvard University
 *	CS124 Prog 2
 *
 */

#include <stdio.h>
#include <time.h>
#include "matrix.h"
#include "matrixMultiplication.h"

int main(void) {
	// Testing matrix multiplication
	// int row = 2;
	// int mid = 3;
	// int col = 2;

	// matrix* m1 = generateRandomMatrix(row, mid);
	// matrix* m2 = generateRandomMatrix(mid, col);
	// printMatrix(m1);
	// printMatrix(m2);

	// matrix* p = createMatrix(row, col);
	// time_t start = time(NULL);
	// matrixMultiplicationStandard(p, m1, m2);
	// time_t end = time(NULL);
	// printMatrix(p);

	// printf("Total time: %ld\n", end - start);

	// freeMatrix(m1);
	// freeMatrix(m2);
	// freeMatrix(p);


	// Testing splitting matrices
	int row = 3;
	int mid = 1;
	int col = 3;
	matrix* m1 = generateRandomMatrix(row, mid);
	matrix* m2 = generateRandomMatrix(mid, col);
	matrix* p = createMatrix(row, col);
	matrixMultiplicationStrassen(p, m1, m2);
	printMatrix(m1);
	printMatrix(m2);
	printMatrix(p);
	freeMatrix(m1);
	freeMatrix(m2);
	freeMatrix(p);
}