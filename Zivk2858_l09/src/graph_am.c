/** @file  graph_am.c
 * Adjacency Matrix Graph
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 */
#include "graph_am.h"

//==================================================================================
// Functions

graph_am *graph_am_initialize(int size) {
  if (size < 0) {
    size = 0;
  }

  graph_am *source = malloc(sizeof(graph_am));

  if (source != NULL) {
    source->size = size;
    source->values = calloc((size_t)size * (size_t)size, sizeof(int));
  }
  return source;
}

void graph_am_free(graph_am **source) {
  if (source != NULL && *source != NULL) {
    free((*source)->values);
    (*source)->values = NULL;
    free(*source);
    *source = NULL;
  }

  return;
}

bool graph_am_add_edge(graph_am *source, const graph_am_edge *edge) {
  bool added = false;

  if (source != NULL && edge != NULL) {
    int row = edge->row;
    int col = edge->col;

    if (row >= 0 && row < source->size && col >= 0 && col < source->size) {
      int *cell = source->values + row * source->size + col;

      if (*cell == 0) {
        if (row == col) {
          *cell = 2;
        } else {
          *cell = 1;
          *(source->values + col * source->size + row) = 1;
        }
        added = true;
      }
    }
  }

  return added;
}

bool graph_am_remove_edge(graph_am *source, const graph_am_edge *edge) {
  bool removed = false;

  if (source != NULL && edge != NULL) {
    int row = edge->row;
    int col = edge->col;

    if (row >= 0 && row < source->size && col >= 0 && col < source->size) {
      int *cell = source->values + row * source->size + col;

      if (*cell != 0) {
        *cell = 0;
        if (row != col) {
          *(source->values + col * source->size + row) = 0;
        }
        removed = true;
      }
    }
  }

  return removed;
}

graph_am *graph_am_create(int size, const graph_am_edge *edges, int count) {
  graph_am *source = graph_am_initialize(size);

  if (source != NULL && edges != NULL) {
    for (int i = 0; i < count; i++) {
      graph_am_add_edge(source, edges + i);
    }
  }

  return source;
}

void graph_am_connected(const graph_am *source, int vertex, int vertices[],
                        int *count) {
  if (count != NULL) {
    *count = 0;
  }

  if (source != NULL && vertices != NULL && count != NULL && vertex >= 0 &&
      vertex < source->size) {
    for (int i = 0; i < source->size; i++) {
      if (*(source->values + vertex * source->size + i) != 0) {
        vertices[*count] = i;
        *count += 1;
      }
    }
  }

  return;
}

int graph_am_degree(const graph_am *source, int vertex) {
  int degree = 0;

  if (source != NULL && vertex >= 0 && vertex < source->size) {
    for (int i = 0; i < source->size; i++) {
      int value = *(source->values + vertex * source->size + i);

      if (value == 2) {
        degree += 2;
      } else if (value != 0) {
        degree += 1;
      }
    }
  }

  return degree;
}

void graph_am_breadth_traversal(const graph_am *source, int vertex,
                                int vertices[], int *count) {
  if (count != NULL) {
    *count = 0;
  }

  if (source == NULL || vertices == NULL || count == NULL || vertex < 0 ||
      vertex >= source->size) {
    return;
  }

  int size = source->size;
  bool *visited = calloc((size_t)size, sizeof(bool));
  int *queue = malloc((size_t)size * sizeof(int));

  if (visited == NULL || queue == NULL) {
    free(visited);
    free(queue);
    return;
  }

  int front = 0;
  int rear = 0;
  queue[rear++] = vertex;
  visited[vertex] = true;

  while (front < rear) {
    int current = queue[front++];
    vertices[*count] = current;
    *count += 1;

    for (int i = 0; i < size; i++) {
      if (*(source->values + current * size + i) != 0 && !visited[i]) {
        visited[i] = true;
        queue[rear++] = i;
      }
    }
  }

  free(visited);
  free(queue);

  return;
}

void graph_am_depth_traversal(const graph_am *source, int vertex,
                              int vertices[], int *count) {
  if (count != NULL) {
    *count = 0;
  }

  if (source == NULL || vertices == NULL || count == NULL || vertex < 0 ||
      vertex >= source->size) {
    return;
  }

  int size = source->size;
  bool *visited = calloc((size_t)size, sizeof(bool));
  int *stack = malloc((size_t)size * sizeof(int));

  if (visited == NULL || stack == NULL) {
    free(visited);
    free(stack);
    return;
  }

  int top = 0;
  stack[top++] = vertex;

  while (top > 0) {
    int current = stack[--top];

    if (visited[current]) {
      continue;
    }

    visited[current] = true;
    vertices[*count] = current;
    *count += 1;

    // Push in ascending order so higher vertex indexes are visited first.
    for (int i = 0; i < size; i++) {
      if (*(source->values + current * size + i) != 0 && !visited[i]) {
        stack[top++] = i;
      }
    }
  }

  free(visited);
  free(stack);

  return;
}

void graph_am_print(const graph_am *source) {
  // Print the column numbers.
  printf("    ");

  for (int i = 0; i < source->size; i++) {
    printf("%3d", i);
  }
  printf("\n    ");

  for (int i = 0; i < source->size; i++) {
    printf("---");
  }
  printf("\n");

  // Print the row numbers and rows.
  for (int i = 0; i < source->size; i++) {
    printf("%3d|", i);

    for (int j = 0; j < source->size; j++) {
      // find item using offsets
      printf("%3d", *(source->values + i * source->size + j));
    }
    printf("\n");
  }
}
