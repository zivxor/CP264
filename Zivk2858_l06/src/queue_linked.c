/** @file  queue_linked.c
 * -------------------------------------
 * @author name, id, email
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 */
//==================================================================================
// Includes
#include "queue_linked.h"

//==================================================================================
// Local Helper Functions

// your code here, if any

//==================================================================================
// Functions

queue_linked *queue_initialize() {

  queue_linked *queue = malloc(sizeof(queue_linked));

  if (queue != NULL) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->count = 0;
  }
  return queue;
}

void queue_destroy(queue_linked **source) {
  if (source == NULL || *source == NULL) {
    return; // nothing to do
  }

  queue_linked *q = *source;
  queue_node *curr = q->front;
  while (curr != NULL) {
    queue_node *next = curr->next;
    free(curr);
    curr = next;
  }

  q->front = NULL;
  q->rear = NULL;
  q->count = 0;

  free(q);
  *source = NULL;
}

bool queue_empty(const queue_linked *source) {
  if (source == NULL || source->front == NULL) {
    return true;
  }
  return false;
}

int queue_count(const queue_linked *source) { return source->count; }

bool queue_insert(queue_linked *source, const data_type *item) {
  queue_node *new = malloc(sizeof(queue_node));
  if (new == NULL) {
    return false;
  }
  if (source == NULL) {
    queue_linked *queue = queue_initialize();
  }
  if (source->front = NULL) {
    source->front = new;
    source->rear = new;
  } else {
    source->rear->next = new;
    source->rear = source->rear->next;
  }
  source->count++;
  return true;
}

bool queue_peek(const queue_linked *source, data_type *item) {
  if (queue_empty(source)) {
    return false;
  }
  queue_node *node = source->front;
  *item = node->item;
  return true;
}

bool queue_remove(queue_linked *source, data_type *item) {

  if (queue_empty(source)) {
    return false;
  }

  *item = source->front->item;
  queue_node *prev = source->front;
  source->front = source->front->next;
  free(prev);
  source->count--;
  return true;
}

bool queue_equal(const queue_linked *source, const queue_linked *target) {

  if (queue_empty(source) && queue_empty(target)) {
    return true;
  }

  return false;
}

bool queue_copy(queue_linked **target, const queue_linked *source) {
  if (source == NULL) {
    return false;
  }
  if ((*target)->front != NULL) {
    queue_destroy(target);
  }
  if (target == NULL) {
    queue_linked *p = queue_initialize();
    target = &p;
  }
  queue_node *curr_source = source->front;
  while (curr_source != NULL) {
    if (!queue_insert(*target, &curr_source->item)) {
      return false;
    }
    curr_source = curr_source->next;
  }
  return true;
}

void queue_append(queue_linked *target, queue_linked *source) {
  if (queue_empty(source)) {
    return;
  }
  if (queue_empty(target)) {
    target->front = source->front;
    target->rear = source->rear;
  } else {
    target->rear->next = source->front;
    target->rear = source->rear;
  }
  target->count += source->count;
  source->front = NULL;
  source->rear = NULL;
  source->count = 0;

  return;
}

void queue_combine(queue_linked *target, queue_linked *source1,
                   queue_linked *source2) {

  if (queue_empty(source1) && queue_empty(source2)) {
    return;
  }
  queue_node *curr1 = source1->front;
  queue_node *curr2 = source2->front;

  while (curr1 != NULL || curr2 != NULL) {
    if (curr1 != NULL) {
      queue_node *next1 = curr1->next;
      curr1->next = NULL;
      if (queue_empty(target)) {
        target->front = curr1;
        target->rear = curr1;
      } else {
        target->rear->next = curr1;
        target->rear = target->rear->next;
      }
      target->count++;
      curr1 = next1;
    }
    if (curr2 != NULL) {
      queue_node *next2 = curr2->next;
      curr2->next = NULL;
      if (queue_empty(target)) {
        target->front = curr2;
        target->rear = curr2;
      } else {
        target->rear->next = curr2;
        target->rear = target->rear->next;
      }
      target->count++;
      curr2 = next2;
    }
  }

  return;
}

void queue_split_alt(queue_linked *target1, queue_linked *target2,
                     queue_linked *source) {

  if (queue_empty(source)) {
    return;
  }

  queue_node *curr = source->front;
  bool toggle = true;

  while (curr != NULL) {
    queue_node *next = curr->next;
    curr->next = NULL;
    if (toggle) {
      if (queue_empty(target1)) {
        target1->front = curr;
        target1->rear = curr;
      } else {
        target1->rear->next = curr;
        target1->rear = target1->rear->next;
      }
      target1->count++;
    } else {
      if (queue_empty(target2)) {
        target2->front = curr;
        target2->rear = curr;
      } else {
        target2->rear->next = curr;
        target2->rear = target2->rear->next;
      }
      target2->count++;
    }
    toggle = !toggle;
    curr = next;
  }

  source->front = NULL;
  source->rear = NULL;
  source->count = 0;

  return;
}

void queue_print(const queue_linked *source) {
  char string[200];
  queue_node *current = source->front;

  while (current != NULL) {
    data_string(string, sizeof string, &current->item);
    printf("%s\n", string);
    current = current->next;
  }
  return;
}
