/**
 *	solution.h
 *	
 *	Contains useful functions for manipulating solutions
 * 	for Number Partition problem
 *
 *	@author: George Zhang
 *	Harvard University, CS124
 *
 */

// Generates a random sequence of -1/+1 to denote solution set
// NOTE: need to free returned array
int* sequenceGenerate(int n);
// Produces a random neighbor of a sequence
// Returns mutated sequence
int* sequenceNeighbor(int* s, int n);
// Generates a random prepartitioning (using [0, n))
// NOTE: need to free returned array
int* partitionGenerate(int n);
// Produces a random neighbor of a sequence
// Returns mutated sequence
int* partitionNeighbor(int* s, int n);
// Converts a sequence solution into a partition solution
int* sequenceToPartition(int* s, int n);
// Prints set passed in, whether solution or prepartition
void printSolution(int* s, int n);