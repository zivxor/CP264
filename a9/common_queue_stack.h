#ifndef COMMON_QUEUE_STACK_H
#define COMMON_QUEUE_STACK_H

#include <stdio.h>

/*
 Node structure of linked list queue and stack for postfix expression operations.
 int data - represent operand, operator, or parenthesis according to the type.
 int type - 0:operand; 1:operator; 2:left parenthesis; 3:right parenthesis.
 */
typedef struct node {
  int data;
  int type;
  struct node *next;
} NODE;

/* Linked queue type. */
typedef struct queue {
  int length;
  NODE *front;
  NODE *rear;
} QUEUE;

/* Linked stack type. */
typedef struct stack {
  int length;
  NODE *top;
} STACK;

NODE *new_node(int data, int type);
void clean(NODE **npp);
void display(NODE *np);
int mytype(char c);
int priority(char op);

void enqueue(QUEUE *qp, NODE *np);
NODE *dequeue(QUEUE *qp);
void clean_queue(QUEUE *qp);

void push(STACK *sp, NODE *np);
NODE *pop(STACK *sp);
void clean_stack(STACK *sp);

#endif
