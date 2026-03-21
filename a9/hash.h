#ifndef HASH_H
#define HASH_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Define structure DATA type to represent key and value as key value pair. */
typedef struct {
  char key[20];
  int value;
} DATA;

/* Define structure NODE as linked list node to represent hash data. */
typedef struct hnode {
  DATA data;
  struct hnode *next;
} HNODE;

/* Define HASHTABLE structure type for linked hash table. */
typedef struct hashtable {
  int size;
  int count;
  HNODE **hna;
} HASHTABLE;

int hash(char *key, int size);
HASHTABLE *new_hashtable(int size);
int hashtable_insert(HASHTABLE *ht, DATA data);
HNODE *hashtable_search(HASHTABLE *ht, char *key);
int hashtable_delete(HASHTABLE *ht, char *key);
void hashtable_clean(HASHTABLE **ht);

#endif
