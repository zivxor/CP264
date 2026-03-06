typedef struct data {
    int value;
    int type; // 0 for operand, 1 for operator
} DATA;

/* Define node structure of a binary tree
 * data - data field of tree node
 * left - pointer to the left child
 * right - pointer to the right child
*/
typedef struct tnode {
    DATA data;
    struct tnode *left;
    struct tnode *right;
} TNODE;

/* Define a structure to represent tree properties. 
 * order - the number of nodes 
 * height - the height
 */
typedef struct tree_info {
    int order;
    int height;
} TINFO;

/* Compute and return the TINFO value of a tree.
 * @param root - pointer to the root of a tree
 * @return - number of nodes and height in TINFO type.
 */
TINFO tree_info(TNODE *root);

/* Display the node data of the tree in pre-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */
void preorder(TNODE *root);

/* Display the node data of the tree in in-order and format "%c".
 *
 *  @param root - pointer to the root of a tree
 */
void inorder(TNODE *root);

/* Display the node data of the tree in post-order and format "%c ".
 *
 *  @param root - pointer to the root of a tree
 */
void postorder(TNODE *root);

/* Display the node data of the tree in breadth-first-order and format "%c ".
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 */
void bforder(TNODE *root);

/*  Display the node data of the tree in infix expression format.
 *  Required to add parentheses for operator nodes.
 *  @param root - pointer to the root of a tree
 */                 
void display_infix(TNODE *root);

/* Evaluate the value of a tree expression and return the result.
 * Required to use recursive algorithm.
 *
 *  @param root - pointer to the root of a tree
 *
 *  @return  - the evaluated result of a tree expression
*/
int evaluate_tree(TNODE *root);

/* Search by key using breadth-first-search algorithm
 * Required to use auxiliary queue and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key -  search key to match with the node data.value
 *
 *  @return  - the found node pointer if fount, otherwise NULL
 */
TNODE *bfs(TNODE *root, int key);

/* Search by key using depth-first-search algorithm.
 * Required to use auxiliary stack and iterative algorithm.
 *
 *  @param root - pointer to the root of a tree
 *  @param key -  search key to match with the node data.value
 *
 *  @return  - the found node pointer if fount, otherwise NULL
 */
TNODE *dfs(TNODE *root, int key);


// The following functions are given in a7 help.

/* Create a TNODE node and sets the data to value and returns the pointer.
 * Use malloc()
 * @param val - data for the new node
 * @param type - 0 for operand, 1 for operator
 * @return pointer to the new node if successful, otherwise NULL
 */
TNODE *tree_node(DATA data);

/* This function displays the node data in format "%d " for operand  
 * and "%c " for operator.
 * @param node - pointer to the node to be printed
 */
void print_node(TNODE *node);

/* This function cleans a tree.
 * @param rootp - pointer of pointer to the tree root
 */
void clean_tree(TNODE **rootp);

/* This function creates a new node of given value and inserts it into a tree 
 * at the first available position in order of breadth-first and left to right.
 *
 * @param rootp - pointer of pointer to the tree node.
 * @param val - data for the new node.
 * @param type - 0 for operand, 1 for operator
 */
void insert_tree(TNODE **rootp, DATA data);
