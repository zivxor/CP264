#include "edgelist.h"

static EDGENODE *new_edgenode(int from, int to, int weight) {
  EDGENODE *np = (EDGENODE *)malloc(sizeof(EDGENODE));
  if (np != NULL) {
    np->from = from;
    np->to = to;
    np->weight = weight;
    np->next = NULL;
  }
  return np;
}

EDGELIST *new_edgelist(void) {
  EDGELIST *g = (EDGELIST *)malloc(sizeof(EDGELIST));
  if (g != NULL) {
    g->size = 0;
    g->start = NULL;
    g->end = NULL;
  }
  return g;
}

void insert_edge_start(EDGELIST *g, int from, int to, int weight) {
  if (g == NULL) {
    return;
  }

  EDGENODE *np = new_edgenode(from, to, weight);
  if (np == NULL) {
    return;
  }

  np->next = g->start;
  g->start = np;

  if (g->end == NULL) {
    g->end = np;
  }

  g->size++;
}

void insert_edge_end(EDGELIST *g, int from, int to, int weight) {
  if (g == NULL) {
    return;
  }

  EDGENODE *np = new_edgenode(from, to, weight);
  if (np == NULL) {
    return;
  }

  if (g->size == 0) {
    g->start = np;
    g->end = np;
  } else {
    g->end->next = np;
    g->end = np;
  }

  g->size++;
}

void delete_edge(EDGELIST *g, int from, int to) {
  if (g == NULL || g->size == 0) {
    return;
  }

  EDGENODE *curr = g->start;
  EDGENODE *prev = NULL;

  while (curr != NULL && !(curr->from == from && curr->to == to)) {
    prev = curr;
    curr = curr->next;
  }

  if (curr == NULL) {
    return;
  }

  if (prev == NULL) {
    g->start = curr->next;
  } else {
    prev->next = curr->next;
  }

  if (curr == g->end) {
    g->end = prev;
  }

  free(curr);
  g->size--;

  if (g->size == 0) {
    g->start = NULL;
    g->end = NULL;
  }
}

int weight_edgelist(EDGELIST *g) {
  if (g == NULL) {
    return 0;
  }

  int sum = 0;
  EDGENODE *curr = g->start;
  while (curr != NULL) {
    sum += curr->weight;
    curr = curr->next;
  }
  return sum;
}

void clean_edgelist(EDGELIST **gp) {
  if (gp == NULL || *gp == NULL) {
    return;
  }

  EDGENODE *curr = (*gp)->start;
  while (curr != NULL) {
    EDGENODE *tmp = curr;
    curr = curr->next;
    free(tmp);
  }

  free(*gp);
  *gp = NULL;
}

void display_edgelist(EDGELIST *g) {
  if (g == NULL) {
    return;
  }

  printf("size %d (from to weight) ", g->size);
  EDGENODE *curr = g->start;
  while (curr != NULL) {
    printf("(%d %d %d) ", curr->from, curr->to, curr->weight);
    curr = curr->next;
  }
}
