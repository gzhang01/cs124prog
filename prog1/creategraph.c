/**
 *	creategraph.c
 *
 *	Generates complete, undirected graphs in adjacency matrix form
 *
 * 	@author: George Zhang
 *	Harvard University - CS124
 *	Spring 2016
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void generateGraph(int n, int d, float graph[n][n]);
void generate0d(int n, float graph[n][n]);
void generate234d(int n, int d, float graph[n][n]);
void printGraph(int n, float graph[n][n]);
float randFloat();
float distance(int d, float p1[d], float p2[d]);
float square(float n);

// Generates a graph with n vertices in adjacency matrix form
// Input: 	n - number of vertices
// 			d - dimension of vertex. if 0, then random edge lengths
//			graph - pointer to 2D array to store edge values
// Output: no return value; generated graph stored in graph
void generateGraph(int n, int d, float graph[n][n]) {
	// initialize RNG
	srand((unsigned) time(NULL));

	// Generate graph
	if (d == 0) {
		generate0d(n, graph);
	} else {
		generate234d(n, d, graph);
	}
}

// Creates graph of n vertices, where weight of each edge is in [0, 1]
// Stores result in graph
void generate0d(int n, float graph[n][n]) {
	// Fill diagonal of graph (should all be zero)
	for (int i = 0; i < n; i++) {
		graph[i][i] = 0;
	}

	// Fill rest of graph
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			float tmp = randFloat();
			graph[i][j] = tmp;
			graph[j][i] = tmp;
		}
	}
}

// Generates graph in adjacency matrix form for n vertices initialized
// in d dimensions
void generate234d(int n, int d, float graph[n][n]) {
	// Keep track of vertices. Each row is single vertex with dimensionality d
	float vertices[n][d];

	// Initialize vertices
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < d; j++) {
			vertices[i][j] = randFloat();
			printf("%f ", vertices[i][j]);
		}
		printf("\n");
	}

	// Fill diagonal of graph (should all be zero)
	for (int i = 0; i < n; i++) {
		graph[i][i] = 0;
	}

	// Calculates distances between vertices for graph
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			float dist = distance(d, vertices[i], vertices[j]);
			graph[i][j] = dist;
			graph[j][i] = dist;
		}
	}
}

// Prints the graph to stdout for testing
// NOTE: should not be used for large values of n!
void printGraph(int n, float graph[n][n]) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%.4f ", graph[i][j]);
		}
		printf("\n");
	}
}

// Generates a random float from 0 to 1
float randFloat() {
	return (float) rand() / (float) RAND_MAX;
}

// Calculates distance between two points p1, p2 with dimensionality d
float distance(int d, float p1[d], float p2[d]) {
	float sum = 0;

	for (int i = 0; i < d; i++) {
		sum += square(p1[i] - p2[i]);
	}

	return sqrt(sum);
}

// Calculates square of number n
float square(float n) {
	return n * n;
}

int main(void) {
	int n = 4;
	int d = 0;
	float graph[n][n];

	generateGraph(n, d, graph);

	printGraph(n, graph);
}



