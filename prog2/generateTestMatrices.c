/**
 *	generateTestMatrices.c
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
#include "matrix.h"
#include "matrixMultiplication.h"


int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: ./gen dim\n");
		return 1;
	}

	// Creating test matrices
	int dim = (int) strtol(argv[1], NULL, 10);
	matrix* matrices[2];
	matrices[0] = generateRandomMatrix(dim);
	matrices[1] = generateRandomMatrix(dim);

	// Create file name
	char filename[20];
	sprintf(filename, "testfiles/t%d.txt", dim);
	
	// Open file
	FILE* f = fopen(filename, "w");

	// Write in matrices
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < dim; j++) {
			for (int k = 0; k < dim; k++) {
				fprintf(f, "%d", getElement(matrices[i], j, k));
				if (i != 1 || j != dim - 1 || k != dim - 1) {
					fprintf(f, "\n");
				}
			}
		}
	}

	// Close file
	fclose(f);

	freeMatrix(matrices[0]);
	freeMatrix(matrices[1]);

}