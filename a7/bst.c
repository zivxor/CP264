#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* This function creates BSTNODE node with given RECORD data
 * using malloc() and return the new node pointer.
 */
BSTNODE *bst_node(RECORD data) {
  BSTNODE *node = malloc(sizeof(BSTNODE));
  if (node == NULL) {
    return NULL;
  }
  node->left = NULL;
  node->right = NULL;
  node->data = data;
  return node;
}

/* Search the BST by search key matching with data.name
 *
 * @param root - pointer to tree root.
 * @param key - string of search key
 *
 * @return - pointer to matched node if found, otherwise NULL
 */
BSTNODE *bst_search(BSTNODE *root, char *key) {
  if (root == NULL || key == NULL) {
    return NULL;
  }
  BSTNODE *curr = root;
  while (curr) {
    int compared = strcmp(key, curr->data.name);
    if (compared == 0) {
      return curr;
    } else if (compared < 0) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  return NULL;
}
/* Insert a node of given record data into BST.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param data  -  record data for the new node.
 *
 */
void bst_insert(BSTNODE **rootp, RECORD data) {
  if (rootp == NULL) {
    return;
  }

  if (*rootp == NULL) {
    *rootp = bst_node(data);
    return;
  }

  BSTNODE *parent = NULL;
  BSTNODE *curr = *rootp;
  while (curr) {
    int comp = strcmp(data.name, curr->data.name);
    parent = curr;
    if (comp < 0) {
      curr = curr->left;
    } else if (comp > 0) {
      curr = curr->right;
    } else {
      return;
    }
  }

  BSTNODE *new_node = bst_node(data);
  if (new_node == NULL) {
    return;
  }

  if (strcmp(data.name, parent->data.name) < 0) {
    parent->left = new_node;
  } else {
    parent->right = new_node;
  }
}

/* Delete a node of data.name matched with given key.
 *
 * @param rootp - pointer of pointer to tree root.
 * @param key -   key to match with data.name for deletion.
 */
void bst_delete(BSTNODE **rootp, char *key) {
  if (rootp == NULL || *rootp == NULL || key == NULL) {
    return;
  }

  BSTNODE *node = *rootp;
  int comp = strcmp(key, node->data.name);

  if (comp < 0) {
    bst_delete(&node->left, key);
    return;
  }

  if (comp > 0) {
    bst_delete(&node->right, key);
    return;
  }

  if (node->left == NULL && node->right == NULL) {
    *rootp = NULL;
    free(node);
  } else if (node->left == NULL) {
    *rootp = node->right;
    free(node);
  } else if (node->right == NULL) {
    *rootp = node->left;
    free(node);
  } else {
    BSTNODE **predp = &node->left;
    while ((*predp)->right) {
      predp = &(*predp)->right;
    }

    BSTNODE *pred = *predp;
    node->data = pred->data;
    *predp = pred->left;
    free(pred);
  }
}

/* This function cleans the BST passed by pointer of root pointer.
 * @param rootp - pointer to pointer of a tree node.
 */
static void bst_clean_nodes(BSTNODE *root) {
  if (root == NULL) {
    return;
  }

  bst_clean_nodes(root->left);
  bst_clean_nodes(root->right);
  free(root);
}

void bst_clean(BSTNODE **rootp) {
  if (rootp == NULL || *rootp == NULL) {
    return;
  }

  bst_clean_nodes(*rootp);
  *rootp = NULL;
}