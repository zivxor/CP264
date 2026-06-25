#include "avl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct record {
  char name[20];
  float score;
} RECORD;

typedef struct avlnode AVLNODE;

struct avlnode {
  RECORD data;
  int height;
  AVLNODE *parent;
  AVLNODE *left;
  AVLNODE *right;
};

void ror(AVLNODE *node) {}
void rol(AVLNODE *node) {}
void rebalance(AVLNODE *node) {}

/* Get the height of AVL tree
 * @param np - pointer to the root of tree
 * @return - the height value at root.
 */
int height(AVLNODE *root) { return root ? root->height : 0; }

/* Return the balance factor at the given node
 * @param np - pointer to the node of tree
 * @return - the balance factor of the node pointed by np.
 */
int balance_factor(AVLNODE *np) {
  int balance = height(np->left) - height(np->right);
  return balance;
}

/* Create and return AVLNODE of given data
 * Use malloc()
 * @param data - data for the new node.
 * @return - pointer to the new AVLNODE.
 */
AVLNODE *avl_node(RECORD data) {
  AVLNODE *new = malloc(sizeof(AVLNODE));
  new->data = data;
  new->height = 1;
  new->parent = NULL;
  new->left = NULL;
  new->right = NULL;
  return new;
}

/* Search AVL tree by key matching data.name
 * @param root - pointer to tree root.
 * @param key - key to match with data.name for search
 * @return - node pointer if found, otherwise NULL
 */
AVLNODE *avl_search(AVLNODE *root, char *key) {
  AVLNODE *cur = root;
  while (cur) {
    int cmp = strcmp(key, cur->data.name);
    if (cmp == 0) {
      return cur;
    } else if (cmp < 0) {
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return NULL;
}

/* Insert a node of given record data into AVL tree.
 * Try to use iterative algorithm.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param data  - record data for the new node.
 */
void avl_insert(AVLNODE **rootp, RECORD data) {}

/* Delete a node of data.name matched with given key from AVL tree.
 * Try to use iterative algorithm
 *
 * @param rootp - pointer of pointer to tree root.
 * @param key -   key to match with data.name for deletion.
 */
void avl_delete(AVLNODE **rootp, char *key) {
  AVLNODE *curr = *rootp;
  AVLNODE *node = avl_search(curr, key);
  if (node) {
  }
}

/* This function clean AVL tree.
 * @param rootp - pointer of pointer of tree root.
 */
void avl_clean(AVLNODE **rootp);
