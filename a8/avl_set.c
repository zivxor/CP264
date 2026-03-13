#include "avl_set.h"
#include <stdlib.h>
#include <string.h>
/**
 * returns the number of elements in the set
 */
int set_size(AVLSET *s) {
  if (!s)
    return -1;
  return s->size;
}

/**
 * Returns 1 it set s contains element e; otherwise 0.
 */
int set_contain(AVLSET *s, char *e) {
  if (!s || !e)
    return 0;
  return avl_search(s->root, e) != NULL;
}

/**
 * Add element e into set s.
 */
void set_add(AVLSET *s, char *e) {
  if (!s || !e)
    return;
  if (avl_search(s->root, e))
    return;
  RECORD r = {0};
  strncpy(r.name, e, sizeof(r.name) - 1);
  avl_insert(&s->root, r);
  s->size++;
}

/**
 * Remove element e from set s.
 */
void set_remove(AVLSET *s, char *e) {
  if (!s || !e)
    return;
  if (!avl_search(s->root, e))
    return;
  avl_delete(&s->root, e);
  s->size--;
}

/**
 * Clear the set, clearing the underlying AVL tree, and reset fields of s.
 */
void set_clean(AVLSET *s) {
  if (!s)
    return;
  avl_clean(&s->root);
  s->size = 0;
}