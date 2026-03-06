#include "expression_tree.h"
#include <stdio.h>
#include <stdlib.h>

/* Compute and return the TINFO value of a tree.
 * @param root - pointer to the root of a tree
 * @return - number of nodes and height in TINFO type.
 */
TINFO tree_info(TNODE *root) {
  TINFO info;
  info.order = 0;
  info.height = 0;
  if (root == NULL) {
    return info;
  }
  TINFO left_info = tree_info(root->left);
  TINFO right_info = tree_info(root->right);
  info.order = left_info.order + right_info.order + 1;
  info.height = (left_info.height > right_info.height ? left_info.height
                                                      : right_info.height) +
                1;
  return info;
}

/* Display the node data of the tree in pre-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */
void preorder(TNODE *root) {
  if (root == NULL) {
    return;
  }
  print_node(root);
  preorder(root->left);
  preorder(root->right);
}

/* Display the node data of the tree in in-order and format "%c".
 *
 *  @param root - pointer to the root of a tree
 */
void inorder(TNODE *root) {
  if (root == NULL) {
    return;
  }
  inorder(root->left);
  print_node(root);
  inorder(root->right);
}

/* Display the node data of the tree in post-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */
void postorder(TNODE *root) {
  if (root == NULL) {
    return;
  }
  postorder(root->left);
  postorder(root->right);
  print_node(root);
}

/* Display the node data of the tree in breadth-first-order and format "%c ".
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 */
void bforder(TNODE *root) {
  if (root == NULL) {
    return;
  }
  TNODE **queue = malloc(sizeof(TNODE *) * 100); // Assuming max 100 nodes
  int front = 0;
  int rear = 0;
  queue[rear++] = root;
  while (front < rear) {
    TNODE *current = queue[front++];
    print_node(current);
    if (current->left != NULL) {
      queue[rear++] = current->left;
    }
    if (current->right != NULL) {
      queue[rear++] = current->right;
    }
  }
  free(queue);
}

/*  Display the node data of the tree in infix expression format.
 *  Required to add parentheses for operator nodes.
 *  @param root - pointer to the root of a tree
 */
void display_infix(TNODE *root) {
  if (root == NULL) {
    return;
  }
  if (root->data.type == 1) { // Operator
    printf("(");
  }
  display_infix(root->left);
  print_node(root);
  display_infix(root->right);
  if (root->data.type == 1) { // Operator
    printf(")");
  }
}

/* Evaluate the value of a tree expression and return the result.
 * Required to use recursive algorithm.
 *
 *  @param root - pointer to the root of a tree
 *
 *  @return  - the evaluated result of a tree expression
 */
int evaluate_tree(TNODE *root) {
  if (root == NULL) {
    return 0;
  }
  if (root->data.type == 0) { // Operand
    return root->data.value;
  }
  int left_val = evaluate_tree(root->left);
  int right_val = evaluate_tree(root->right);
  switch (root->data.value) {
  case '+':
    return left_val + right_val;
  case '-':
    return left_val - right_val;
  case '*':
    return left_val * right_val;
  case '/':
    return left_val / right_val; // Assuming no division by zero
  default:
    return 0; // Invalid operator
  }
}

/* Search by key using breadth-first-search algorithm
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key -  search key to match with the node data.value
 *
 *  @return  - the found node pointer if fount, otherwise NULL
 */
TNODE *bfs(TNODE *root, int key) {
  if (root == NULL) {
    return NULL;
  }
  TNODE **queue = malloc(sizeof(TNODE *) * 100); // Assuming max 100 nodes
  int front = 0;
  int rear = 0;
  queue[rear++] = root;
  while (front < rear) {
    TNODE *current = queue[front++];
    if (current->data.value == key) {
      free(queue);
      return current;
    }
    if (current->left != NULL) {
      queue[rear++] = current->left;
    }
    if (current->right != NULL) {
      queue[rear++] = current->right;
    }
  }
  free(queue);
  return NULL; // Not found
}

/* Search by key using depth-first-search algorithm.
 * Required to use auxiliary stack and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key -  search key to match with the node data.value
 *
 *  @return  - the found node pointer if fount, otherwise NULL
 */
TNODE *dfs(TNODE *root, int key) {
  if (root == NULL) {
    return NULL;
  }
  TNODE **stack = malloc(sizeof(TNODE *) * 100); // Assuming max 100 nodes
  int top = -1;
  stack[++top] = root;
  while (top >= 0) {
    TNODE *current = stack[top--];
    if (current->data.value == key) {
      free(stack);
      return current;
    }
    if (current->right !=
        NULL) { // Push right first for left to be processed first
      stack[++top] = current->right;
    }
    if (current->left != NULL) {
      stack[++top] = current->left;
    }
  }
  free(stack);
  return NULL; // Not found
}

// The following functions are given in a7 help.

/* Create a TNODE node and sets the data to value and returns the pointer.
 * Use malloc()
 * @param val - data for the new node
 * @param type - 0 for operand, 1 for operator
 * @return pointer to the new node if successful, otherwise NULL
 */
TNODE *tree_node(DATA data) {
  TNODE *new_node = malloc(sizeof(TNODE));
  if (new_node == NULL) {
    return NULL;
  }
  new_node->data = data;
  new_node->left = NULL;
  new_node->right = NULL;
  return new_node;
}

/* This function displays the node data in format "%d " for operand
 * and "%c " for operator.
 * @param node - pointer to the node to be printed
 */
void print_node(TNODE *node) {
  if (node->data.type == 0) { // Operand
    printf("%d ", node->data.value);
  } else { // Operator
    printf("%c ", node->data.value);
  }
}

/* This function cleans a tree.
 * @param rootp - pointer of pointer to the tree root
 */
void clean_tree(TNODE **rootp) {
  if (rootp == NULL || *rootp == NULL) {
    return;
  }
  clean_tree(&(*rootp)->left);
  clean_tree(&(*rootp)->right);
  free(*rootp);
  *rootp = NULL;
}

/* This function creates a new node of given value and inserts it into a tree
 * at the first available position in order of breadth-first and left to right.
 *
 * @param rootp - pointer of pointer to the tree node.
 * @param val - data for the new node.
 * @param type - 0 for operand, 1 for operator
 */
void insert_tree(TNODE **rootp, DATA data) {
  TNODE *new_node = tree_node(data);
  if (new_node == NULL) {
    return; // Memory allocation failed
  }
  if (*rootp == NULL) {
    *rootp = new_node;
    return;
  }
  TNODE **queue = malloc(sizeof(TNODE *) * 100); // Assuming max 100 nodes
  int front = 0;
  int rear = 0;
  queue[rear++] = *rootp;
  while (front < rear) {
    TNODE *current = queue[front++];
    if (current->left == NULL) {
      current->left = new_node;
      break;
    } else {
      queue[rear++] = current->left;
    }
    if (current->right == NULL) {
      current->right = new_node;
      break;
    } else {
      queue[rear++] = current->right;
    }
  }
  free(queue);
}