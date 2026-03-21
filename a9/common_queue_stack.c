#include "common_queue_stack.h"

#include <ctype.h>
#include <stdlib.h>

NODE *new_node(int data, int type) {
  NODE *np = (NODE *)malloc(sizeof(NODE));

  if (np != NULL) {
    np->data = data;
    np->type = type;
    np->next = NULL;
  }
  return np;
}

void clean(NODE **npp) {
  if (npp == NULL) {
    return;
  }

  NODE *np = *npp;

  while (np != NULL) {
    NODE *tmp = np;
    np = np->next;
    free(tmp);
  }
  *npp = NULL;
}

void display(NODE *np) {
  while (np != NULL) {
    if (np->type == 0) {
      printf("%d", np->data);
    } else {
      printf("%c", np->data);
    }

    np = np->next;
    if (np != NULL) {
      printf(" ");
    }
  }
}

int mytype(char c) {
  if (isdigit((unsigned char)c)) {
    return 0;
  }
  if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%') {
    return 1;
  }
  if (c == '(') {
    return 2;
  }
  if (c == ')') {
    return 3;
  }
  if (isalpha((unsigned char)c)) {
    return 4;
  }
  if (isspace((unsigned char)c)) {
    return 5;
  }
  return -1;
}

int priority(char op) {
  if (op == '*' || op == '/' || op == '%') {
    return 1;
  }
  if (op == '+' || op == '-') {
    return 0;
  }
  return -1;
}

void enqueue(QUEUE *qp, NODE *np) {
  if (qp == NULL || np == NULL) {
    return;
  }

  np->next = NULL;

  if (qp->length == 0) {
    qp->front = np;
    qp->rear = np;
  } else {
    qp->rear->next = np;
    qp->rear = np;
  }
  qp->length++;
}

NODE *dequeue(QUEUE *qp) {
  if (qp == NULL || qp->length == 0 || qp->front == NULL) {
    return NULL;
  }

  NODE *np = qp->front;
  qp->front = np->next;
  np->next = NULL;
  qp->length--;

  if (qp->length == 0) {
    qp->rear = NULL;
  }
  return np;
}

void clean_queue(QUEUE *qp) {
  if (qp == NULL) {
    return;
  }

  while (qp->length > 0) {
    NODE *np = dequeue(qp);
    free(np);
  }
}

void push(STACK *sp, NODE *np) {
  if (sp == NULL || np == NULL) {
    return;
  }

  np->next = sp->top;
  sp->top = np;
  sp->length++;
}

NODE *pop(STACK *sp) {
  if (sp == NULL || sp->length == 0 || sp->top == NULL) {
    return NULL;
  }

  NODE *np = sp->top;
  sp->top = np->next;
  np->next = NULL;
  sp->length--;
  return np;
}

void clean_stack(STACK *sp) {
  if (sp == NULL) {
    return;
  }

  while (sp->length > 0) {
    NODE *np = pop(sp);
    free(np);
  }
}
