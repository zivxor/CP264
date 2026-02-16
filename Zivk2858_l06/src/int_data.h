/** @file  int_data.h
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 * DO NOT CHANGE CONTENTS
 */
#ifndef INT_DATA_
#define INT_DATA_

// ==============================================================================================
// Includes

#include <stdio.h>
#include <stdlib.h>

// ==============================================================================================
// Structures

typedef struct {
    int value;
} int_struct;

// ==============================================================================================
// Prototypes

/**
 * Copies source integer to target integer.
 *
 * @param target - pointer to target int structure
 * @param source - pointer to source int structure
 */
void int_copy(int_struct *target, const int_struct *source);

/**
 * Create a formatted string of an int structure.
 *
 * @param string - destination string
 * @param size - maximum size of destination string
 * @param source - pointer to int structure
 * @return - number of characters in string
 */
int int_string(char *string, size_t size, const int_struct *source);

/**
 * Compares two integers.
 *
 * @param source - pointer to int structure
 * @param target - pointer to int structure
 * @return - 0 if source == target, < 0 if source < target, > 0 if source > target.
 */
int int_compare(const int_struct *source, const int_struct *target);

void int_from_string(int_struct *target, const char *source);

#endif /* INT_DATA_ */
