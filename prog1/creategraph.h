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
// Output: returns number of edges created; generated graph stored in graph
int generateGraph(int n, int d, edge* graph[n * (n - 1) / 2]);

// Frees all memory allocated in graph
// Input:   edges - number of edges
//          graph - array of (n C 2) edges
void destroyGraph(int edges, edge* graph[]);

// Pretty prints the graph to stdout for testing
// Prints in matrix form (bottom triangular)
// NOTE: should not be used for large values of n!
// Input:   edges - number of edges
//          graph - array of (n C 2) edges
void printGraph(int n, edge* graph[]);
