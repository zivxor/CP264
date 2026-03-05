/** @file  bst_linked.h
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 * DO NOT CHANGE CONTENTS
 */
#ifndef BST_LINKED_H_
#define BST_LINKED_H_

// ==============================================================================================
// Includes

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

// ==============================================================================================
// Structures

/**
 * BST node
 */
typedef struct BST_NODE {
  /** Node data */
  data_type item;
  /** Height of the current node */
  int height;
  /** Pointer to the left child */
  struct BST_NODE *left;
  /** Pointer to the right child */
  struct BST_NODE *right;
} bst_node;

/**
 * BST header
 */
typedef struct {
  /** Pointer to the root node of the BST */
  bst_node *root;
  /** Number of items in BST */
  int count;
} bst_linked;

//==================================================================================
// Prototypes

/**
 * Initializes a BST.
 *
 * @return - pointer to a BST
 */
bst_linked *bst_initialize();

/**
 * Destroys a BST. All nodes in source are freed and set to NULL.
 * Header node is freed and set to NULL.
 *
 * @param source - pointer to a BST
 */
void bst_destroy(bst_linked **source);

/**
 * Determines if source is empty.
 *
 * @param source - pointer to a BST
 * @return - true if the BST is empty, false otherwise
 */
bool bst_empty(const bst_linked *source);

/**
 * Returns number of items in source.
 *
 * @param source - pointer to a BST
 * @return - number of items in BST
 */
int bst_count(const bst_linked *source);

/**
 * Inserts a copy of item into source. Values in source must be unique.
 * Returns true if new item inserted, false if memory cannot be allocated
 * or item is already in source.
 *
 * @param source - pointer to a BST Pointer to a BST.
 * @param item - pointer to the item to push
 * @return - true if item inserted, false otherwise
 */
bool bst_insert(bst_linked *source, const data_type *item);

/**
 * Retrieves a copy of a value matching key in source into item.
 *
 * @param source - pointer to a BST
 * @param key - key value to search for
 * @param item - pointer to copy of the item retrieved
 * @return - true if item retrieved, false otherwise (key not found)
 */
bool bst_retrieve(const bst_linked *source, const data_type *key,
                  data_type *item);

/**
 * Removes and returns a value matching key in source into item.
 *
 * @param source - pointer to a BST
 * @param key - key value to search for
 * @param item - pointer to copy of the item removed
 * @return - true if item removed, false otherwise (key not found)
 */
bool bst_remove(bst_linked *source, const data_type *key, data_type *item);

/**
 * Copies source to target.
 *
 * @param target - pointer to a BST
 * @param source - pointer to a BST
 * returns - true if memory assigned to target, false otherwise
 */
bool bst_copy(bst_linked **target, const bst_linked *source);

/**
 * Copies the contents of source to an array in inorder.
 *
 * @param source - pointer to a BST
 * @param items - array of items: length must be at least the count of items in
 * source
 */
void bst_inorder(const bst_linked *source, data_type *items);

/**
 * Copies the contents of source to an array in preorder.
 *
 * @param source - pointer to a BST
 * @param items - array of items: length must be at least the count of items in
 * source
 */
void bst_preorder(const bst_linked *source, data_type *items);

/**
 * Copies the contents of source to an array in postorder.
 *
 * @param source - pointer to a BST
 * @param items - array of items: length must be at least the count of items in
 * source
 */
void bst_postorder(const bst_linked *source, data_type *items);

/**
 * Retrieves a copy of the maximum value in source.
 *
 * @param source - pointer to a BST
 * @return - true if a maximum value is found, false otherwise (source is empty)
 */
bool bst_max(const bst_linked *source, data_type *item);

/**
 * Retrieves a copy of the minimum value in source.
 *
 * @param source - pointer to a BST
 * @return - true if a minimum value is found, false otherwise (source is empty)
 */
bool bst_min(const bst_linked *source, data_type *item);

/**
 * Finds the number of leaf nodes in source.
 *
 * @param source - pointer to a BST
 * @return - count of nodes with no children.
 */
int bst_leaf_count(const bst_linked *source);

/**
 * Finds the number of nodes with one child in source.
 *
 * @param source - pointer to a BST
 * @return - count of nodes with one child.
 */
int bst_one_child_count(const bst_linked *source);

/**
 * Finds the number of nodes with two children in source.
 *
 * @param source - pointer to a BST
 * @return - count of nodes with two children
 */
int bst_two_child_count(const bst_linked *source);

/**
 * Determines the number of nodes with zero, one, and two children in source.
 * (May not call bst_leaf_count, bst_one_child_count, or bst_two_child_count.)
 *
 * @param source - pointer to a BST
 * @param zero - count of leaf nodes (no children)
 * @param one - count of nodes with one child
 * @param two - count of nodes with two children
 */
void bst_node_counts(const bst_linked *source, int *zero, int *one, int *two);

/**
 * Determines whether or not source is a balanced tree.
 * All node heights are no more than one greater than any child heights.
 *
 * @param source - pointer to a BST
 * @return - true if source is balanced, false otherwise
 */
bool bst_balanced(const bst_linked *source);

/**
 * Determines whether or not source is a valid BST.
 *
 * @param source - pointer to a BST
 * @return - true if source is valid, false otherwise
 */
bool bst_valid(const bst_linked *source);

/**
 * Determines if source and target contain the same values in same
 * configuration.
 *
 * @param target - pointer to a BST
 * @param source - pointer to a BST
 * @return - true if target is identical to source, false otherwise
 */
bool bst_equal(const bst_linked *target, const bst_linked *source);

/**
 * Prints the items in source in preorder.
 *
 * @param source - pointer to a BST
 */
void bst_print(const bst_linked *source);

#endif /* BST_LINKED_H_ */
