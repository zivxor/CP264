/** @file  main.c
 * -------------------------------------
 * @author your name, your id, your email
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include "graph_am.h"

#define TEST_SIZE 6
#define GRAPH_AM_MAX 8

#define TST "===========================================\n"
#define SEP "-------------------------------------------\n"

#define BOOL_STR(x) ((x)?"true":"false")  // converts bool type to string

/**
 * FOR TESTING
 * Fill an array with edges of random row and column values for the creation
 * of an adjacency matrix graph.
 *
 * @param size - width/height of adjacency matrix
 * @param edges - array of row/column edges
 * @param count - size of edges
 */
void random_edges(int size, graph_am_edge *edges, int count) {
    // See the random number generator
    srand(time(NULL));

    for(int i = 0; i < count; i++) {
        edges[i].row = rand() % size;
        edges[i].col = rand() % size;
    }
    return;
}

/**
 * FOR TESTING
 * Prints array of integer.
 *
 * @param vertices
 * @param count
 */
void print_vertices(int *vertices, int count) {
    printf("{");

    for(int i = 0; i < count; i++) {
        printf("%d, ", vertices[i]);
    }
    printf("}");
}

void print_edges(graph_am_edge *edges, int count) {
    printf("{");

    for(int i = 0; i < count; i++) {
        printf("{%d, %d}, ", edges[i].row, edges[i].col);
    }
    printf("}");
}

static int edges_string(char *string, size_t size, const graph_am_edge *source, int count) {
    int len = snprintf(string, size, "{");
    // Write contents of edges array to a string
    for(int i = 0; i < count; i++) {
        len += snprintf(string + len, size - len, "{%d, %d}, ", source[i].row, source[i].col);
    }
    len += snprintf(string + len, size - len, "}");
    return len;
}

/**
 * Test the graph_am functions.
 */
void test_graph_am(void) {
    int len = 0;
    char string[200];
    graph_am_edge edges[TEST_SIZE];

    printf(TST);
    printf("Testing graph_am\n");
    printf(SEP);
    // Create an array of random edges
    random_edges(0, edges, 0);
    len = snprintf(string, sizeof string, "source = graph_am_create(%d, ", 0);
    len += edges_string(string + len, sizeof string - len, edges, 0);
    len = snprintf(string + len, sizeof string - len, ", %d)\n", 0);
    printf("%s", string);
    graph_am *source = graph_am_create(0, edges, 0);
    graph_am_print(source);
    printf(SEP);
    // Create an array of random edges
    random_edges(GRAPH_AM_MAX, edges, TEST_SIZE);
    len = snprintf(string, sizeof string, "source = graph_am_create(%d, ", GRAPH_AM_MAX);
    len += edges_string(string + len, sizeof string - len, edges, TEST_SIZE);
    len = snprintf(string + len, sizeof string - len, ", %d)\n", TEST_SIZE);
    printf("%s\n", string);
    source = graph_am_create(GRAPH_AM_MAX, edges, TEST_SIZE);
    graph_am_print(source);
    printf(SEP);
    printf("Degrees of graph:\n\n");

    for(int i = 0; i < GRAPH_AM_MAX; i++) {
        int degree = graph_am_degree(source, i);
        printf("graph_am_degree(source, %d) -> %d\n", i, degree);
    }
    printf(SEP);
    printf("Connected Vertices:\n\n");

    for(int i = 0; i < GRAPH_AM_MAX; i++) {
        int vertices[GRAPH_AM_MAX];
        int count = 0;
        printf("graph_am_connected(source, %d, vertices, &count) -> ", i);
        graph_am_connected(source, i, vertices, &count);
        print_vertices(vertices, count);
        printf("\n");
    }
    printf(SEP);
    printf("Breadth First Traversal:\n\n");
    printf("Vertex Traversal\n");

    for(int i = 0; i < GRAPH_AM_MAX; i++) {
        int vertices[GRAPH_AM_MAX];
        int count = 0;
        printf("graph_am_breadth_traversal(source, %d, vertices, &count) -> ", i);
        graph_am_breadth_traversal(source, i, vertices, &count);
        print_vertices(vertices, count);
        printf("\n");
    }
    printf(SEP);
    printf("Depth First Traversal:\n\n");

    for(int i = 0; i < GRAPH_AM_MAX; i++) {
        int vertices[GRAPH_AM_MAX];
        int count = 0;
        printf("graph_am_depth_traversal(source, %d, vertices, &count) -> ", i);
        graph_am_depth_traversal(source, i, vertices, &count);
        print_vertices(vertices, count);
        printf("\n");
    }
    printf(SEP);
    printf("Remove vertices:\n\n");

    for(int i = 0; i < TEST_SIZE; i++) {
        bool removed = graph_am_remove_edge(source, &edges[i]);
        printf("removed = graph_am_remove_edge(source, {%d, %d}) -> %s\n", edges[i].row, edges[i].col,
                BOOL_STR(removed));
    }
    printf("\n");
    graph_am_edge edge = {5, 99};
    bool removed = graph_am_remove_edge(source, &edge);
    printf("removed = graph_am_remove_edge(source, {%d, %d}) -> %s\n\n", edge.row, edge.col, BOOL_STR(removed));
    graph_am_print(source);
    printf(SEP);

    for(int i = 0; i < TEST_SIZE; i++) {
        bool added = graph_am_add_edge(source, &edges[i]);
        printf("added = graph_am_add_edge(source, {%d, %d}) -> %s\n", edges[i].row, edges[i].col, BOOL_STR(added));
    }
    printf("\n");
    bool added = graph_am_add_edge(source, &edge);
    printf("added = graph_am_add_edge(source, {%d, %d}) -> %s\n\n", edge.row, edge.col, BOOL_STR(added));
    graph_am_print(source);
}

/**
 * @param argc - unused
 * @param argv - unused
 * @return EXIT_SUCCESS
 */
int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    test_graph_am();
    return (EXIT_SUCCESS);
}
