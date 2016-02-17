/**
 *	creategraph.c
 *
 *	Generates complete, undirected graphs
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
#include "creategraph.h"

#define INDEX(i, j) (i - 1) * i / 2 + j

void generateGraph(int n, int d, edge *graph[n * (n - 1) / 2]);
void destroyGraph(int n, edge *graph[n * (n - 1) / 2]);
void printGraph(int n, edge *graph[n * (n - 1) / 2]);
void generate0d(int n, edge *graph[n * (n - 1) / 2]);
void generate234d(int n, int d, edge *graph[n * (n - 1) / 2]);
float randFloat();
float distance(int d, float p1[d], float p2[d]);
float square(float n);

// Generates a graph with n vertices in adjacency matrix form
// Input: 	n - number of vertices
// 			d - dimension of vertex. if 0, then random edge lengths
//			graph - pointer to edge array containing all edges in graph
// Output: no return value; generated graph stored in graph
void generateGraph(int n, int d, edge *graph[n * (n - 1) / 2]) {
	// initialize RNG with microsecond
    struct timeval tv;
    gettimeofday(&tv, NULL);
	srand((unsigned) tv.tv_usec);

	// Generate graph
	if (d == 0) {
		generate0d(n, graph);
	} else {
		generate234d(n, d, graph);
	}
}

// Frees all memory allocated in graph
// Input:   n - number of vertices
//          graph - array of (n C 2) edges
void destroyGraph(int n, edge *graph[n * (n - 1) / 2]) {
    int edges = n * (n - 1) / 2;
    for (int i = 0; i < edges; i++) {
        free(graph[i]);
    }
}

// Pretty prints the graph to stdout for testing
// Prints in matrix form (bottom triangular)
// NOTE: should not be used for large values of n!
// Input:   n - number of vertices
//          graph - array of (n C 2) edges
// Example: let n = 3
// Output:
//     0.5
//     0.1 0.3
//     0.2 0.4 0.6
// 0.5 = weight(0,1)
// 0.1 = weight(0,2)
// 0.3 = weight(1,2)
// 0.2 = weight(0,3)
// 0.4 = weight(1,3)
// 0.6 = weight(2,3)
void printGraph(int n, edge *graph[n * (n - 1) / 2]) {
    int edges = n * (n - 1) / 2;
    int count = 0, row = 1;
    for (int i = 0; i < edges; i++) {
        if (count == row) {
            printf("\n");
            count = 0;
            row++;
        }
        printf("%.4f ", graph[i]->length);
        count++;
    }
    printf("\n");
}

// Helper function
// Creates graph of n vertices, where weight of each edge is in [0, 1]
// Stores result in graph
void generate0d(int n, edge *graph[n * (n - 1) / 2]) {
    // Find all edges
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            edge *e = malloc(sizeof(edge));
            e->p1 = i;
            e->p2 = j;
            e->length = randFloat();
            graph[INDEX(i, j)] = e;
        }
    }
}

// Helper function
// Generates graph for n vertices initialized in d dimensions
void generate234d(int n, int d, edge *graph[n * (n - 1) / 2]) {
	// Keep track of vertices. Each row is single vertex with dimensionality d
	float vertices[n][d];

	// Initialize vertices
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < d; j++) {
			vertices[i][j] = randFloat();
		}
	}

    // Find all edges
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            edge *e = malloc(sizeof(edge));
            e->p1 = i;
            e->p2 = j;
            e->length = distance(d, vertices[i], vertices[j]);
            graph[INDEX(i, j)] = e;
        }
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

