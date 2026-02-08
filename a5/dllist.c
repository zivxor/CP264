#include "dllist.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Create and return a new double linked list node using malloc()
 * with passed data value and returns pointer to the new node.
 */
NODE *dll_node(char value) {
  NODE *new = malloc(sizeof(NODE));
  if (new == NULL) {
    return NULL;
  }
  new->data = value;
  new->next = NULL;
  new->prev = NULL;
  return new;
}

/*
 * Insert a given node at the beginning the of a doubly linked list.
 * @param DLL *dllp -  reference to input DLL variable
 * @param NODE *np  -  reference of a NODE node to be inserted
 */
void dll_insert_start(DLL *dllp, NODE *np) {
  if (dllp == NULL || np == NULL) {
    return;
  }
  if (dllp->start == NULL) {
    dllp->start = np;
    dllp->end = np;
    dllp->end->next = NULL;
    dllp->start->prev = NULL;
    dllp->length++;
    return;
  }
  np->next = dllp->start;
  dllp->start->prev = np;
  dllp->start = np;
  dllp->start->prev = NULL;
  dllp->length++;
  return;
}
/*
 * Insert a node at the end of a doubly linked list.
 * @param DLL *dllp -  reference to input DLL variable
 * @param NODE *np  -  reference of a NODE node to be inserted
 */
void dll_insert_end(DLL *dllp, NODE *np) {
  if (dllp == NULL || np == NULL) {
    return;
  }

  if (dllp->start == NULL) {
    dllp->start = np;
    dllp->end = np;
    dllp->end->next = NULL;
    dllp->start->prev = NULL;
    dllp->length++;
    return;
  }

  NODE *curr = dllp->end;
  curr->next = np;
  np->prev = curr;
  np->next = NULL;
  dllp->end = np;
  dllp->length++;
  return;
}
/*
 * This deletes the first node of a doubly linked list.
 * @param DLL *dllp -  reference to input DLL variable
 */
void dll_delete_start(DLL *dllp) {
  if (dllp == NULL || dllp->start == NULL) {
    return;
  }
  if (dllp->start == dllp->end) {
    free(dllp->start);
    dllp->length = 0;
    dllp->start = NULL;
    dllp->end = NULL;
    return;
  }

  dllp->start = dllp->start->next;
  free(dllp->start->prev);
  dllp->start->prev = NULL;
  dllp->length--;
  return;
}
/*
 * Delete the end node of a doubly linked list.
 * @param DLL *dllp -  reference to input DLL variable
 */
void dll_delete_end(DLL *dllp) {
  if (dllp == NULL || dllp->start == NULL) {
    return;
  }
  if (dllp->start == dllp->end) {
    free(dllp->start);
    dllp->length = 0;
    dllp->start = NULL;
    dllp->end = NULL;
    return;
  }
  dllp->end = dllp->end->prev;
  free(dllp->end->next);
  dllp->end->next = NULL;
  dllp->length--;
  return;
}
/*
 * Clean and free the nodes of a doubly linked list and reset start and length.
 * @param DLL *dllp -  reference to input DLL variable
 */
void dll_clean(DLL *dllp) {
  if (dllp == NULL) {
    return;
  }
  if (dllp->start == NULL) {
    dllp->start = NULL;
    dllp->end = NULL;
    dllp->length = 0;
    return;
  }
  NODE *curr = dllp->start;
  while (curr) {
    NODE *next = curr->next;
    free(curr);
    curr = next;
  }
  dllp->start = NULL;
  dllp->end = NULL;
  dllp->length = 0;
  return;
}