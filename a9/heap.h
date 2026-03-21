#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>

typedef int KEYTYPE;
typedef int VALUETYPE;

typedef struct {
  KEYTYPE key;
  VALUETYPE value;
} HEAPDATA;

typedef struct heap {
  unsigned int size;
  unsigned int capacity;
  HEAPDATA *hda;
} HEAP;

HEAP *new_heap(int capacity);
void heap_insert(HEAP *heap, HEAPDATA data);
HEAPDATA heap_find_min(HEAP *heap);
HEAPDATA heap_extract_min(HEAP *heap);
int heap_change_key(HEAP *heap, int index, KEYTYPE new_key);
int heap_search_value(HEAP *heap, VALUETYPE val);
void heap_clean(HEAP **heapp);
void heap_sort(void *a[], int left, int right);

#endif
