#include "algorithm.h"

#include <stdlib.h>

#include "heap.h"

EDGELIST *mst_prim(GRAPH *g, int start) {
  EDGELIST *mst = new_edgelist();
  if (mst == NULL || g == NULL || start < 0 || start >= g->order) {
    return mst;
  }

  int n = g->order;
  int *key = (int *)malloc((size_t)n * sizeof(int));
  int *parent = (int *)malloc((size_t)n * sizeof(int));
  int *in_mst = (int *)calloc((size_t)n, sizeof(int));
  HEAP *pq = new_heap(n);

  if (key == NULL || parent == NULL || in_mst == NULL || pq == NULL) {
    free(key);
    free(parent);
    free(in_mst);
    heap_clean(&pq);
    return mst;
  }

  for (int i = 0; i < n; i++) {
    key[i] = INFINITY;
    parent[i] = -1;
  }
  key[start] = 0;

  for (int i = 0; i < n; i++) {
    HEAPDATA d = {key[i], i};
    heap_insert(pq, d);
  }

  while (pq->size > 0) {
    HEAPDATA min = heap_extract_min(pq);
    int u = min.value;

    if (in_mst[u]) {
      continue;
    }

    in_mst[u] = 1;

    if (u != start && parent[u] != -1) {
      insert_edge_end(mst, parent[u], u, key[u]);
    }

    ADJNODE *adj = g->nodes[u]->neighbor;
    while (adj != NULL) {
      int v = adj->nid;
      int w = adj->weight;

      if (!in_mst[v] && w < key[v]) {
        key[v] = w;
        parent[v] = u;
        int idx = heap_search_value(pq, v);
        if (idx >= 0) {
          heap_change_key(pq, idx, key[v]);
        }
      }

      adj = adj->next;
    }
  }

  free(key);
  free(parent);
  free(in_mst);
  heap_clean(&pq);
  return mst;
}

EDGELIST *spt_dijkstra(GRAPH *g, int start) {
  EDGELIST *spt = new_edgelist();
  if (spt == NULL || g == NULL || start < 0 || start >= g->order) {
    return spt;
  }

  int n = g->order;
  int *dist = (int *)malloc((size_t)n * sizeof(int));
  int *parent = (int *)malloc((size_t)n * sizeof(int));
  int *done = (int *)calloc((size_t)n, sizeof(int));
  HEAP *pq = new_heap(n);

  if (dist == NULL || parent == NULL || done == NULL || pq == NULL) {
    free(dist);
    free(parent);
    free(done);
    heap_clean(&pq);
    return spt;
  }

  for (int i = 0; i < n; i++) {
    dist[i] = INFINITY;
    parent[i] = -1;
  }
  dist[start] = 0;

  for (int i = 0; i < n; i++) {
    HEAPDATA d = {dist[i], i};
    heap_insert(pq, d);
  }

  while (pq->size > 0) {
    HEAPDATA min = heap_extract_min(pq);
    int u = min.value;

    if (done[u]) {
      continue;
    }
    done[u] = 1;

    if (u != start && parent[u] != -1) {
      int w = get_edge_weight(g, parent[u], u);
      insert_edge_end(spt, parent[u], u, w);
    }

    ADJNODE *adj = g->nodes[u]->neighbor;
    while (adj != NULL) {
      int v = adj->nid;
      int w = adj->weight;

      if (!done[v] && dist[u] != INFINITY && dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        parent[v] = u;

        int idx = heap_search_value(pq, v);
        if (idx >= 0) {
          heap_change_key(pq, idx, dist[v]);
        }
      }

      adj = adj->next;
    }
  }

  free(dist);
  free(parent);
  free(done);
  heap_clean(&pq);
  return spt;
}

EDGELIST *sp_dijkstra(GRAPH *g, int start, int end) {
  EDGELIST *sp = new_edgelist();
  if (sp == NULL || g == NULL || start < 0 || end < 0 || start >= g->order ||
      end >= g->order) {
    return sp;
  }

  int n = g->order;
  int *dist = (int *)malloc((size_t)n * sizeof(int));
  int *parent = (int *)malloc((size_t)n * sizeof(int));
  int *done = (int *)calloc((size_t)n, sizeof(int));
  HEAP *pq = new_heap(n);

  if (dist == NULL || parent == NULL || done == NULL || pq == NULL) {
    free(dist);
    free(parent);
    free(done);
    heap_clean(&pq);
    return sp;
  }

  for (int i = 0; i < n; i++) {
    dist[i] = INFINITY;
    parent[i] = -1;
  }
  dist[start] = 0;

  for (int i = 0; i < n; i++) {
    HEAPDATA d = {dist[i], i};
    heap_insert(pq, d);
  }

  while (pq->size > 0) {
    HEAPDATA min = heap_extract_min(pq);
    int u = min.value;

    if (done[u]) {
      continue;
    }
    done[u] = 1;

    if (u == end) {
      break;
    }

    ADJNODE *adj = g->nodes[u]->neighbor;
    while (adj != NULL) {
      int v = adj->nid;
      int w = adj->weight;

      if (!done[v] && dist[u] != INFINITY && dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        parent[v] = u;

        int idx = heap_search_value(pq, v);
        if (idx >= 0) {
          heap_change_key(pq, idx, dist[v]);
        }
      }

      adj = adj->next;
    }
  }

  if (dist[end] != INFINITY) {
    int v = end;
    while (v != start && parent[v] != -1) {
      int u = parent[v];
      int w = get_edge_weight(g, u, v);
      insert_edge_start(sp, u, v, w);
      v = u;
    }
  }

  free(dist);
  free(parent);
  free(done);
  heap_clean(&pq);
  return sp;
}
