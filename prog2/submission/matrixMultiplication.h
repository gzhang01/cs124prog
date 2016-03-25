/**
 *	matrixMultiplication.c
 *	
 *	Implements multiplication with matrices
 *
 *	@author: George Zhang
 *  @author: Daniel Chen
 *	Harvard University
 * 	CS124 - Prog 2
 *
 */


// Modified Strassen's algorithm -- use Strassen's until threshold t; then use standard
// Multiplies two matrices (m1 x m2) and puts result in matrix p
// NOTE: unexpected results will occur if p points to same matrix as m1, m2
void matrixMult(matrix* p, matrix* m1, matrix* m2, int t);

// Multiplies two matrices (m1 x m2) using standard matrix multiplication
// Puts result in matrix p
// NOTE: unexpected results may occur if p points to same matrix as m1, m2
void matrixMultiplicationStandard(matrix* p, matrix* m1, matrix* m2);

// Multiplies two matrices (m1 x m2) using Strassen's
// Puts result in matrix p
// NOTE: unexpected results will occur if p points to same matrix as m1, m2
// NOTE: currently works for powers of 2
void matrixMultiplicationStrassen(matrix* p, matrix* m1, matrix* m2, int t);
