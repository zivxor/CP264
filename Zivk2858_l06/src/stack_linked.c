/** @file  stack_linked.c
 * -------------------------------------
 * @author David Brown, 1234567879, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 */
// Includes
#include "stack_linked.h"

//==================================================================================
// Local Helper Functions

/**
 * If it exists, moves top pointer from source to target.
 *
 * @param target - pointer to target stack
 * @param source - pointer to source stack
 */
static void move_top_to_top(stack_linked *target, stack_linked *source) {

    if(source->top != NULL) {
        // Update source
        stack_node *temp = source->top;
        source->top = source->top->next;
        // Update target
        temp->next = target->top;
        target->top = temp;
    }
    return;
}

//==================================================================================
// Functions

stack_linked* stack_initialize() {
    // Allocate memory to the stack header
    stack_linked *source = malloc(sizeof *source);

    if(source) {
        // Initialize the stack structure
        source->top = NULL;
    }
    // returns NULL if malloc fails
    return source;
}

void stack_destroy(stack_linked **source) {
    stack_node *node = NULL;

    while((*source)->top != NULL) {
        node = (*source)->top;
        (*source)->top = (*source)->top->next;
        free(node);
        node = NULL;
    }
    // destroy the stack header
    free(*source);
    *source = NULL;
    return;
}

bool stack_empty(const stack_linked *source) {
    return source->top == NULL;
}

bool stack_push(stack_linked *source, const data_type *item) {
    bool pushed = false;
    // allocate memory to a new stack node
    stack_node *node = malloc(sizeof *node);

    if(node) {
        // copy the data parameter to the new memory
        data_copy(&node->item, item);
        node->next = source->top;
        source->top = node;
        pushed = true;
    }
    return pushed;
}

bool stack_peek(const stack_linked *source, data_type *item) {
    if(source->top != NULL) {
        data_copy(item, &source->top->item);
    }
    return source->top != NULL;
}

bool stack_pop(stack_linked *source, data_type *item) {
    bool popped = false;

    if(source->top != NULL) {
        stack_node *temp = source->top;
        data_copy(item, &source->top->item);
        source->top = source->top->next;
        free(temp);
        popped = true;
    }
    return popped;
}

bool stack_equal(const stack_linked *source, const stack_linked *target) {
    stack_node *source_node = source->top;
    stack_node *target_node = target->top;

    while(source_node && target_node && (data_compare(&source_node->item, &target_node->item) == 0)) {
        source_node = source_node->next;
        target_node = target_node->next;
    }
    // both nodes must be NULL since they reached the end of the stacks
    return !source_node && !target_node;
}

bool stack_copy(stack_linked **target, const stack_linked *source) {
    stack_destroy(target);
    *target = stack_initialize();

    if(source->top != NULL) {
        stack_node *curr = source->top;

        while(curr != NULL) {
            stack_node *node = malloc(sizeof *node);
            data_copy(&node->item, &curr->item);
            node->next = (*target)->top;
            (*target)->top = node;
            curr = curr->next;
        }
    }
    return target;
}

void stack_combine(stack_linked *target, stack_linked *source1, stack_linked *source2) {
    while((source1->top != NULL) && (source2->top != NULL)) {
        move_top_to_top(target, source1);
        move_top_to_top(target, source2);
    }
    // At most only one of the following loops is executed
    while(source1->top != NULL) {
        move_top_to_top(target, source1);
    }
    while(source2->top != NULL) {
        move_top_to_top(target, source2);
    }
}

void stack_split_alt(stack_linked *target1, stack_linked *target2, stack_linked *source) {
    bool left = true;

    while(source->top != NULL) {
        if(left) {
            move_top_to_top(target1, source);
        } else {
            move_top_to_top(target2, source);
        }
        left = !left;
    }
    return;
}

void stack_print(const stack_linked *source) {
    char string[200];
    stack_node *curr = source->top;

    while(curr != NULL) {
        data_string(string, sizeof string, &curr->item);
        printf("%s\n", string);
        curr = curr->next;
    }
    return;
}
