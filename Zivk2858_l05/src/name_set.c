/** @file  name_set.c
 * -------------------------------------
 * @author your name, your ID, your email
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 */
#include "name_set.h"
#include <stdio.h>
#include <stdlib.h>

// ==============================================================================================
// Functions

name_set *name_set_initialize() {

  name_set *set = malloc(sizeof(name_set));
  if (set == NULL)
    return NULL;
  set->front = NULL;
  set->rear = NULL;
  set->count = 0;

  return set;
}

int name_set_free(name_set **source) {
  if (*source == NULL)
    return 0;

  int count = 1;
  name_node *current = (*source)->front;
  while (current != NULL) {
    name_node *temp = current;
    current = current->next;
    free(temp);
    count++;
  }

  free(*source);
  *source = NULL;
  return count;
}

bool name_set_append(name_set *source, const char *first_name,
                     const char *last_name) {
  if (source == NULL || first_name == NULL || last_name == NULL)
    return false;

  // Check for duplicates
  if (name_set_contains(source, first_name, last_name))
    return false;

  name_node *new_node = malloc(sizeof(name_node));
  if (new_node == NULL)
    return false;

  strncpy(new_node->first_name, first_name, NAME_LEN - 1);
  new_node->first_name[NAME_LEN - 1] = '\0';
  strncpy(new_node->last_name, last_name, NAME_LEN - 1);
  new_node->last_name[NAME_LEN - 1] = '\0';
  new_node->next = NULL;

  if (source->front == NULL) {
    source->front = new_node;
    source->rear = new_node;
  } else {
    source->rear->next = new_node;
    source->rear = new_node;
  }

  source->count++;
  return true;
}

bool name_set_contains(const name_set *source, const char *first_name,
                       const char *last_name) {

  if (source == NULL || source->front == NULL || first_name == NULL ||
      last_name == NULL) {
    return false;
  }

  name_node *current = source->front;
  while (current != NULL) {
    if (strcmp(current->first_name, first_name) == 0 &&
        strcmp(current->last_name, last_name) == 0) {
      return true;
    }
    current = current->next;
  }
  return false;
}

int name_set_count(const name_set *source) {

  if (source == NULL) {
    return 0;
  }
  return source->count;
}

void name_set_print(const name_set *source) {
  if (source == NULL || source->front == NULL) {
    return;
  }
  // Set node to point to the first node in the set.
  name_node *node = source->front;

  // Traverse the set.
  while (node != NULL) {
    printf("%s, %s\n", node->last_name, node->first_name);
    // Update the pointer to the next node.
    node = node->next;
  }
  return;
}
