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
 	int startRow;		// Start row in matrix
 	int startCol;		// Start column in matrix
 	int endRow;			// End row in matrix
 	int endCol;			// End column in matrix
 	int totalRow;		// Total number of rows in array
 	int totalCol;		// Total number of columns in array
 	int* m;				// 2D array of numbers
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

// Gets number of rows in matrix
int getRows(matrix* mtx);

// Gets number of columns in matrix
int getCols(matrix* mtx);

// Splits current matrix (mtx) of side length n into four submatrices of side length n / 2
// Stores result in matrix* array matrices
//		 	|  A   B  |
//	M -->	|		  |
//			|  C   D  |
void splitMatrix(matrix** matrices, matrix* mtx);

// Pretty prints matrix to console
void printMatrix(matrix* mtx);