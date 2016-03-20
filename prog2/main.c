/**
 *	main.c
 *
 *	Runs the implementation of modified Strassen's algorithm
 *
 *	@author: George Zhang
 *  @author: Daniel Chen
 *	Harvard University
 *	CS124 Prog 2
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrix.h"
#include "matrixMultiplication.h"

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("Usage: ./strassen 0 dimension inputfile\n");
		return 1;
	}

	// Threshold
	int t = 1;

	// Get dimensions, padding and create matrices
	int dim = (int) strtol(argv[2], NULL, 10);
	int pad = dim;
	matrix* mtx[2];
	mtx[0] = createMatrix(pad);
	mtx[1] = createMatrix(pad);

	// Populate matrices
	FILE* f = fopen(argv[3], "r");
	if (f == NULL) {
		printf("Could not open file\n");
		return 2;
	}

	char buf[11];
	for (int i = 0, n = dim * dim; i < 2 * n; i++) {
		fscanf(f, "%s\n", buf);
		setElement(mtx[i / n], (i % n) / dim, i % dim, (int) strtol(buf, NULL, 10));
	}

	fclose(f);

	// Compute matrix product
	matrix* p = createMatrix(pad);
	matrixMult(p, mtx[0], mtx[1], t);

	for (int i = 0; i < dim; i++) {
		printf("%i\n", getElement(p, i, i));
	}



	
	// time_t start = time(NULL);
	// time_t end = time(NULL);
	// printf("Total time: %ld\n", end - start);
}