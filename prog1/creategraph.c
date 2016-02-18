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

int generateGraph(int n, int d, edge *graph[n * (n - 1) / 2]);
void destroyGraph(int edges, edge *graph[]);
void printGraph(int n, edge *graph[n * (n - 1) / 2]);
int generate0d(int n, float th, edge *graph[n * (n - 1) / 2]);
int generate234d(int n, int d, float th, edge *graph[n * (n - 1) / 2]);
float randFloat();
float distance(int d, float p1[d], float p2[d]);
float square(float n);
float threshold(int n, int d);

// Generates a graph with n vertices in adjacency matrix form
// Input: 	n - number of vertices
// 			d - dimension of vertex. if 0, then random edge lengths
//			graph - pointer to edge array containing all edges in graph
// Output: returns number of edges created; generated graph stored in graph
int generateGraph(int n, int d, edge *graph[n * (n - 1) / 2]) {
	// initialize RNG with microsecond
    struct timeval tv;
    gettimeofday(&tv, NULL);
	srand((unsigned) tv.tv_usec);

    // Obtain threshold
    float th = threshold(n, d);

	// Generate graph
	if (d == 0) {
		return generate0d(n, th, graph);
	} else {
		return generate234d(n, d, th, graph);
	}
}

// Frees all memory allocated in graph
// Input:   edges - number of edges
//          graph - array of (n C 2) edges
void destroyGraph(int edges, edge *graph[]) {
    for (int i = 0; i < edges; i++) {
        free(graph[i]);
    }
}

// Pretty prints the graph to stdout for testing
// Prints in matrix form (bottom triangular)
// NOTE: should not be used for large values of n!
// Input:   edges - number of edges
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
void printGraph(int edges, edge *graph[]) {
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
// Stores result in graph; returns number of edges added
int generate0d(int n, float th, edge *graph[n * (n - 1) / 2]) {
    int numEdges = 0;
    // Find all edges
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            // If value is greater than threshold, ignore it
            float val = randFloat();
            if (val > th) {
                continue;
            }
            edge *e = malloc(sizeof(edge));
            e->p1 = i;
            e->p2 = j;
            e->length = val;
            graph[numEdges] = e;
            numEdges++;
        }
    }
    return numEdges;
}

// Helper function
// Generates graph for n vertices initialized in d dimensions
int generate234d(int n, int d, float th, edge *graph[n * (n - 1) / 2]) {
	// Keep track of vertices. Each row is single vertex with dimensionality d
	float vertices[n][d];

	// Initialize vertices
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < d; j++) {
			vertices[i][j] = randFloat();
		}
	}

    int numEdges = 0;

    // Find all edges
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            // If individual axes difference greater than threshold, ignore
            for (int dim = 0; dim < d; dim++) {
                if (vertices[i][dim] - vertices[j][dim] > th) {
                    continue;
                }
            }

            // If distance between points greather than threshold, ignore
            float dist = distance(d, vertices[i], vertices[j]);
            if (dist > th) {
                continue;
            }

            edge *e = malloc(sizeof(edge));
            e->p1 = i;
            e->p2 = j;
            e->length = dist;
            graph[numEdges] = e;
            numEdges++;
        }
    }
    return numEdges;
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

// Calculates a threshold given n vertices and dimension d
// Values determined by experimental data
float threshold(int n, int d) {
    if (d == 0) {
        return 3.5 / (0.16799676 * n + 2.93108083);
    } else if (d == 2) {
        return 2.5 / (0.03520531 * n + 2.6599906);
    } else if (d == 3) {
        return 2.0 / (0.01392143 * n + 2.03798067);
    } else if (d == 4) {
        return 1.8 / (0.00761201 * n + 1.65815953);
    }

    // If given d is not valid, return -1 as error
    return -1;
}





