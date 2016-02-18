/**
 *	randmst.c
 *
 *	Generates a minimum spanning tree using Kruskal's algorithm
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <math.h>
#include "creategraph.h"
#include "node.h"

void generateMST(int n, int d, int edges, edge *graph[n * (n - 1) / 2], edge *mst[n - 1]);
void mergeSort(edge *tree[], int l, int r);
void merge(edge *tree[], int l, int m, int r);
void printMST(int n, edge *mst[n - 1]);
float getMaxWeight(int n, edge *mst[n - 1]);
void calculateAvgWeight(int flag, int n, int trials, int d, float* totalWeight);

// Generating a minimum spanning tree
// Inputs:	n - number of vertices
// 			d - dimension of vertex. if 0, then random edge lengths
//          edges - number of edges in graph
//          graph - complete graph of given number of vertices
//			mst - pointer to array of edges making up MST
// Output: no return value; generated tree stored in mst
// NOTE: tree is not preserved
void generateMST(int n, int d, int edges, edge *graph[n * (n - 1) / 2], edge *mst[n - 1]) {
    // Sorts edges by weight
    mergeSort(graph, 0, edges - 1);

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

    assert(foundEdges == n - 1);

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

// Gets maximum edge weight in MST for finding k(n)
float getMaxWeight(int n, edge *mst[n]) {
    float maxWeight = 0;
    for (int i = 0; i < n; i++) {
        if (mst[i]->length > maxWeight)
            maxWeight = mst[i]->length;
    }
    return maxWeight;
}

// Calculate Average Weight of MST with n points
void calculateAvgWeight(int flag, int n, int trials, int d, float* totalWeight) {
    for (int trial = 0; trial < trials; trial++) {
        
        if (flag == 4 || flag == 5) { printf("Trial %i\n", trial); }
        // Space for complete graph and MST
        int cap = n;
        edge **graph = malloc(cap * sizeof(edge*));
        edge **mst = malloc((n - 1) * sizeof(edge*));
        time_t start = time(NULL);

        // Create graph
        int edges = generateGraph(n, d, &cap, &graph);
        time_t graphDone = time(NULL);
        if (flag == 4) { printf("Time to generate graph: %li\n", graphDone - start); }

        // Create MST
        generateMST(n, d, edges, graph, mst);
        time_t mstDone = time(NULL);
        if (flag == 4) { printf("Time to generate MST: %li\n", mstDone - graphDone); }

        if (flag == 0 || flag == 4 || flag == 5) {
            // Find weight of tree
            float weight = 0;
            for (int i = 0; i < n - 1; i++) {
                weight += mst[i]->length;
            }
            *totalWeight += weight;
        } else if (flag == 1) {
            // Find total weight of tree
            float maxWeight = getMaxWeight(n - 1, mst);
            *totalWeight += maxWeight;
        } else if (flag == 2) {
            // Find maxWeight of tree
            float maxWeight = getMaxWeight(n - 1, mst);
            if (maxWeight > *totalWeight) {
                *totalWeight = maxWeight;
            }
        }

        // Destroys graph
        destroyGraph(edges, graph);
        free(graph);
        free(mst);

        time_t end = time(NULL);

        if (flag == 4) {
            printf("Time to free memory: %li\n", end - mstDone);
            printf("Total trial runtime: %li\n\n", end - start);
        }
    }
}



int main(int argc, char *argv[]) {
    time_t start = time(NULL);

    // Obtain info from command line
    int flag = (int) strtol(argv[1], NULL, 10);
	int n = (int) strtol(argv[2], NULL, 10);
	int trials = (int) strtol(argv[3], NULL, 10);
    int d = (int) strtol(argv[4], NULL, 10);

    if (argc != 5 && (flag == 0 || flag == 4)) {
        printf("Usage: ./randmst 0 numpoints numtrials dimension\n");
        return 1;
    }

    if ((flag == 1 || flag == 2) && argc != 7) {
        printf("Usage: ./randmst (1/2) numpoints numtrials dimension start mult\n");
        return 1;
    }

    float total_weight = 0;

    // This is used to Calculate Average Weight of MST with n numpoints
    // flag 4: include time information
    if (flag == 0 || flag == 4) {
        calculateAvgWeight(flag, n, trials, d, &total_weight);

        // Prints out desired info
        printf("%f %i %i %i\n", total_weight / trials, n, trials, d);
    }

    // This is used for estimating k(n)
    // flag 1: Calculate average max weight of edge of MST from 2 to n for all dimensions
    // flag 2: Calculate absolute max weight of edge in all trials
    else if (flag == 1 || flag == 2) {
        int start = (int) strtol(argv[5], NULL, 10);
        int multiple = (int) strtol(argv[6], NULL, 10);

        // File to store data in
        char *file = (flag == 1) ? "data/knt100avg_new.csv" : "data/knt100max_new.csv";

        // Store Average Max Weight in Output File
        FILE *fp;

        for (int numpoints = start; numpoints <= n; numpoints += multiple) {
            printf("%i\n", numpoints);
            float maxWeight[5] = {0};
            for (int dim = 0; dim <= 4; dim++) {
                if (dim == 1) {
                    continue;
                }
                calculateAvgWeight(flag, numpoints, trials, dim, &maxWeight[dim]);
            }

            fp = fopen(file, "a");
            // Print Average Max Weight of MSTs to Output File
            if (flag == 1) {
                fprintf(fp, "%3i,%.4f,%.4f,%.4f,%.4f\n", numpoints, maxWeight[0] / trials, maxWeight[2] / trials, maxWeight[3] / trials, maxWeight[4] / trials);
            } else if (flag == 2) {
                fprintf(fp, "%3i,%.4f,%.4f,%.4f,%.4f\n", numpoints, maxWeight[0], maxWeight[2], maxWeight[3], maxWeight[4]);
            }  
            fclose(fp);     
        } 
    }

    // This is used for running algorithm for 2^n numpoints from n=4 to 16 
    else if (flag == 5) {
        // File to store data in
        char *file = "data/output.csv";
        FILE *fp;
        fp = fopen(file, "w");
        fputs("numpoints,dim,trials,avgweight\n", fp);
        fclose(fp);
        fp = fopen(file, "a");

        for (int dim = 0; dim <= 4; dim++) {
            if (dim == 1) {
                continue;
            }
            printf("Dimension %i\n", dim);
            for (int i = 4; i <= 16; i++) {
                printf("Numpoints %i\n", (int) pow(2,i));
                calculateAvgWeight(flag, (int) pow(2,i), trials, dim, &total_weight);
                
                // Prints to Output File
                fprintf(fp, "%i,%i,%i,%f\n", n, dim, trials, total_weight / trials);
            }
            
        }

        fclose(fp); 

    }

    time_t end = time(NULL);

    if (flag == 4) {
        printf("total program runtime: %li\n", end - start);
    }
}