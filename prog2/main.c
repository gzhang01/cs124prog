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

// Flag args:
// 	0: expected behavior according to spec
//	1: Test with no padding
// 	2: Test with semioptimized padding
// 	3: Test with optimized padding **** Not Implemented ****
// 	4: Generate data with semioptimized padding
//	5: Collect data on run times of three algorithms
int getPad(int dim, int threshold, int flag) {
	if (flag == 0 || flag == 1) {
		return dim;
	} else if (flag == 2 || flag == 4 || flag == 5) {
		int tempdim = dim;
		while (tempdim > threshold) {
			tempdim = (tempdim + 1) / 2;
		}
		while (tempdim < dim) {
			tempdim = tempdim * 2;
		}
		return tempdim;
	}

	return -1;
}

// Run program given threshold t, dimension dim, total size of matrix pad, and flag
// Returns time taken to run
int runProg(int t, int dim, int pad, int flag, char* filename) {
	// Create matrices
	matrix* mtx[2];
	mtx[0] = createMatrix(pad);
	mtx[1] = createMatrix(pad);

	// Populate matrices
	FILE* f = fopen(filename, "r");
	if (f == NULL) {
		printf("Could not open file\n");
		return -1;
	}

	char buf[11];
	for (int i = 0, n = dim * dim; i < 2 * n; i++) {
		fscanf(f, "%s\n", buf);
		setElement(mtx[i / n], (i % n) / dim, i % dim, (int) strtol(buf, NULL, 10));
	}

	fclose(f);

	// Compute matrix product
	matrix* p = createMatrix(pad);
	time_t start = time(NULL);
	matrixMult(p, mtx[0], mtx[1], t);
	time_t end = time(NULL);

	// If flag is zero, then output according to spec
	// Otherwise, print out run time
	if (flag == 0) {
		for (int i = 0; i < dim; i++) {
			printf("%i\n", getElement(p, i, i));
		}
		printf("\n");
	} else {
		printf("Total time for threshold %i, dim %i: %ld\n", t, dim, end - start);
	}

	freeMatrix(mtx[0]);
	freeMatrix(mtx[1]);
	freeMatrix(p);

	return end - start;
}

int main(int argc, char* argv[]) {
	if (argc != 4) {
		printf("Usage: ./strassen 0 dimension inputfile\n");
		printf("Use 0 for expected behavior according to spec\n");
		printf("Use 1 for default file without padding\n");
		printf("Use 2 for semioptimized padding\n");
		printf("Use 3 for optimized padding\n");
		printf("Use 4 for generating data with semioptimized padding\n");
		return 1;
	}

	// Threshold
	int t = 40;

	// Get dimensions, flag, padding
	int dim = (int) strtol(argv[2], NULL, 10);
	int flag = (int) strtol(argv[1], NULL, 10);
	int pad = getPad(dim, t, flag);

	if (flag == 0 || flag == 1 || flag == 2 || flag == 3) {
		runProg(t, dim, pad, flag, argv[3]);
	} else if (flag == 4) {
		// Flag 4 generates data
		// Run with different dimensions
		for (int dim = 512; dim <= 512; dim *= 2) {
			// Get appropriate file
			// NOTE: must generate appropriate file first ("./gen dim" in terminal)
			char filename[20];
			sprintf(filename, "testfiles/t%d.txt", dim);

			// Location to place data
			char outfile[15];
			sprintf(outfile, "data/d%d.csv", dim);
			// Clear previous data
			FILE* f = fopen(outfile, "w");
			fclose(f);

			// Run for several thresholds
			for (int t = 20; t < 150; t += 5) {
				// Keep track of total running time
				int runTime = 0;
				int trials = 0;
				
				// Get padding
				pad = getPad(dim, t, flag);

				// Run for variable number of times
				// TODO: implement arrays of numbers to test with number times to run
				// 5 trials each for now
				for (int run = 0; run < 10; run++, trials++) {
					runTime += runProg(t, dim, pad, flag, filename);
				}

				// Adding datapoint to file
				FILE* f = fopen(outfile, "a");
				fprintf(f, "%i,%.3f\n", t, 1.0 * runTime / trials);
				fclose(f);
			}
		}	
	} else if (flag == 5) {
		// Run standard, Strassen's, and modified Strassen's
		char* infile = "testfiles/t2048.txt";
		char* outfile = "data/methodCompare.csv";

		for (int dim = 800; dim <= 1000; dim += 200) {
			int runTime[] = {0, 0, 0};
			int trials = 0;
			pad = getPad(dim, t, flag);


			for (int run = 0; run < 1; run++, trials++) {
				// Standard uses threshold = dim; no padding needed
				runTime[0] += runProg(dim, dim, dim, flag, infile);
				// Pure Strassen's uses threshold 1
				// runTime[1] += runProg(1, dim, getPad(dim, 1, flag), flag, infile);
				// Modified Strassen's
				runTime[2] += runProg(t, dim, pad, flag, infile);
			}

			// Adding datapoint to file
			FILE* f = fopen(outfile, "a");
			fprintf(f, "%i,%.3f,%.3f,%.3f\n", t, 1.0 * runTime[0] / trials, 1.0 * runTime[1] / trials, 1.0 * runTime[2] / trials);
			fclose(f);
		}
	} else {
		printf("Incorrect flag used\n");
		return 2;
	}

	return 0;
}