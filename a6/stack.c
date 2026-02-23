#include "common.h"
#include <stdio.h>
#include <stdlib.h>
/*
 * Define a structure STACK containing the length and pointer of the top node.
 * int length - maintains the length of stack.
 * NODE *top - pointer to the top node of linked list stack
 */
typedef struct stack {
  int length;
  NODE *top;
} STACK;

/*
 * Push a node into a linked list stack
 * @param STACK *sp - pointer to the stack
 * @param NODE *np - pointer to the node.
 */
void push(STACK *sp, NODE *np) {
  if (sp == NULL || np == NULL) {
    return;
  }
  if (sp->top == NULL) {
    sp->top = np;
    sp->length++;
    return;
  }
  np->next = sp->top;
  sp->top = np;
  sp->length++;
}

/*
 * Pop and return the pointer of the removed top node
 * @param STACK *sp - pointer to the stack
 * @return - the reference of the removed node and set it's next to NULL
 */
NODE *pop(STACK *sp) {
  if (sp == NULL || sp->top == NULL) {
    return NULL;
  }
  NODE *temp = sp->top;
  sp->top = sp->top->next;
  temp->next = NULL;
  sp->length--;
  return temp;
}

/*
 * clean the linked list stack
 */
void clean_stack(STACK *sp) {
  while (sp->length > 0) {
    NODE *temp = pop(sp);
    free(temp);
  }
}