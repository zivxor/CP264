/** @file  name_set.h
 * -------------------------------------
 * @author Heider Ali, 999999999, heali@wlu.ca
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 */
#ifndef NAME_SET_H_
#define NAME_SET_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ==============================================================================================
// Definitions

/** converts bool to a string constant */
#define BOOL_STR(x) ((x) ? "true" : "false")
#define NAME_LEN 41 // Max. size of first and last name fields +end byte.

// =============================================================================
// Structures

/**
 * name_set node structure.
 */
typedef struct NAME_NODE {
  /** person's first name */
  char first_name[NAME_LEN]; // .
                             /** person's last  name */
  char last_name[NAME_LEN];
  /** pointer to next name node */
  struct NAME_NODE *next;
} name_node;

/**
 * name_set header structure
 */
typedef struct {
  /** pointer to first node of name_set */
  name_node *front; // Pointer to first node of name_set.
                    /** pointer to last node of name_set */
  name_node *rear;  // Pointer to last  node of name_set.
                    /** count of nodes in name_set */
  int count;
} name_set;

// =============================================================================
// Prototypes

/**
 * Initializes and returns an empty name_set.
 * An empty name_set has front and rear pointers set to NULL and
 * count initialized to zero.
 *
 * @returns - pointer to an initialized name_set
 */
name_set *name_set_initialize();

/**
 * Frees all of the nodes in source, including the header node.
 * Returns a count of the number of nodes freed, including the header node.
 *
 * @param source - pointer to an initialized name_set
 * @return - number of nodes freed
 */
int name_set_free(name_set **source);

/**
 * Print the contents of the linked set of names, one name per line in the
 * format:<br/> last name, first name<br/> ex:<br/> Brown, David
 *
 * @param source - pointer to an initialized name_set
 */
void name_set_print(const name_set *source);

/**
 * Appends a name to sourcer, but only if the name is not already present in
 * source. That is, only unique names are inserted.
 *
 * @param source - pointer to an initialized name_set
 * @param first_name - a first name string
 * @param last_name - a last name string
 * @return - true if the name was appended, false otherwise
 */
bool name_set_append(name_set *source, const char *first_name,
                     const char *last_name);

/**
 * Determines if a name is already in a name_set.
 *
 * @param source - pointer to an initialized name_set
 * @param first_name - a first name string
 * @param last_name - a last name string
 * @return - true if the name in set, false otherwise
 */
bool name_set_contains(const name_set *source, const char *first_name,
                       const char *last_name);

/**
 *
 * @param source - pointer to an initialized name_set
 * @return number of name in source
 */
int name_set_count(const name_set *source);

#endif
