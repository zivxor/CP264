/** @file  bst_linked.c
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 */
#include "bst_linked.h"

// Macro for comparing node heights
#define MAX_HEIGHT(a, b) ((a) > (b) ? a : b)

//==================================================================================
// Private Helper Functions

/**
 * Private helper function to print contents of BST in preorder.
 *
 * @param node - pointer to bst_node
 */
static void bst_print_aux(bst_node *node) {
  char string[200];

  if (node != NULL) {
    data_string(string, sizeof string, &node->item);
    printf("%s, ", string);
    bst_print_aux(node->left);
    bst_print_aux(node->right);
  }
  return;
}

/**
 * Initializes a new BST node with a copy of item.
 *
 * @param item - pointer to the value to copy to the node
 * @return - a pointer to a new BST node, NULL if memory not allocated
 */
static bst_node *bst_node_initialize(const data_type *item) {
  bst_node *node = malloc(sizeof *node);

  if (node != NULL) {
    data_copy(&node->item, item);
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
  }
  return node;
}

/**
 * Determines the height of node - empty nodes have a height of 0.
 *
 * @param node - pointer to a BST node
 * @return - the height of the current node
 */
static int bst_node_height(const bst_node *node) {
  int height = 0;

  if (node != NULL) {
    height = node->height;
  }
  return height;
}

/**
 * Updates the height of a node. Its height is the max of the heights of its
 * child nodes, plus 1.
 *
 * @param node - pointer to a BST node
 */
static void bst_update_height(bst_node *node) {
  int left_height = bst_node_height(node->left);
  int right_height = bst_node_height(node->right);

  node->height = MAX_HEIGHT(left_height, right_height) + 1;
  return;
}

/**
 * Inserts a copy of item into source. Insertion must preserve the BST
 * definition. item may appear only once in source.
 *
 * @param source - pointer to a BST
 * @param node - pointer to a BST node
 * @param item - the item to insert
 * @return - true if item inserted, false otherwise
 */
static bool bst_insert_aux(bst_linked *source, bst_node **node,
                           const data_type *item) {
  bool inserted = false;

  if (*node == NULL) {
    // Base case: add a new node containing the item.
    *node = bst_node_initialize(item);
    source->count += 1;
    inserted = true;
  } else {
    // Compare the node data_type against the new item.
    int comp = data_compare(item, &(*node)->item);

    if (comp < 0) {
      // General case: check the left subsource.
      inserted = bst_insert_aux(source, &(*node)->left, item);
    } else if (comp > 0) {
      // General case: check the right subsource.
      inserted = bst_insert_aux(source, &(*node)->right, item);
    }
  }
  if (inserted) {
    // Update the node height if any of its children have been changed.
    bst_update_height(*node);
  }
  return inserted;
}

/**
 * Private helper function to destroy all nodes in a BST.
 *
 * @param node - pointer to pointer to bst_node
 */
static void bst_destroy_aux(bst_node **node) {
  if (*node != NULL) {
    // Recursively free left and right subtrees
    bst_destroy_aux(&(*node)->left);
    bst_destroy_aux(&(*node)->right);
    // Free the current node
    free(*node);
    *node = NULL;
  }
}

/**
 * Private helper function to copy BST nodes recursively.
 *
 * @param target - pointer to target BST
 * @param node - pointer to source node
 * @return - true if successful, false otherwise
 */
static bool bst_copy_aux(bst_linked *target, const bst_node *node) {
  bool success = true;

  if (node != NULL) {
    success = bst_insert(target, &node->item);
    if (success) {
      success = bst_copy_aux(target, node->left);
    }
    if (success) {
      success = bst_copy_aux(target, node->right);
    }
  }
  return success;
}

/**
 * Private helper function to copy BST in inorder.
 *
 * @param node - pointer to bst_node
 * @param items - pointer to pointer to data array
 */
static void bst_inorder_aux(const bst_node *node, data_type **items) {
  if (node != NULL) {
    bst_inorder_aux(node->left, items);
    **items = node->item;
    (*items)++;
    bst_inorder_aux(node->right, items);
  }
}

