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

void generateMST(int n, int d, edge *tree[n * (n - 1) / 2], edge *mst[n - 1]);
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
void generateMST(int n, int d, edge *tree[n * (n - 1) / 2], edge *mst[n - 1]) {
	int edges = n * (n - 1) / 2;
    printGraph(n, tree);

    // Sorts edges by weight
    mergeSort(tree, 0, edges - 1);

    // Initializes sets based on vertices
    node *sets[n];
    for (int i = 0; i < n; i++) {
        sets[i] = makeSet(i);
    }

    // Find edges of MST
    int foundEdges = 0;
    for (int i = 0; i < n; i++) {
        if (find(sets[tree[i]->p1]) != find(sets[tree[i]->p2])) {
            mst[foundEdges] = tree[i];
            join(sets[tree[i]->p1], sets[tree[i]->p2]);
            foundEdges++;
            if (foundEdges == n) {
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
void mergeSort(edge *tree[], int l, int r) {
    // Find middle element, sort both halves, and merge back together
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(tree, l, m);
        mergeSort(tree, m + 1, r);
        merge(tree, l, m, r);
    }
}

// Merges halves back together
void merge(edge *tree[], int l, int m, int r) {
    // Sizes of two halves
    int n1 = m - l + 1, n2 = r - m;

    // Temp arrays to hold halves
    edge *left[n1], *right[n2];

    // Copy halves of array into temp arrays
    for (int i = 0; i < n1; i++) {
        left[i] = tree[l + i];
    }
    for (int i = 0; i < n2; i++) {
        right[i] = tree[m + 1 + i];
    }

    // Merging halves back together
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (left[i]->length < right[j]->length) {
            tree[k] = left[i];
            i++;
        } else {
            tree[k] = right[j];
            j++;
        }
        k++;
    }

    // Adding in rest of left list, if any are left
    while (i < n1) {
        tree[k] = left[i];
        i++;
        k++;
    }

    // Adding in rest of right list, if any are left
    while (j < n2) {
        tree[k] = right[j];
        j++;
        k++;
    }
}

// Prints out info about MST for testing
// NOTE: Do not use with large values of n
void printMST(int n, edge *mst[n - 1]) {
    for (int i = 0; i < n; i++) {
        printf("Edge from %i to %i with length %.4f\n", mst[i]->p1, mst[i]->p2, mst[i]->length);
    }
}

int main(void) {
	int n = 5;
	int d = 0;
    int edges = n * (n - 1) / 2;
    edge *tree[edges];
    generateGraph(n, d, tree);
	edge *mst[n - 1];

	generateMST(n, d, tree, mst);

    printMST(n - 1, mst);



    // Destroys graph
    destroyGraph(n, tree);


}