/**
 *	node.c
 *
 *	Implements a disjoint set data structure
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "node.h"

node *makeset(int x);
node *find(node *n);
void join(node *x, node *y);
void link(node *x, node *y);

// Creates a node in the forest
node *makeset(int x) {
    node *n = malloc(sizeof(node));
    n->value = x;
    n->parent = n;
    n->rank = 0;
    return n;
}

// Finds the root element of the tree
node *find(node *n) {
    if (n != n->parent) {
        n->parent = find(n->parent);
    }
    return n->parent;
}

// Forms the union of sets containing x and y
void join(node *x, node *y) {
	link(find(x), find(y));
}

// Helper function
// Links two roots of trees
void link(node *x, node *y) {
	if (x->rank > y->rank) {
		return link(y, x);
	} else if (x->rank == y->rank) {
		y->rank++;
	}
	x->parent = y;
}