/**
 *  kk.c
 *  
 *  Implementation of Karmarkar-Karp algorithm using max heap
 *
 *  @author: George Zhang
 *  Harvard University, CS124
 *
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include "heap.h"
#include "solution.h"

#define MAX_ITER 25000


// Returns residue based on Karmarkar-Karp algorithm for array nums of length n
uint64_t kk(uint64_t* nums, int n) {
    // Initialize heap
    heap* h = createHeap(n);
    for (int i = 0; i < n; i++) {
        insert(h, nums[i]);
    }

    // Run algorithm
    while (getSize(h) > 1) {
        insert(h, pop(h) - pop(h));
    }

    // Return final element
    uint64_t residue = pop(h);
    freeHeap(h);
    return residue;
}

// Calculates residue for a sequence solution
uint64_t sequenceResidue(uint64_t* nums, int* s, int n) {
    int64_t residue = 0;
    for (int i = 0; i < n; i++) {
        residue += s[i] * nums[i];
    }
    return (residue < 0) ? -1 * residue : residue;
}

// Calculates residue for a prepartition solution
uint64_t partitionResidue(uint64_t* nums, int* s, int n) {
    // Calculate new numbers based on prepartition
    uint64_t* newNums = calloc(n, sizeof(uint64_t));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (s[j] == i) {
                newNums[i] += nums[j];
            }
        }
    }

    // Get residue
    uint64_t residue = kk(newNums, n);
    free(newNums);
    return residue;
}

// Uses repeated random to find a solution to number partition
uint64_t repeatedRandom(uint64_t* nums, int* start, int n, int isSequence) {
    // Keep track of s; can't use passed in pointer (mutable)
    int* s = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        s[i] = start[i];
    }

    if (isSequence) {
        uint64_t bestResidue = sequenceResidue(nums, s, n);
        for (int i = 0; i < MAX_ITER; i++) {
            // Obtain random solution
            int* randomSolution = sequenceGenerate(n);
            uint64_t residue = sequenceResidue(nums, randomSolution, n);

            // If better, replace
            if (residue < bestResidue) {
                bestResidue = residue;
                free(s);
                s = randomSolution;
            } else {
                free(randomSolution);
            }

            // Write results
            // FILE* f = fopen("data/rrs.csv", "a");
            // if (f == NULL) {
            //     printf("Could not open rrs.csv\n");
            //     return -1;
            // }
            // fprintf(f, "%i,%llu,%llu\n", i, bestResidue, residue);
            // fclose(f);
        }
        free(s);
        return bestResidue;
    } else {
        uint64_t bestResidue = partitionResidue(nums, s, n);
        for (int i = 0; i < MAX_ITER; i++) {
            // Obtain random solution
            int* randomSolution = partitionGenerate(n);
            uint64_t residue = partitionResidue(nums, randomSolution, n);

            // If better, replace
            if (residue < bestResidue) {
                bestResidue = residue;
                free(s);
                s = randomSolution;
            } else {
                free(randomSolution);
            }

                        // Write results
            // FILE* f = fopen("data/rrp.csv", "a");
            // if (f == NULL) {
            //     printf("Could not open rrp.csv\n");
            //     return -1;
            // }
            // fprintf(f, "%i,%llu,%llu\n", i, bestResidue, residue);
            // fclose(f);
        }
        free(s);
        return bestResidue;
    }
}

// Uses hill climbing to find a solution
uint64_t hillClimbing(uint64_t* nums, int* start, int n, int isSequence) {
    // Keep track of s; can't use passed in pointer (mutable)
    int* s = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        s[i] = start[i];
    }

    if (isSequence) {
        uint64_t bestResidue = sequenceResidue(nums, s, n);
        for (int i = 0; i < MAX_ITER; i++) {
            // Get neighbor
            int* neighbor = sequenceNeighbor(s, n);
            uint64_t residue = sequenceResidue(nums, neighbor, n);

            // If better, replace
            if (residue < bestResidue) {
                bestResidue = residue;
                free(s);
                s = neighbor;
            } else {
                free(neighbor);
            }

            // Write results
            // FILE* f = fopen("data/hcs.csv", "a");
            // if (f == NULL) {
            //     printf("Could not open hcs.csv\n");
            //     return -1;
            // }
            // fprintf(f, "%i,%llu,%llu\n", i, bestResidue, residue);
            // fclose(f);
        }
        free(s);
        return bestResidue;
    } else {
        uint64_t bestResidue = partitionResidue(nums, s, n);
        for (int i = 0; i < MAX_ITER; i++) {
            // Obtain random solution
            int* neighbor = partitionNeighbor(s, n);
            uint64_t residue = partitionResidue(nums, neighbor, n);

            // If better, replace
            if (residue < bestResidue) {
                bestResidue = residue;
                free(s);
                s = neighbor;
            } else {
                free(neighbor);
            }

            // Write results
            // FILE* f = fopen("data/hcp.csv", "a");
            // if (f == NULL) {
            //     printf("Could not open hcp.csv\n");
            //     return -1;
            // }
            // fprintf(f, "%i,%llu,%llu\n", i, bestResidue, residue);
            // fclose(f);
        }
        free(s);
        return bestResidue;
    }
}

// Cooling function for simulated annealing
double cooling(int iter) {
    return pow(10, 10) * pow(0.8, iter / 300);
}

// Uses simulated annealing to find a solution
uint64_t simulatedAnnealing(uint64_t* nums, int* start, int n, int isSequence) {
    // Keep track of s and bestS; can't use passed in pointer (mutable)
    int* s = malloc(sizeof(int) * n);
    int* bestS = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        s[i] = start[i];
        bestS[i] = start[i];
    }


    if (isSequence) {
        uint64_t sResidue = sequenceResidue(nums, s, n);
        uint64_t bestResidue = sequenceResidue(nums, bestS, n);
        for (int i = 0; i < MAX_ITER; i++) {
            // Get neighbor
            int* neighbor = sequenceNeighbor(s, n);
            uint64_t residue = sequenceResidue(nums, neighbor, n);

            // If better or within probability, replace
            if (residue < sResidue || (double) rand() / RAND_MAX < exp((int64_t) (sResidue - residue) / cooling(i))) {
                sResidue = residue;
                free(s);
                s = neighbor;
            } else {
                free(neighbor);
            }

            // Reassign best solution
            if (sResidue < bestResidue) {
                bestResidue = sResidue;
                for (int j = 0; j < n; j++) {
                    bestS[j] = s[j];
                }
            }

            // Write results
            // FILE* f = fopen("data/sas.csv", "a");
            // if (f == NULL) {
            //     printf("Could not open sas.csv\n");
            //     return -1;
            // }
            // fprintf(f, "%i,%llu,%llu,%llu\n", i, bestResidue, sResidue, residue);
            // fclose(f);
        }
        free(s);
        free(bestS);
        return bestResidue;
    } else {
        uint64_t sResidue = partitionResidue(nums, s, n);
        uint64_t bestResidue = partitionResidue(nums, bestS, n);
        for (int i = 0; i < MAX_ITER; i++) {
            // Get neighbor
            int* neighbor = partitionNeighbor(s, n);
            uint64_t residue = partitionResidue(nums, neighbor, n);

            // If better or within probability, replace
            if (residue < sResidue || (double) rand() / RAND_MAX < exp((int64_t) (sResidue - residue) / cooling(i))) {
                sResidue = residue;
                free(s);
                s = neighbor;
            } else {
                free(neighbor);
            }

            // Reassign best solution
            if (sResidue < bestResidue) {
                bestResidue = sResidue;
                for (int j = 0; j < n; j++) {
                    bestS[j] = s[j];
                }
            }

            // Write results
            // FILE* f = fopen("data/sap.csv", "a");
            // if (f == NULL) {
            //     printf("Could not open sap.csv\n");
            //     return -1;
            // }
            // fprintf(f, "%i,%llu,%llu,%llu\n", i, bestResidue, sResidue, residue);
            // fclose(f);
        }
        free(s);
        free(bestS);
        return bestResidue;
    }
}

// Generate random 64 bit numbers
uint64_t getNum() {
    uint64_t num = (uint64_t) rand() << 32 | rand();
    return num % (uint64_t) pow(10, 12) + 1;
}

void runSample() {
    // Getting random numbers
    int n = 100;
    uint64_t* nums = malloc(sizeof(uint64_t) * n);
    for (int i = 0; i < n; i++) {
        nums[i] = getNum();
    }

    // Generate sequence and partition (same result)
    int* s = sequenceGenerate(n);
    int* p = partitionGenerate(n);

    // Results and times
    uint64_t results[9];
    struct timeval times[10];
    gettimeofday(&times[0], NULL);
    results[0] = kk(nums, n);
    gettimeofday(&times[1], NULL);
    results[1] = sequenceResidue(nums, s, n);
    gettimeofday(&times[2], NULL);
    results[2] = partitionResidue(nums, p, n);
    gettimeofday(&times[3], NULL);
    results[3] = repeatedRandom(nums, s, n, 1);
    gettimeofday(&times[4], NULL);
    results[4] = repeatedRandom(nums, p, n, 0);
    gettimeofday(&times[5], NULL);
    results[5] = hillClimbing(nums, s, n, 1);
    gettimeofday(&times[6], NULL);
    results[6] = hillClimbing(nums, p, n, 0);
    gettimeofday(&times[7], NULL);
    results[7] = simulatedAnnealing(nums, s, n, 1);
    gettimeofday(&times[8], NULL);
    results[8] = simulatedAnnealing(nums, p, n, 0);
    gettimeofday(&times[9], NULL);

    // Difference between times
    int diff[9];
    for (int i = 0; i < 9; i++) {
        diff[i] = (int) ((1000000 * (times[i + 1].tv_sec - times[i].tv_sec) + (times[i + 1].tv_usec - times[i].tv_usec)) / 1000);
    }

    // Writing data and times to file
    FILE* f = fopen("data/data.csv", "a");
    if (f == NULL) {
        printf("Error opening file\n");
        return;
    }
    fprintf(f, "%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld,%lld\n", results[0], results[1], results[2], results[3], results[4], results[5], results[6], results[7], results[8]);
    fclose(f);

    f = fopen("data/times.csv", "a");
    if (f == NULL) {
        printf("Error opening file\n");
        return;
    }
    fprintf(f, "%i,%i,%i,%i,%i,%i,%i,%i,%i\n", diff[0], diff[1], diff[2], diff[3], diff[4], diff[5], diff[6], diff[7], diff[8]);
    fclose(f);

    // Free all allocated pointers
    free(nums);
    free(s);
    free(p);
}

void part2() {
    // Seed RNG
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand((unsigned) tv.tv_usec);

    // Wiping any existing data
    // FILE* f = fopen("data/data.csv", "w");
    // if (f == NULL) {
    //     printf("Error opening file\n");
    //     return;
    // }
    // fclose(f);
    // f = fopen("data/times.csv", "w");
    // if (f == NULL) {
    //     printf("Error opening file\n");
    //     return;
    // }
    // fclose(f);

    // Collect data 50 times
    for (int i = 0; i < 50; i++) {
        printf("%i\n", i);
        runSample();
        break;
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: ./kk inputfile\n");
        return 1;
    }

    char* file = argv[1];
    int n = 100;

    // Read numbers from file
    FILE* f = fopen(file, "r");
    if (f == NULL) {
        printf("Could not open file\n");
        return 1;
    }

    // Input numbers into array nums
    uint64_t* nums = malloc(sizeof(uint64_t) * n);
    char* line = NULL;
    size_t read, len, i = 0;
    while ((read = getline(&line, &len, f)) != -1) {
        nums[i] = strtoull(line, NULL, 10);
        i++;
    }
    
    fclose(f);

    printf("%llu\n", kk(nums, n));
    free(nums);

    // part2();
    
    
}