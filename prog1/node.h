/**
 *	node.h
 *
 *	Implements a disjoint set data structure
 *
 */

typedef struct node {
    int value;
    struct node* parent;
    int rank;
} node;

// Creates a new node with the value x
node *makeSet(int x);

// Finds the root of the tree that n is in
node *find(node *n);

// Joins tress containing nodes x and y
void join(node *x, node *y);

// Frees the memory that n points to
void destroySet(node *n);