#include "avl.h"
#ifndef AVL_SET_H_
#define AVL_SET_H_
typedef struct {
  int size;
  AVLNODE *root;
} AVLSET;

/**
 * returns the number of elements in the set
 */
int set_size(AVLSET *s);

/**
 * Returns 1 it set s contains element e; otherwise 0.
 */
int set_contain(AVLSET *s, char *e);

/**
 * Add element e into set s.
 */
void set_add(AVLSET *s, char *e);

/**
 * Remove  element e into set s
 */
void set_remove(AVLSET *s, char *e);

/**
 * Clear the set, clearing the underlying AVL tree, and reset fields of s.
 */
void set_clean(AVLSET *s);
#endif