#include "heap.h"

static void heapdata_swap(HEAPDATA *a, HEAPDATA *b) {
  HEAPDATA t = *a;
  *a = *b;
  *b = t;
}

static int sift_up(HEAP *heap, int index) {
  while (index > 0) {
    int parent = (index - 1) / 2;

    if (heap->hda[parent].key <= heap->hda[index].key) {
      break;
    }

    heapdata_swap(&heap->hda[parent], &heap->hda[index]);
    index = parent;
  }
  return index;
}

static int sift_down(HEAP *heap, int index) {
  int n = (int)heap->size;

  while (1) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < n && heap->hda[left].key < heap->hda[smallest].key) {
      smallest = left;
    }
    if (right < n && heap->hda[right].key < heap->hda[smallest].key) {
      smallest = right;
    }

    if (smallest == index) {
      break;
    }

    heapdata_swap(&heap->hda[index], &heap->hda[smallest]);
    index = smallest;
  }
  return index;
}

HEAP *new_heap(int capacity) {
  if (capacity < 4) {
    capacity = 4;
  }

  HEAP *heap = (HEAP *)malloc(sizeof(HEAP));

  if (heap == NULL) {
    return NULL;
  }

  heap->hda = (HEAPDATA *)malloc((size_t)capacity * sizeof(HEAPDATA));

  if (heap->hda == NULL) {
    free(heap);
    return NULL;
  }

  heap->size = 0;
  heap->capacity = (unsigned int)capacity;
  return heap;
}

void heap_insert(HEAP *heap, HEAPDATA data) {
  if (heap == NULL) {
    return;
  }

  if (heap->size == heap->capacity) {
    unsigned int new_capacity = heap->capacity * 2;
    HEAPDATA *new_hda =
        (HEAPDATA *)realloc(heap->hda, (size_t)new_capacity * sizeof(HEAPDATA));

    if (new_hda == NULL) {
      return;
    }

    heap->hda = new_hda;
    heap->capacity = new_capacity;
  }

  heap->hda[heap->size] = data;
  heap->size++;
  sift_up(heap, (int)heap->size - 1);
}

HEAPDATA heap_find_min(HEAP *heap) {
  HEAPDATA out = {0, 0};

  if (heap == NULL || heap->size == 0) {
    return out;
  }
  return heap->hda[0];
}

HEAPDATA heap_extract_min(HEAP *heap) {
  HEAPDATA out = {0, 0};

  if (heap == NULL || heap->size == 0) {
    return out;
  }

  out = heap->hda[0];
  heap->size--;

  if (heap->size > 0) {
    heap->hda[0] = heap->hda[heap->size];
    sift_down(heap, 0);
  }

  if (heap->capacity > 4 && heap->size <= heap->capacity / 4) {
    unsigned int new_capacity = heap->capacity / 2;
    if (new_capacity < 4) {
      new_capacity = 4;
    }

    HEAPDATA *new_hda =
        (HEAPDATA *)realloc(heap->hda, (size_t)new_capacity * sizeof(HEAPDATA));

    if (new_hda != NULL) {
      heap->hda = new_hda;
      heap->capacity = new_capacity;
    }
  }

  return out;
}

int heap_change_key(HEAP *heap, int index, KEYTYPE new_key) {
  if (heap == NULL || index < 0 || index >= (int)heap->size) {
    return -1;
  }

  KEYTYPE old_key = heap->hda[index].key;
  heap->hda[index].key = new_key;

  if (new_key < old_key) {
    return sift_up(heap, index);
  }
  if (new_key > old_key) {
    return sift_down(heap, index);
  }
  return index;
}

int heap_search_value(HEAP *heap, VALUETYPE val) {
  if (heap == NULL) {
    return -1;
  }

  for (unsigned int i = 0; i < heap->size; i++) {
    if (heap->hda[i].value == val) {
      return (int)i;
    }
  }
  return -1;
}

void heap_clean(HEAP **heapp) {
  if (heapp == NULL || *heapp == NULL) {
    return;
  }

  free((*heapp)->hda);
  (*heapp)->hda = NULL;
  free(*heapp);
  *heapp = NULL;
}

static int ptr_value(void *p) { return *((int *)p); }

static void ptr_swap(void **a, void **b) {
  void *t = *a;
  *a = *b;
  *b = t;
}

static void heapify_ptr_down(void *a[], int n, int i) {
  while (1) {
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    int largest = i;

    if (left < n && ptr_value(a[left]) > ptr_value(a[largest])) {
      largest = left;
    }
    if (right < n && ptr_value(a[right]) > ptr_value(a[largest])) {
      largest = right;
    }

    if (largest == i) {
      break;
    }

    ptr_swap(&a[i], &a[largest]);
    i = largest;
  }
}

void heap_sort(void *a[], int left, int right) {
  if (a == NULL || left >= right) {
    return;
  }

  int n = right - left + 1;
  void **base = a + left;

  for (int i = n / 2 - 1; i >= 0; i--) {
    heapify_ptr_down(base, n, i);
  }

  for (int end = n - 1; end > 0; end--) {
    ptr_swap(&base[0], &base[end]);
    heapify_ptr_down(base, end, 0);
  }
}
