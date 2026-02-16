/** @file  stack_linked.h
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 * DO NOT CHANGE CONTENTS
 */
#ifndef STACK_LINKED_H_
#define STACK_LINKED_H_

// ==============================================================================================
// Includes

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "data.h"

// ==============================================================================================
// Structures

/**
 * Stack node.
 */
typedef struct STACK_NODE {
/** Node data */
    data_type item;
/** Pointer to the next stack node */
    struct STACK_NODE *next;
} stack_node;

/**
 * Stack header.
 */
typedef struct {
/** Pointer to the top node of the stack */
    stack_node *top;
} stack_linked;

// ==============================================================================================
// Prototypes

/**
 * Initializes an empty stack.\n
 * top is initialized to NULL.
 *
 * @return - pointer to a stack, NULL if memory cannot be allocated
 */
stack_linked* stack_initialize();

/**
 * Destroys a stack.\n
 * Releases all memory from all nodes including header node.
 * source must be reinitialized to be used.
 *
 * @param source - pointer to a stack
 */
void stack_destroy(stack_linked **source);

/**
 * Determines if source is empty.
 *
 * @param source - pointer to a stack
 * @return - true if source is empty, false otherwise
 */
bool stack_empty(const stack_linked *source);

/**
 * Pushes a copy of item onto the top of source. Increments top.
 *
 * @param source - pointer to a stack
 * @param item - pointer to item to push
 * @return - true if copy of item pushed, false otherwise
 */
bool stack_push(stack_linked *source, const data_type *item);

/**
 * Returns a copy of the item on the top of source, source is unchanged.
 *
 * @param source - pointer to a stack
 * @param item - pointer to a copy of the item to retrieve
 * @return - true if item peeked, false otherwise (source is empty)
 */
bool stack_peek(const stack_linked *source, data_type *item);

/**
 * Removes and returns the item at the top of source. Decrements top.
 * If the last item is popped, top is set to NULL.
 *
 * @param source - pointer to a stack
 * @param item - pointer to item to popped item
 * @return - true if top item popped, false otherwise (source is empty)
 */
bool stack_pop(stack_linked *source, data_type *item);

/**
 * Compares two stacks for equality. Stacks are equal if they contain equivalent items
 * in the same order.
 *
 * @param source - the first stack to compare
 * @param target - the second stack to compare
 * @return - true if stacks are identical, false otherwise
 */
bool stack_equal(const stack_linked *source, const stack_linked *target);

/**
 * Copies contents of source to target. target is destroyed and reinitialized
 * if necessary.
 *
 * @param target - the stack to copy to
 * @param source - the stack to copy from
 * @return - true if source is copied to target, false otherwise
 */
bool stack_copy(stack_linked **target, const stack_linked *source);

/**
 * Combines the contents of two source stacks into a target stack. Items alternate.
 * Source stacks are empty (not destroyed) when the function completes.
 * Moves nodes, not data.
 *
 * @param target - pointer to target stack
 * @param source1 - pointer to first source stack
 * @param source2 - pointer to second source stack
 */
void stack_combine(stack_linked *target, stack_linked *source1, stack_linked *source2);

/**
 * Splits a source stack alternately into two target stacks. Items alternate.
 * Source stack is empty (not destroyed) when function completes.
 * Moves nodes, not data.
 *
 * @param target1 - pointer to first target stack
 * @param target2 - pointer to second target stack
 * @param source - pointer to source stack
 */
void stack_split_alt(stack_linked *target1, stack_linked *target2, stack_linked *source);

/**
 * Prints the items in source from top to bottom of stack.
 * (For testing only).
 *
 * @param source - pointer to a stack
 */
void stack_print(const stack_linked *source);

#endif /* STACK_LINKED_H_ */