/**
 * Private helper function to copy BST in preorder.
 *
 * @param node - pointer to bst_node
 * @param items - pointer to pointer to data array
 */
static void bst_preorder_aux(const bst_node *node, data_type **items) {
  if (node != NULL) {
    **items = node->item;
    (*items)++;
    bst_preorder_aux(node->left, items);
    bst_preorder_aux(node->right, items);
  }
}

/**
 * Private helper function to copy BST in postorder.
 *
 * @param node - pointer to bst_node
 * @param items - pointer to pointer to data array
 */
static void bst_postorder_aux(const bst_node *node, data_type **items) {
  if (node != NULL) {
    bst_postorder_aux(node->left, items);
    bst_postorder_aux(node->right, items);
    **items = node->item;
    (*items)++;
  }
}

/**
 * Private helper function to count leaf nodes.
 *
 * @param node - pointer to bst_node
 * @param count - pointer to count variable
 */
static void bst_leaf_count_aux(const bst_node *node, int *count) {
  if (node != NULL) {
    if (node->left == NULL && node->right == NULL) {
      (*count)++;
    }
    bst_leaf_count_aux(node->left, count);
    bst_leaf_count_aux(node->right, count);
  }
}

/**
 * Private helper function to count nodes with one child.
 *
 * @param node - pointer to bst_node
 * @param count - pointer to count variable
 */
static void bst_one_child_count_aux(const bst_node *node, int *count) {
  if (node != NULL) {
    if ((node->left == NULL && node->right != NULL) ||
        (node->left != NULL && node->right == NULL)) {
      (*count)++;
    }
    bst_one_child_count_aux(node->left, count);
    bst_one_child_count_aux(node->right, count);
  }
}

/**
 * Private helper function to count nodes with two children.
 *
 * @param node - pointer to bst_node
 * @param count - pointer to count variable
 */
static void bst_two_child_count_aux(const bst_node *node, int *count) {
  if (node != NULL) {
    if (node->left != NULL && node->right != NULL) {
      (*count)++;
    }
    bst_two_child_count_aux(node->left, count);
    bst_two_child_count_aux(node->right, count);
  }
}

/**
 * Private helper function to count all node types.
 *
 * @param node - pointer to bst_node
 * @param zero - pointer to leaf count
 * @param one - pointer to one-child count
 * @param two - pointer to two-child count
 */
static void bst_node_counts_aux(const bst_node *node, int *zero, int *one,
                                int *two) {
  if (node != NULL) {
    if (node->left == NULL && node->right == NULL) {
      (*zero)++;
    } else if ((node->left == NULL && node->right != NULL) ||
               (node->left != NULL && node->right == NULL)) {
      (*one)++;
    } else {
      (*two)++;
    }
    bst_node_counts_aux(node->left, zero, one, two);
    bst_node_counts_aux(node->right, zero, one, two);
  }
}

/**
 * Private helper function to check if BST is balanced.
 *
 * @param node - pointer to bst_node
 * @return - true if balanced, false otherwise
 */
static bool bst_balanced_aux(const bst_node *node) {
  if (node == NULL) {
    return true;
  }

  int left_height = bst_node_height(node->left);
  int right_height = bst_node_height(node->right);
  int diff = left_height - right_height;

  if (diff < 0) {
    diff = -diff;
  }

  if (diff > 1) {
    return false;
  }

  return bst_balanced_aux(node->left) && bst_balanced_aux(node->right);
}

/**
 * Private helper function to check if BST is valid.
 *
 * @param node - pointer to bst_node
 * @param min - pointer to minimum value (NULL if no min)
 * @param max - pointer to maximum value (NULL if no max)
 * @return - true if valid, false otherwise
 */
static bool bst_valid_aux(const bst_node *node, const data_type *min,
                          const data_type *max) {
  if (node == NULL) {
    return true;
  }

  // Check BST property
  if (min != NULL && data_compare(&node->item, min) <= 0) {
    return false;
  }

  if (max != NULL && data_compare(&node->item, max) >= 0) {
    return false;
  }

  // Check node height is correct
  int left_height = bst_node_height(node->left);
  int right_height = bst_node_height(node->right);
  int expected_height = MAX_HEIGHT(left_height, right_height) + 1;

  if (node->height != expected_height) {
    return false;
  }

  return bst_valid_aux(node->left, min, &node->item) &&
         bst_valid_aux(node->right, &node->item, max);
}

