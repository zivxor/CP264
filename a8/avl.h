#ifndef AVL_H_
#define AVL_H_

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

/* Get the height of AVL tree
 * @param np - pointer to the root of tree
 * @return - the height value at root.
 */
int height(AVLNODE *root);

/* Return the balance factor at the given node
 * @param np - pointer to the node of tree
 * @return - the balance factor of the node pointed by np.
 */
int balance_factor(AVLNODE *np);

/* Create and return AVLNODE of given data
 * Use malloc()
 * @param data - data for the new node.
 * @return - pointer to the new AVLNODE.
 */
AVLNODE *avl_node(RECORD data);

/* Search AVL tree by key matching data.name
 * @param root - pointer to tree root.
 * @param key - key to match with data.name for search
 * @return - node pointer if found, otherwise NULL
 */
AVLNODE *avl_search(AVLNODE *root, char *key);

/* Insert a node of given record data into AVL tree.
 * Try to use iterative algorithm. 
 *
 * @param rootp - pointer of pointer to tree root.
 * @param data  - record data for the new node.
 */
void avl_insert(AVLNODE **rootp, RECORD data);

/* Delete a node of data.name matched with given key from AVL tree.
 * Try to use iterative algorithm
 * 
 * @param rootp - pointer of pointer to tree root.
 * @param key -   key to match with data.name for deletion.
 */
void avl_delete(AVLNODE **rootp, char *key);

/* This function clean AVL tree.
 * @param rootp - pointer of pointer of tree root.
 */
void avl_clean(AVLNODE **rootp);

#endif /* AVL_H_ */