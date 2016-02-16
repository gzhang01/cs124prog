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
#include "mst.h"

void generateMST(int n, int d, edge *mst[n - 1]);
void mergeSort(edge *tree[], int l, int r);
void merge(edge *tree[], int l, int m, int r);

// Generating a minimum spanning tree
// Inputs:	n - number of vertices
// 			d - dimension of vertex. if 0, then random edge lengths
//			mst - pointer to array of edges making up MST
// Output: no return value; generated tree stored in mst
void generateMST(int n, int d, edge *mst[n - 1]) {
	// Gets the entire starting tree
	int edges = n * (n - 1) / 2;
	edge *tree[edges];
	generateGraph(n, d, tree);
    printGraph(n, tree);

    // mergeSort(tree, 0, edges);
    
    printGraph(n, tree);

    destroyGraph(n, tree);
}

// Will probably need to implement iterative merge sort!

// // Sorts section of array with index in range [l, r)
// void mergeSort(edge *tree[], int l, int r) {
//     // Find middle element, sort both halves, and merge back together
//     if (l < r) {
//         printf("Here %i, %i\n", l, r);
//         int m = l + (r - l) / 2;
//         mergeSort(tree, l, m);
//         mergeSort(tree, m + 1, r);
//         merge(tree, l, m, r);
//     }
// }

// // Merges halves back together
// void merge(edge *tree[], int l, int m, int r) {
//     // Sizes of two halves
//     int n1 = m - l + 1, n2 = r - m;

//     // Temp arrays to hold halves
//     edge *left[n1], *right[n2];

//     // Copy halves of array into temp arrays
//     for (int i = 0; i < n1; i++) {
//         left[i] = tree[l + i];
//     }
//     for (int i = 0; i < n2; i++) {
//         right[i] = tree[m + 1 + i];
//     }

//     // Merging halves back together
//     int i = 0, j = 0, k = l;
//     while (i < n1 && j < n2) {
//         if (left[i]->length < right[j]->length) {
//             tree[k] = left[i];
//             i++;
//         } else {
//             tree[k] = right[j];
//             j++;
//         }
//         k++;
//     }

//     // Adding in rest of left list, if any are left
//     while (i < n1) {
//         tree[k] = left[i];
//         i++;
//         k++;
//     }

//     // Adding in rest of right list, if any are left
//     while (j < n2) {
//         tree[k] = right[j];
//         j++;
//         k++;
//     }
// }

int main(void) {
	int n = 10;
	int d = 0;
	edge *tree[n - 1];

	generateMST(n, d, tree);

	// printGraph(n, graph);


}