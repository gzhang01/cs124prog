/**
 *	creategraph.h
 *
 *	Generates complete, undirected graphs
 *
 */

typedef struct {
	int p1;
	int p2;
	float length;
} edge;

// Generates a graph with n vertices in adjacency matrix form
// Input: 	n - number of vertices
// 			d - dimension of vertex. if 0, then random edge lengths
//			graph - pointer to edge array containing all edges in graph
// Output: no return value; generated graph stored in graph
void generateGraph(int n, int d, edge* graph[n * (n - 1) / 2]);

// Frees all memory allocated in graph
// Input:   n - number of vertices
//          graph - array of (n C 2) edges
void destroyGraph(int n, edge* graph[n * (n - 1) / 2]);

// Pretty prints the graph to stdout for testing
// Prints in matrix form (bottom triangular)
// NOTE: should not be used for large values of n!
// Input:   n - number of vertices
//          graph - array of (n C 2) edges
void printGraph(int n, edge* graph[n * (n - 1) / 2]);
