/**
 *	matrix.h
 *	
 *	Implements basic operations with matrices
 *
 *	@author: George Zhang
 *	Harvard University
 * 	CS124 - Prog 2
 *
 */

 typedef struct matrix {
 	int startRow;
 	int startCol;
 	int rows;
 	int cols;
 	int* m;
 } matrix; 

// Generates a random r by c matrix with entries 0, 1, or -1
matrix* generateRandomMatrix(int r, int c);

// Creates a matrix with r rows and c columns
matrix* createMatrix(int r, int c);

// Frees matrix mtx
void freeMatrix(matrix* mtx);

// Gets the element from matrix mtx at row i and column j
int getElement(matrix* mtx, int i, int j);

// Sets the element in matrix mtx at row i and column j to e
void setElement(matrix* mtx, int i, int j, int e);

// Pretty prints matrix to console
void printMatrix(matrix* mtx);

// Multiplies two matrices (m1 x m2) using standard matrix multiplication
// Puts result in matrix p
// NOTE: unexpected results may occur if p points to same matrix as m1, m2
void matrixMultiplicationStandard(matrix* p, matrix* m1, matrix* m2);



