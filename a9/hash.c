#include "hash.h"

static HNODE *new_hnode(DATA data) {
  HNODE *node = (HNODE *)malloc(sizeof(HNODE));

  if (node != NULL) {
    node->data = data;
    node->next = NULL;
  }
  return node;
}

int hash(char *key, int size) {
  if (key == NULL || size <= 0) {
    return 0;
  }

  int sum = 0;

  while (*key) {
    sum += (unsigned char)(*key);
    key++;
  }
  return sum % size;
}

HASHTABLE *new_hashtable(int size) {
  if (size <= 0) {
    return NULL;
  }

  HASHTABLE *ht = (HASHTABLE *)malloc(sizeof(HASHTABLE));

  if (ht == NULL) {
    return NULL;
  }

  ht->hna = (HNODE **)calloc((size_t)size, sizeof(HNODE *));

  if (ht->hna == NULL) {
    free(ht);
    return NULL;
  }

  ht->size = size;
  ht->count = 0;
  return ht;
}

HNODE *hashtable_search(HASHTABLE *ht, char *key) {
  if (ht == NULL || key == NULL || ht->size <= 0) {
    return NULL;
  }

  int idx = hash(key, ht->size);
  HNODE *cur = ht->hna[idx];

  while (cur != NULL) {
    if (strcmp(cur->data.key, key) == 0) {
      return cur;
    }
    cur = cur->next;
  }
  return NULL;
}

int hashtable_insert(HASHTABLE *ht, DATA data) {
  if (ht == NULL || ht->size <= 0 || data.key[0] == '\0') {
    return 0;
  }

  int idx = hash(data.key, ht->size);
  HNODE *cur = ht->hna[idx];

  while (cur != NULL) {
    if (strcmp(cur->data.key, data.key) == 0) {
      cur->data.value = data.value;
      return 0;
    }
    if (cur->next == NULL) {
      break;
    }
    cur = cur->next;
  }

  HNODE *node = new_hnode(data);

  if (node == NULL) {
    return 0;
  }

  if (ht->hna[idx] == NULL) {
    ht->hna[idx] = node;
  } else {
    cur->next = node;
  }

  ht->count++;
  return 1;
}

int hashtable_delete(HASHTABLE *ht, char *key) {
  if (ht == NULL || key == NULL || ht->size <= 0) {
    return 0;
  }

  int idx = hash(key, ht->size);
  HNODE *cur = ht->hna[idx];
  HNODE *prev = NULL;

  while (cur != NULL) {
    if (strcmp(cur->data.key, key) == 0) {
      if (prev == NULL) {
        ht->hna[idx] = cur->next;
      } else {
        prev->next = cur->next;
      }
      free(cur);
      ht->count--;
      return 1;
    }
    prev = cur;
    cur = cur->next;
  }
  return 0;
}

void hashtable_clean(HASHTABLE **ht) {
  if (ht == NULL || *ht == NULL) {
    return;
  }

  for (int i = 0; i < (*ht)->size; i++) {
    HNODE *cur = (*ht)->hna[i];

    while (cur != NULL) {
      HNODE *tmp = cur;
      cur = cur->next;
      free(tmp);
    }
    (*ht)->hna[i] = NULL;
  }

  (*ht)->count = 0;
}
