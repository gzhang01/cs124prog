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

int main(void) {
	matrix* m1 = generateRandomMatrix(800, 800);
	matrix* m2 = generateRandomMatrix(800, 800);
	// printMatrix(m1);
	// printMatrix(m2);

	matrix* p = createMatrix(800, 800);
	time_t start = time(NULL);
	matrixMultiplicationStandard(p, m1, m2);
	time_t end = time(NULL);
	// printMatrix(p);

	printf("Total time: %ld\n", end - start);

	freeMatrix(m1);
	freeMatrix(m2);
	freeMatrix(p);
}