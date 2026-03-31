#ifndef EDGELIST_H
#define EDGELIST_H

#include <stdio.h>
#include <stdlib.h>

/*
 * Define structure EDGE of linked list node
 * from   - index of source vertex
 * to     - index of destination vertex
 * weight - weight of the edge
 * next   - pointer to the next edge node
 */
typedef struct edgenode {
  int from;
  int to;
  int weight;
  struct edgenode *next;
} EDGENODE;

/*
 * Define structure EDGELIST of edge list graph DS
 * size  - number of edges
 * start - pointer to the first edge node
 * end   - pointer to the last edge node
 */
typedef struct edgelist {
  int size;
  EDGENODE *start;
  EDGENODE *end;
} EDGELIST;

EDGELIST *new_edgelist(void);
void insert_edge_start(EDGELIST *g, int from, int to, int weight);
void insert_edge_end(EDGELIST *g, int from, int to, int weight);
void delete_edge(EDGELIST *g, int from, int to);
int weight_edgelist(EDGELIST *g);
void clean_edgelist(EDGELIST **gp);
void display_edgelist(EDGELIST *g);

#endif