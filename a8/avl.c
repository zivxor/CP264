#include "avl.h"
#include <stdlib.h>
#include <string.h>

/* Get the height of AVL tree
 * @param root - pointer to the root of tree
 * @return - the height value at root.
 * Convention: NULL -> 0, leaf -> 1
 */
int height(AVLNODE *root) {
  if (!root)
    return 0;
  return root->height;
}

/* Return the balance factor at the given node
 * @param np - pointer to the node of tree
 * @return - the balance factor of the node pointed by np.
 * bf = height(left) - height(right)
 */
int balance_factor(AVLNODE *np) {
  if (!np)
    return 0;
  int lh = height(np->left);
  int rh = height(np->right);
  return lh - rh;
}

/* Create and return AVLNODE of given data
 * Use malloc()
 * @param data - data for the new node.
 * @return - pointer to the new AVLNODE.
 */
AVLNODE *avl_node(RECORD data) {
  AVLNODE *np = (AVLNODE *)malloc(sizeof(AVLNODE));
  if (!np)
    return NULL;

  np->data = data;
  np->height = 1; // leaf
  np->parent = NULL;
  np->left = NULL;
  np->right = NULL;
  return np;
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
    if (cmp == 0)
      return cur;
    else if (cmp < 0)
      cur = cur->left;
    else
      cur = cur->right;
  }
  return NULL;
}

static void update_height(AVLNODE *node) {
  if (!node)
    return;
  int lh = height(node->left);
  int rh = height(node->right);
  node->height = (lh > rh ? lh : rh) + 1;
}

static void rotate_right(AVLNODE **rootp, AVLNODE *y) {
  AVLNODE *x = y->left;
  AVLNODE *B = x->right;

  // rotation
  x->right = y;
  y->left = B;

  // parents
  x->parent = y->parent;
  if (y->parent) {
    if (y->parent->left == y)
      y->parent->left = x;
    else
      y->parent->right = x;
  } else {
    *rootp = x;
  }
  y->parent = x;
  if (B)
    B->parent = y;

  // update heights bottom-up
  update_height(y);
  update_height(x);
}

static void rotate_left(AVLNODE **rootp, AVLNODE *x) {
  AVLNODE *y = x->right;
  AVLNODE *B = y->left;

  // rotation
  y->left = x;
  x->right = B;

  // parents
  y->parent = x->parent;
  if (x->parent) {
    if (x->parent->left == x)
      x->parent->left = y;
    else
      x->parent->right = y;
  } else {
    *rootp = y;
  }
  x->parent = y;
  if (B)
    B->parent = x;

  // update heights bottom-up
  update_height(x);
  update_height(y);
}

/* Rebalance a single node and return the (possibly new) root of this subtree */
static AVLNODE *rebalance_one(AVLNODE **rootp, AVLNODE *node) {
  if (!node)
    return NULL;

  update_height(node);
  int bf = balance_factor(node);

  // Left heavy
  if (bf > 1) {
    if (balance_factor(node->left) < 0) {
      // LR
      rotate_left(rootp, node->left);
    }
    // LL
    rotate_right(rootp, node);
    return node->parent; // new root of this subtree
  }

  // Right heavy
  if (bf < -1) {
    if (balance_factor(node->right) > 0) {
      // RL
      rotate_right(rootp, node->right);
    }
    // RR
    rotate_left(rootp, node);
    return node->parent; // new root of this subtree
  }

  // Already balanced
  return node;
}

/* Rebalance all nodes on path to root starting from node */
static void rebalance(AVLNODE **rootp, AVLNODE *node) {
  while (node) {
    AVLNODE *subroot = rebalance_one(rootp, node);
    if (!subroot)
      break;
    node = subroot->parent;
  }
}

/* Insert a node of given record data into AVL tree.
 * Try to use iterative algorithm.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param data  - record data for the new node.
 */
void avl_insert(AVLNODE **rootp, RECORD data) {
  AVLNODE *np = avl_node(data);
  if (!np)
    return;

  if (!*rootp) {
    *rootp = np;
    return;
  }

  AVLNODE *cur = *rootp;
  AVLNODE *parent = NULL;

  while (cur) {
    parent = cur;
    int cmp = strcmp(data.name, cur->data.name);
    if (cmp < 0) {
      cur = cur->left;
    } else if (cmp > 0) {
      cur = cur->right;
    } else {
      // duplicate key: do nothing
      free(np);
      return;
    }
  }

  np->parent = parent;
  if (strcmp(data.name, parent->data.name) < 0)
    parent->left = np;
  else
    parent->right = np;

  // rebalance from the inserted node upward
  rebalance(rootp, np);
}

/* Delete a node of data.name matched with given key from AVL tree.
 * Try to use iterative algorithm
 *
 * @param rootp - pointer of pointer to tree root.
 * @param key -   key to match with data.name for deletion.
 */
void avl_delete(AVLNODE **rootp, char *key) {
  AVLNODE *node = avl_search(*rootp, key);
  if (!node)
    return;

  AVLNODE *rebalance_start = NULL;

  // Case 1: no children
  if (!node->left && !node->right) {
    rebalance_start = node->parent;

    if (!node->parent) {
      *rootp = NULL;
    } else if (node->parent->left == node) {
      node->parent->left = NULL;
    } else {
      node->parent->right = NULL;
    }
    free(node);
  }
  // Case 2: one child
  else if (!node->left || !node->right) {
    AVLNODE *child = (node->left) ? node->left : node->right;
    rebalance_start = node->parent;

    child->parent = node->parent;
    if (!node->parent) {
      *rootp = child;
    } else if (node->parent->left == node) {
      node->parent->left = child;
    } else {
      node->parent->right = child;
    }
    free(node);
  }
  // Case 3: two children
  else {
    // in-order successor = leftmost of right subtree
    AVLNODE *succ = node->right;
    while (succ->left)
      succ = succ->left;

    // copy successor's data into node
    node->data = succ->data;

    AVLNODE *parent = succ->parent;
    AVLNODE *child = succ->right; // succ has no left

    if (parent->left == succ)
      parent->left = child;
    else
      parent->right = child;

    if (child)
      child->parent = parent;

    rebalance_start = parent;
    free(succ);
  }

  if (rebalance_start)
    rebalance(rootp, rebalance_start);
}

/* This function clean AVL tree.
 * @param rootp - pointer of pointer of tree root.
 */
void avl_clean(AVLNODE **rootp) {
  if (!rootp || !*rootp)
    return;

  avl_clean(&((*rootp)->left));
  avl_clean(&((*rootp)->right));

  free(*rootp);
  *rootp = NULL;
}
