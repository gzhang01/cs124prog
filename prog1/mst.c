/**
 *	randmst.c
 *
 *	Generates a minimum spanning tree using Kruskal's algorithm
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "creategraph.h"
#include "node.h"

void generateMST(int n, int d, edge *graph[n * (n - 1) / 2], edge *mst[n - 1]);
void mergeSort(edge *tree[], int l, int r);
void merge(edge *tree[], int l, int m, int r);
void printMST(int n, edge *mst[n - 1]);

// Generating a minimum spanning tree
// Inputs:	n - number of vertices
// 			d - dimension of vertex. if 0, then random edge lengths
//          tree - complete graph of given number of vertices
//			mst - pointer to array of edges making up MST
// Output: no return value; generated tree stored in mst
// NOTE: tree is not preserved
void generateMST(int n, int d, edge *graph[n * (n - 1) / 2], edge *mst[n - 1]) {
	int edges = n * (n - 1) / 2;
    // printGraph(n, graph);

    // Sorts edges by weight
    mergeSort(graph, 0, edges - 1);
    // printGraph(n, graph);

    // Initializes sets based on vertices
    node *sets[n];
    for (int i = 0; i < n; i++) {
        sets[i] = makeSet(i);
    }

    // Find edges of MST
    int foundEdges = 0;
    for (int i = 0; i < edges; i++) {
        // If roots are not the same, join them and add edge to MST
        if (find(sets[graph[i]->p1]) != find(sets[graph[i]->p2])) {
            mst[foundEdges] = graph[i];
            join(sets[graph[i]->p1], sets[graph[i]->p2]);
            foundEdges++;
            // Break if we've found n - 1 edges (num edges in MST)
            if (foundEdges == n - 1) {
                break;
            }
        }
    }

    // Destroy all sets created
    for (int i = 0; i < n; i++) {
        destroySet(sets[i]);
    }
}

// Sorts section of array with index in range [l, r)
void mergeSort(edge *graph[], int l, int r) {
    // Find middle element, sort both halves, and merge back together
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(graph, l, m);
        mergeSort(graph, m + 1, r);
        merge(graph, l, m, r);
    }
}

// Merges halves back together
void merge(edge *graph[], int l, int m, int r) {
    // Sizes of two halves
    int n1 = m - l + 1, n2 = r - m;

    // Temp arrays to hold halves
    edge **left = malloc(n1 * sizeof(edge*));
    edge **right = malloc(n2 * sizeof(edge*));

    // Copy halves of array into temp arrays
    for (int i = 0; i < n1; i++) {
        left[i] = graph[l + i];
    }

    for (int i = 0; i < n2; i++) {
        right[i] = graph[m + 1 + i];
    }

    // Merging halves back together
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i]->length < right[j]->length) {
            graph[k] = left[i];
            i++;
        } else {
            graph[k] = right[j];
            j++;
        }
        k++;
    }

    // Adding in rest of left list, if any are left
    while (i < n1) {
        graph[k] = left[i];
        i++;
        k++;
    }

    // Adding in rest of right list, if any are left
    while (j < n2) {
        graph[k] = right[j];
        j++;
        k++;
    }

    free(left);
    free(right);
}

// Prints out info about MST for testing
// NOTE: Do not use with large values of n
void printMST(int n, edge *mst[n - 1]) {
    for (int i = 0; i < n; i++) {
        printf("Edge from %i to %i with length %.4f\n", mst[i]->p1, mst[i]->p2, mst[i]->length);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Usage: ./randmst 0 numpoints numtrials dimension\n");
        return 1;
    }

    // Obtain info from command line
    // int flag = (int) strtol(argv[1], NULL, 10);
	int n = (int) strtol(argv[2], NULL, 10);
	// int trials = (int) strtol(argv[3], NULL, 10);
    int d = (int) strtol(argv[4], NULL, 10);

    // Space for complete graph and MST
    int edges = n * (n - 1) / 2;
    edge *graph[edges];
	edge *mst[n - 1];

    // Create graph and MST
    generateGraph(n, d, graph);
	generateMST(n, d, graph, mst);


    // printMST(n - 1, mst);



    // Destroys graph
    destroyGraph(n, graph);


}