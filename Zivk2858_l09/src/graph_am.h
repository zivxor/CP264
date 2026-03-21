/** @file  graph_am.h
 * Undirected Adjacency Matrix Graph Representation
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 * DO NOT CHANGE CONTENTS
 */
#ifndef GRAPH_AM_H_
#define GRAPH_AM_H_

// ==============================================================================================
// Includes

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ==============================================================================================
// Structures

/**
 * Stores edges of adjacency matrix values.
 */
typedef struct {
/** row vertex */
    int row;
/** column vertex */
    int col;
} graph_am_edge;

/**
 * Adjacency Matrix Graph header.
 */
typedef struct {
/** size (width/height) of adjacency matrix */
    int size;
/** pointer to 2D array of values */
    int *values;
} graph_am;

//==================================================================================
// Prototypes

/**
 * Initializes an adjacency matrix graph.
 *
 * @param size - height/width of the graph matrix
 */
graph_am* graph_am_initialize(int size);

/**
 * Frees the contents of an adjacency matrix graph.
 *
 * @param source - pointer to a graph
 */
void graph_am_free(graph_am **source);

/**
 * Adds an edge to source. Fails if vertex values invalid or edge already in source.
 * edges containing row < 0 or row >= size are ignored;
 * edges containing col < 0 or col >= size are ignored;
 * edges containing row == col are a loop and are given a value of 2;
 * All other edges are given a value of 1 in [row][col] and [col][row].
 *
 * @param source - pointer to a graph
 * @param edge - pointer to edge to add to source
 * @return - true if the edge was added, false otherwise
 */
bool graph_am_add_edge(graph_am *source, const graph_am_edge *edge);

/**
 * Removes an edge from source. Fails if edge values invalid or edge not in source.
 * edges containing row < 0 or row >= size are ignored;
 * edges containing col < 0 or col >= size are ignored;
 *
 * @param source - pointer to a graph
 * @param edge - pointer to edge to remove from source
 * @return - true if edge removed, false otherwise
 */
bool graph_am_remove_edge(graph_am *source, const graph_am_edge *edge);

/**
 * Creates a graph from an array of edges.
 * edges containing row < 0 or row >= size are ignored;
 * edges containing col < 0 or col >= size are ignored;
 * edges containing row == col are a loop and is given a value of 2;
 * All other edges are given a value of 1 in [row][col] and [col][row].
 * The resulting matrix is symmetrical.
 *
 * @param size - height/width of the graph matrix
 * @param edges - array of edges
 * @param count - number of values in edges
 * @return - a new graph
 */
graph_am* graph_am_create(int size, const graph_am_edge *edges, int count);

/**
 * Returns an array of all vertices connected to a vertex.
 * vertices must be defined with a size of source->size.
 *
 * @param source - pointer to a graph
 * @param vertex - index of a vertex
 * @param vertices - array of neighbours to vertex
 * @param count - number of vertices
 */
void graph_am_connected(const graph_am *source, int vertex, int vertices[], int *count);

/**
 * Returns number of vertices connected to vertex.
 *
 * @param source - pointer to a graph
 * @param vertex - index of a vertex
 * @return - number of vertices connected to vertex
 */
int graph_am_degree(const graph_am *source, int vertex);

/**
 * Performs a breadth-first traversal of a graph.
 *
 * @param source - pointer to a graph
 * @param vertex - index of vertex to start traversal from
 * @param vertices - array of resulting vertices
 * @param count - number of items in vertices
 */
void graph_am_breadth_traversal(const graph_am *source, int vertex, int vertices[], int *count);

/**
 * Performs a depth-first traversal of a graph.
 *
 * @param source - pointer to a graph
 * @param vertex - index of vertex to start traversal from
 * @param vertices - array of resulting vertices
 * @param count - number of items in vertices
 */
void graph_am_depth_traversal(const graph_am *source, int vertex, int vertices[], int *count);

/**
 * FOR TESTING
 * Prints the contents of an adjacency matrix graph.
 *
 * @param source - pointer to a graph
 */
void graph_am_print(const graph_am *source);

#endif /* GRAPH_AM_H_ */