/**
 * Private helper function to check if two BSTs are equal.
 *
 * @param target_node - pointer to target bst_node
 * @param source_node - pointer to source bst_node
 * @return - true if equal, false otherwise
 */
static bool bst_equal_aux(const bst_node *target_node,
                          const bst_node *source_node) {
  if (target_node == NULL && source_node == NULL) {
    return true;
  }

  if (target_node == NULL || source_node == NULL) {
    return false;
  }

  if (data_compare(&target_node->item, &source_node->item) != 0) {
    return false;
  }

  return bst_equal_aux(target_node->left, source_node->left) &&
         bst_equal_aux(target_node->right, source_node->right);
}

/**
 * Private helper function to find and delete maximum node in a subtree.
 *
 * @param node - pointer to pointer to bst_node
 * @param item - pointer to store the deleted item
 * @return - pointer to the replacement node
 */
static bst_node *bst_delete_node_max(bst_node **node, data_type *item) {
  bst_node *replacement = NULL;

  if ((*node)->right == NULL) {
    // This is the maximum node
    data_copy(item, &(*node)->item);
    replacement = (*node)->left;
    free(*node);
    *node = NULL;
  } else {
    // Keep looking for maximum
    (*node)->right = bst_delete_node_max(&(*node)->right, item);
    bst_update_height(*node);
    replacement = *node;
  }
  return replacement;
}

/**
 * Private helper function to find and delete minimum node in a subtree.
 *
 * @param node - pointer to pointer to bst_node
 * @param item - pointer to store the deleted item
 * @return - pointer to the replacement node
 */
static bst_node *bst_delete_node_min(bst_node **node, data_type *item) {
  bst_node *replacement = NULL;

  if ((*node)->left == NULL) {
    // This is the minimum node
    data_copy(item, &(*node)->item);
    replacement = (*node)->right;
    free(*node);
    *node = NULL;
  } else {
    // Keep looking for minimum
    (*node)->left = bst_delete_node_min(&(*node)->left, item);
    bst_update_height(*node);
    replacement = *node;
  }
  return replacement;
}

/**
 * Private helper function to remove a node from BST.
 *
 * @param source - pointer to BST
 * @param node - pointer to pointer to bst_node
 * @param key - key to search for
 * @param item - pointer to store removed item
 * @return - true if removed, false otherwise
 */
static bool bst_remove_aux(bst_linked *source, bst_node **node,
                           const data_type *key, data_type *item) {
  bool removed = false;

  if (*node != NULL) {
    int comp = data_compare(key, &(*node)->item);

    if (comp < 0) {
      // Search left subtree
      removed = bst_remove_aux(source, &(*node)->left, key, item);
    } else if (comp > 0) {
      // Search right subtree
      removed = bst_remove_aux(source, &(*node)->right, key, item);
    } else {
      // Found the node to remove
      bst_node *temp = *node;

      if ((*node)->left == NULL) {
        // No left child, replace with right child
        data_copy(item, &(*node)->item);
        *node = (*node)->right;
        free(temp);
        source->count--;
      } else if ((*node)->right == NULL) {
        // No right child, replace with left child
        data_copy(item, &(*node)->item);
        *node = (*node)->left;
        free(temp);
        source->count--;
      } else {
        // Two children: replace with maximum from left subtree
        data_copy(item, &(*node)->item);
        data_type predecessor;
        (*node)->left = bst_delete_node_max(&(*node)->left, &predecessor);
        data_copy(&(*node)->item, &predecessor);
        source->count--;
      }
      removed = true;
    }

    if (*node != NULL && removed) {
      bst_update_height(*node);
    }
  }
  return removed;
}

//==================================================================================
// Functions

bst_linked *bst_initialize() {
  // Allocate memory to the list header
  bst_linked *source = malloc(sizeof *source);

  if (source) {
    // Initialize the list structure
    source->root = NULL;
    source->count = 0;
  }
  // returns NULL if malloc fails
  return source;
}

