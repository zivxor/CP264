/** @file  queue_linked.h
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 * DO NOT CHANGE CONTENTS
 */
#ifndef QUEUE_LINKED_H_
#define QUEUE_LINKED_H_

//==================================================================================
// Includes

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "data.h"

//==================================================================================
// Structures

/**
 * Queue node.
 */
typedef struct QUEUE_NODE {
/** Node data */
    data_type item;
/** Pointer to the next queue node */
    struct QUEUE_NODE *next;
} queue_node;

/**
 * Queue header.
 */
typedef struct {
/** Pointer to the front node of the queue */
    queue_node *front;
/** Pointer to the rear node of the queue */
    queue_node *rear;
/** Number of items in queue. */
    int count;
} queue_linked;

// ==============================================================================================
// Prototypes

/**
 * Initializes an empty queue.\n
 * front and rear are initialized to NULL, count to 0.
 *
 * @return - pointer to a queue, NULL if memory cannot be allocated
 */
queue_linked* queue_initialize();

/**
 * Destroys a queue.\n
 * Releases all memory from all nodes including header node.
 * source must be reinitialized to be used.
 *
 * @param source - pointer to a queue
 */
void queue_destroy(queue_linked **source);

/**
 * Determines if source is empty.
 *
 * @param source - pointer to a queue
 * @return - true if source is empty, false otherwise
 */
bool queue_empty(const queue_linked *source);

/**
 * Returns the number of items in source.
 *
 * @param source - pointer to a queue
 * @return - the number of items in source
 */
int queue_count(const queue_linked *source);

/**
 * Adds a copy of item to the rear of source.
 *
 * @param source - pointer to a queue
 * @param item - pointer to the item to insert
 * @return - true if copy of item inserted, false otherwise
 */
bool queue_insert(queue_linked *source, const data_type *item);

/**
 * Returns a copy of the item at the front of source, source is unchanged.
 *
 * @param source - pointer to a queue
 * @param item - pointer to a copy of the item to retrieve
 * @return - true if item peeked, false otherwise (source is empty)
 */
bool queue_peek(const queue_linked *source, data_type *item);

/**
 * Removes and returns the item on the front of a queue.
 *
 * @param source - pointer to a queue
 * @param item - pointer the item to remove
 * @return - true if item removed, false otherwise (source is empty)
 */
bool queue_remove(queue_linked *source, data_type *item);

/**
 * Compares two queues for equality. queues are equal if they contain equivalent items
 * in the same order.
 *
 * @param source - the first queue to compare
 * @param target - the second queue to compare
 * @return - true if queues are identical, false otherwise
 */
bool queue_equal(const queue_linked *source, const queue_linked *target);

/**
 * Copies contents of source to target. target is destroyed and reinitialized
 * if necessary.
 *
 * @param target - the queue to copy to
 * @param source - the queue to copy from
 * @return - true if source is copied to target, false otherwise
 */
bool queue_copy(queue_linked **target, const queue_linked *source);

/**
 * Appends the entire source queue to the rear of the target queue. target need not be empty.
 * The source queue becomes empty (not destroyed) when the function completes.
 * Must move nodes, not data.<br/>
 * (Should not need to use a loop.)
 *
 * @param target - pointer to target queue
 * @param source - pointer to source queue
 */
void queue_append(queue_linked *target, queue_linked *source);

/**
 * Combines the contents of two source queues into a target queue. Items alternate.
 * Source queues are empty (not destroyed) when the function completes.
 * Must move nodes, not data.
 *
 * @param target - pointer to target queue
 * @param source1 - pointer to first source queue
 * @param source2 - pointer to second source queue
 */
void queue_combine(queue_linked *target, queue_linked *source1, queue_linked *source2);

/**
 * Splits a source queue alternately into two target queues. Items alternate.
 * Source queue is empty (not destroyed) when the function completes.
 * Must move nodes, not data.
 *
 * @param target1 - pointer to first target queue
 * @param target2 - pointer to second target queue
 * @param source - pointer to source queue
 */
void queue_split_alt(queue_linked *target1, queue_linked *target2, queue_linked *source);

/**
 * Prints the items in a queue from front to rear.
 * (For testing only).
 *
 * @param source - pointer to a queue
 */
void queue_print(const queue_linked *source);

#endif /* QUEUE_LINKED_H_ */
