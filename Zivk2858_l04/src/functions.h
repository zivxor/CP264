/** @file  functions.h
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 * DO NOT CHANGE CONTENTS
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

// =============================================================================
// Structures

typedef struct {
    int capacity;    // maximum capacity of strings
    int count;       // number of lines stored in strings
    char **strings;  // pointer to 2D array of strings
} strings_array;

// =============================================================================
// Prototypes

/**
 * Initializes a strings_array structure. Allocates memory to the strings attribute,
 * sets capacity attribute, sets count attribute to 0.
 *
 * @param source - pointer to a strings_array struct
 * @param capacity - maximum number of strings in source
 */
void initialize_strings_array(strings_array *source, const int capacity);

/**
 * Frees memory from a strings_array variable.
 *
 * @param data - the strings_array struct to free
 */

/**
 * Frees strings attribute memory for all individual strings allocated.
 * Sets capacity and lines attributes to 0.
 *
 * @param source - pointer to a strings_array struct
 */
void free_strings_array(strings_array *source);

/**
 * Reads consecutive lines of text from fp until either the end of file is reached or
 * the capacity is reached. The count attribute is updated to the number of lines read from fp.
 * Each input line is stored in dynamic storage and it is accessed/referenced by the strings array.
 * That is, strings[0] points to the first input line,
 *          strings[1] points to the second input line, and so on.
 *
 * @param source - pointer to a strings_array struct
 * @param fp - input file pointer
 */
void read_strings(strings_array *source, FILE *fp);

/**
 * Traverses every string in source and prints the strings that contain substr. Case must match.
 *
 * @param source - pointer to a strings_array struct
 * @param substr - the substring to search for
 */
void strings_with_substring(strings_array *source, char *substr);

/**
 * Traverses every string in strings and copies all strings shorter than length to the short_lines file,
 * and all strings equal to or longer than length to the long_lines file.
 *
 * @param source - the strings_array struct to traverse
 * @param fp_short - output file pointer
 * @param fp_long - output file pointer
 * @param length - comparison length for strings
 */
void strings_length(strings_array *source, FILE *fp_short, FILE *fp_long, int length);

#endif /* FUNCTIONS_H_ */