void bst_destroy(bst_linked **source) {
  if (source != NULL && *source != NULL) {
    // Free all nodes in the BST
    bst_destroy_aux(&(*source)->root);
    // Free the header node
    free(*source);
    *source = NULL;
  }
  return;
}

bool bst_empty(const bst_linked *source) { return source->count == 0; }

int bst_count(const bst_linked *source) { return source->count; }

void bst_inorder(const bst_linked *source, data_type *items) {
  bst_inorder_aux(source->root, &items);
  return;
}

void bst_preorder(const bst_linked *source, data_type *items) {
  bst_preorder_aux(source->root, &items);
  return;
}

void bst_postorder(const bst_linked *source, data_type *items) {
  bst_postorder_aux(source->root, &items);
  return;
}

bool bst_insert(bst_linked *source, const data_type *item) {
  return bst_insert_aux(source, &(source->root), item);
}

bool bst_retrieve(const bst_linked *source, const data_type *key,
                  data_type *item) {

  if (source->root == NULL) {
    return false;
  }
  bst_node *node = source->root;
  while (node != NULL) {
    int comp = data_compare(key, &node->item);
    if (comp < 0) {
      node = node->left;
    } else if (comp > 0) {
      node = node->right;
    } else {
      data_copy(item, &node->item);
      return true;
    }
  }

  return false;
}

bool bst_remove(bst_linked *source, const data_type *key, data_type *item) {
  return bst_remove_aux(source, &(source->root), key, item);
}

bool bst_copy(bst_linked **target, const bst_linked *source) {
  if (target == NULL || source == NULL) {
    return false;
  }
  if (*target == NULL) {
    *target = bst_initialize();
    if (*target == NULL) {
      return false;
    }
  }
  return bst_copy_aux(*target, source->root);
}

bool bst_max(const bst_linked *source, data_type *item) {
  if (source == NULL || source->root == NULL) {
    return false;
  }
  bst_node *node = source->root;
  while (node->right != NULL) {
    node = node->right;
  }
  data_copy(item, &node->item);
  return true;
}

bool bst_min(const bst_linked *source, data_type *item) {
  if (source == NULL || source->root == NULL) {
    return false;
  }
  bst_node *node = source->root;
  while (node->left != NULL) {
    node = node->left;
  }
  data_copy(item, &node->item);
  return true;
}

int bst_leaf_count(const bst_linked *source) {
  int count = 0;
  if (source != NULL && source->root != NULL) {
    bst_leaf_count_aux(source->root, &count);
  }
  return count;
}

int bst_one_child_count(const bst_linked *source) {
  int count = 0;
  if (source != NULL && source->root != NULL) {
    bst_one_child_count_aux(source->root, &count);
  }
  return count;
}

int bst_two_child_count(const bst_linked *source) {
  int count = 0;
  if (source != NULL && source->root != NULL) {
    bst_two_child_count_aux(source->root, &count);
  }
  return count;
}

void bst_node_counts(const bst_linked *source, int *zero, int *one, int *two) {
  *zero = 0;
  *one = 0;
  *two = 0;
  if (source != NULL && source->root != NULL) {
    bst_node_counts_aux(source->root, zero, one, two);
  }
  return;
}

bool bst_balanced(const bst_linked *source) {
  if (source == NULL || source->root == NULL) {
    return true;
  }
  return bst_balanced_aux(source->root);
}

bool bst_valid(const bst_linked *source) {
  if (source == NULL || source->root == NULL) {
    return true;
  }
  return bst_valid_aux(source->root, NULL, NULL);
}

bool bst_equal(const bst_linked *target, const bst_linked *source) {
  if (target == NULL && source == NULL) {
    return true;
  }
  if (target == NULL || source == NULL) {
    return false;
  }
  if (target->count != source->count) {
    return false;
  }
  return bst_equal_aux(target->root, source->root);
}

void bst_print(const bst_linked *source) {
  // can print root height only if root is not NULL
  printf("  count: %d, height: %d, items:\n{", source->count,
         source->root ? source->root->height : 0);
  bst_print_aux(source->root);
  printf("}\n");
  return;
}
