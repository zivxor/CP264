#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

#define INFINITY 99999

/*
 * structure of adjacent linked list node
 * nid    -  to node id
 * weight -  edge weight
 * next   -  pointer to next adjnode
 */
typedef struct adjnode {
	int nid;
	int weight;
	struct adjnode *next;
} ADJNODE;

/*
 * structure of graph vertex node
 * nid      - graph vertex node id
 * name     - name or data of the node
 * neighbor - pointer to the linked list of neighbors
 */
typedef struct gnode {
	int nid;
	char name[10];
	ADJNODE *neighbor;
} GNODE;

/*
 * structure of adjacent list graph
 * order - number of nodes
 * size  - number of edges
 * nodes - array of GNODE pointers
 */
typedef struct graph {
	int order;
	int size;
	GNODE **nodes;
} GRAPH;

GRAPH *new_graph(int n);
void insert_edge_graph(GRAPH *g, int from, int to, int weight);
void delete_edge_graph(GRAPH *g, int from, int to);
int get_edge_weight(GRAPH *g, int from, int to);
void traverse_bforder(GRAPH *g, int start);
void traverse_dforder(GRAPH *g, int start);
void display_graph(GRAPH *g);
void clean_graph(GRAPH **gp);

#endif
