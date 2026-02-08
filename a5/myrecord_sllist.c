#include "myrecord_sllist.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 19

/**
 * Search singly linked list by the key name.
 *
 * @param SLL *sllp - provides the address of a singly linked list structure.
 * @param char *name - key to search
 * @return Pointer to found node if found; otherwise NULL
 */
NODE *sll_search(SLL *sllp, char *name) {
  if (name == NULL || sllp == NULL || sllp->start == NULL) {
    return NULL;
  }
  NODE *current = sllp->start;
  while (current != NULL) {
    if (strcmp(current->data.name, name) == 0) {
      return current;
    }
    current = current->next;
  }
  return NULL;
}

/**
 * Insert a new record to linked list at the position sorted by record name
 * field.
 *
 * @param SLL *sllp - provides the address of a singly linked list structure.
 * @param char *name - name field of the new record.
 * @param float score - the score data of the new record.
 */
void sll_insert(SLL *sllp, char *name, float score) {

  if (sllp == NULL || name == NULL) {
    return;
  }
  NODE *node = malloc(sizeof(NODE));
  if (node == NULL) {
    return;
  }

  strncpy(node->data.name, name, MAX_NAME);
  node->data.name[MAX_NAME] = '\0';
  node->data.score = score;
  node->next = NULL;

  if (sllp->start == NULL ||
      strcmp(node->data.name, sllp->start->data.name) <= 0) {
    node->next = sllp->start;
    sllp->start = node;
    sllp->length++;
    return;
  }
  NODE *curr = sllp->start->next;
  NODE *prev = sllp->start;

  while (curr != NULL && strcmp(curr->data.name, node->data.name) < 0) {
    prev = curr;
    curr = curr->next;
  }

  prev->next = node;
  node->next = curr;
  sllp->length += 1;
  return;
}

/**
 * Delete a node of record matched by the name key from linked list.
 *
 * @param SLL *sllp provides the address of a singly linked list structure.
 * @param name - key used to find the node for deletion.
 * @return 1 if deleted a matched node, 0 otherwise.
 */
int sll_delete(SLL *sllp, char *name) {
  if (sllp == NULL || sllp->start == NULL || name == NULL)
    return 0;

  NODE *curr = sllp->start;
  NODE *prev;

  if (strcmp(name, curr->data.name) == 0) {
    sllp->start = curr->next;
    curr->next = NULL;
    free(curr);
    sllp->length--;
    return 1;
  }
  while (curr != NULL && strcmp(name, curr->data.name) != 0) {
    prev = curr;
    curr = curr->next;
  }

  if (curr == NULL)
    return 0;

  prev->next = curr->next;
  curr->next = NULL;
  free(curr);
  sllp->length--;

  return 1;
}

/**
 * Clean singly linked list, delete all nodes.
 * @param @param SLL *sllp provides the address of a singly linked list
 * structure.
 */
void sll_clean(SLL *sllp) {

  if (sllp == NULL || sllp->start == NULL)
    return;

  NODE *curr = sllp->start;
  while (curr != NULL) {
    NODE *next = curr->next;
    free(curr);
    curr = next;
  }
  sllp->length = 0;
  sllp->start = NULL;
  return;
}