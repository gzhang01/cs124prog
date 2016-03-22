Daniel Chen, George Zhang
CS124 Programming Assignment 2
Harvard University
Spring 2016

Modified Strassen's Algorithm
Implemented a modified version of Strassen's Algorithm for multiplying matrices. Uses Strassen's Algorithm until size n_0, at which point switches to standard matrix multiplication algorithm. Experimentally determined n_0. 

Usage: ./strassen 0 dim filename
	dim - dimension of matrices
	filename - path to file containing matrices

Other flags available for usage:
	0 - expected output according to spec
	1 - outputs running time with no padding
	2 - outputs running time with semioptimized padding
	3 - outputs running time with optimized padding (not implemented)
	4 - generates datasets with threshold, time pairs

NOTE: before generate datasets, generate test matrix files
	usage: ./gen dim
		dim - dimension of matrices to be generated
	Saves result in testfiles/t####.txt according to spec (#### = dim)
CAUTION: not mean to be used with dim > 9999

To generate datasets with threshold, time pairs:
	usage: ./strassen 4 dim filename
		dim, filename will be overwritten during runtime
	Results stored in data/d####.csv (#### = dim)
Change line 112 to edit which dimensions to test, line 119 for different thresholds, and line 130 for different number of runs per dim/t pair