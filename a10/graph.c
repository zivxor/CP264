#include "graph.h"

#include <string.h>

#include "queue_stack.h"

static ADJNODE *new_adjnode(int nid, int weight) {
  ADJNODE *np = (ADJNODE *)malloc(sizeof(ADJNODE));
  if (np != NULL) {
    np->nid = nid;
    np->weight = weight;
    np->next = NULL;
  }
  return np;
}

GRAPH *new_graph(int n) {
  if (n <= 0) {
    return NULL;
  }

  GRAPH *g = (GRAPH *)malloc(sizeof(GRAPH));
  if (g == NULL) {
    return NULL;
  }

  g->order = n;
  g->size = 0;
  g->nodes = (GNODE **)malloc((size_t)n * sizeof(GNODE *));

  if (g->nodes == NULL) {
    free(g);
    return NULL;
  }

  for (int i = 0; i < n; i++) {
    g->nodes[i] = (GNODE *)malloc(sizeof(GNODE));
    if (g->nodes[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(g->nodes[j]);
      }
      free(g->nodes);
      free(g);
      return NULL;
    }
    g->nodes[i]->nid = i;
    snprintf(g->nodes[i]->name, sizeof(g->nodes[i]->name), "%c", 'A' + i);
    g->nodes[i]->neighbor = NULL;
  }

  return g;
}

void insert_edge_graph(GRAPH *g, int from, int to, int weight) {
  if (g == NULL || from < 0 || to < 0 || from >= g->order || to >= g->order) {
    return;
  }

  ADJNODE *curr = g->nodes[from]->neighbor;
  ADJNODE *prev = NULL;

  while (curr != NULL) {
    if (curr->nid == to) {
      curr->weight = weight;
      return;
    }
    prev = curr;
    curr = curr->next;
  }

  ADJNODE *np = new_adjnode(to, weight);
  if (np == NULL) {
    return;
  }

  if (prev == NULL) {
    g->nodes[from]->neighbor = np;
  } else {
    prev->next = np;
  }
  g->size++;
}

void delete_edge_graph(GRAPH *g, int from, int to) {
  if (g == NULL || from < 0 || to < 0 || from >= g->order || to >= g->order) {
    return;
  }

  ADJNODE *curr = g->nodes[from]->neighbor;
  ADJNODE *prev = NULL;

  while (curr != NULL && curr->nid != to) {
    prev = curr;
    curr = curr->next;
  }

  if (curr == NULL) {
    return;
  }

  if (prev == NULL) {
    g->nodes[from]->neighbor = curr->next;
  } else {
    prev->next = curr->next;
  }
  free(curr);
  g->size--;
}

int get_edge_weight(GRAPH *g, int from, int to) {
  if (g == NULL || from < 0 || to < 0 || from >= g->order || to >= g->order) {
    return INFINITY;
  }

  ADJNODE *curr = g->nodes[from]->neighbor;
  while (curr != NULL) {
    if (curr->nid == to) {
      return curr->weight;
    }
    curr = curr->next;
  }

  return INFINITY;
}

void traverse_bforder(GRAPH *g, int start) {
  if (g == NULL || start < 0 || start >= g->order) {
    return;
  }

  int *visited = (int *)calloc((size_t)g->order, sizeof(int));
  if (visited == NULL) {
    return;
  }

  QUEUE q = {NULL, NULL};
  visited[start] = 1;
  int *s = (int *)malloc(sizeof(int));
  if (s == NULL) {
    free(visited);
    return;
  }
  *s = start;
  enqueue(&q, s);

  while (q.front != NULL) {
    int *up = (int *)dequeue(&q);
    if (up == NULL) {
      break;
    }

    int u = *up;
    free(up);

    printf("(%d %s) ", u, g->nodes[u]->name);

    ADJNODE *adj = g->nodes[u]->neighbor;
    while (adj != NULL) {
      int v = adj->nid;
      if (!visited[v]) {
        visited[v] = 1;
        int *vp = (int *)malloc(sizeof(int));
        if (vp != NULL) {
          *vp = v;
          enqueue(&q, vp);
        }
      }
      adj = adj->next;
    }
  }

  while (q.front != NULL) {
    free(dequeue(&q));
  }
  clean_queue(&q);
  free(visited);
}

void traverse_dforder(GRAPH *g, int start) {
  if (g == NULL || start < 0 || start >= g->order) {
    return;
  }

  int *visited = (int *)calloc((size_t)g->order, sizeof(int));
  if (visited == NULL) {
    return;
  }

  STACK s = {NULL};
  int *sp = (int *)malloc(sizeof(int));
  if (sp == NULL) {
    free(visited);
    return;
  }
  *sp = start;
  push(&s, sp);

  while (s.top != NULL) {
    int *up = (int *)pop(&s);
    if (up == NULL) {
      break;
    }

    int u = *up;
    free(up);

    if (visited[u]) {
      continue;
    }

    visited[u] = 1;
    printf("(%d %s) ", u, g->nodes[u]->name);

    ADJNODE *adj = g->nodes[u]->neighbor;
    while (adj != NULL) {
      if (!visited[adj->nid]) {
        int *vp = (int *)malloc(sizeof(int));
        if (vp != NULL) {
          *vp = adj->nid;
          push(&s, vp);
        }
      }
      adj = adj->next;
    }
  }

  while (s.top != NULL) {
    free(pop(&s));
  }
  clean_stack(&s);
  free(visited);
}

void display_graph(GRAPH *g) {
  if (g == NULL) {
    return;
  }

  printf("order %d size %d (from to weight) ", g->order, g->size);
  for (int i = 0; i < g->order; i++) {
    ADJNODE *adj = g->nodes[i]->neighbor;
    while (adj != NULL) {
      printf("(%d %d %d) ", i, adj->nid, adj->weight);
      adj = adj->next;
    }
  }
}

void clean_graph(GRAPH **gp) {
  if (gp == NULL || *gp == NULL) {
    return;
  }

  GRAPH *g = *gp;
  for (int i = 0; i < g->order; i++) {
    ADJNODE *adj = g->nodes[i]->neighbor;
    while (adj != NULL) {
      ADJNODE *tmp = adj;
      adj = adj->next;
      free(tmp);
    }
    free(g->nodes[i]);
  }

  free(g->nodes);
  free(g);
  *gp = NULL;
}
