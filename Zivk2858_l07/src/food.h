/** @file food.h
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 * DO NOT CHANGE CONTENTS
 */
#ifndef FOOD_H_
#define FOOD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// ==============================================================================================
// Definitions

/** converts bool to a string constant */
#define BOOL_STR(x) ((x)?"true":"false")
#define HEADER_WIDTH 11
#define NAME_LENGTH 40
#define LINE_LENGTH 120
#define FOOD_FIELDS 4
#define NAME_HEADER "Name:"
#define ORIGIN_HEADER "Origin:"
#define VEG_HEADER "Vegetarian:"
#define CALORIES_HEADER "Calories:"

// ==============================================================================================
// Externals - contents must be defined in one .c file

extern const char *const ORIGINS[];
extern const int ORIGINS_COUNT;

// ==============================================================================================
// Structures

/** food structure */
typedef struct {
/** food name string, maximum length NAME_LENGTH */
    char name[NAME_LENGTH];
/** index into the food ORIGINS array */
    int origin;
/** whether food is vegetarian */
    bool is_vegetarian;
/** number of calories */
    int calories;
} food_struct;

// ==============================================================================================
// Prototypes

/**
 * Initialize contents of a food object.
 *
 * @param food - pointer to food object
 * @param name - Name of food.
 * @param origin - Origin index.
 * @param is_vegetarian - True if vegetarian, false otherwise.
 * @param calories - number of calories.
 */
void food_init(food_struct *food, const char *const name, int origin, bool is_vegetarian, int calories);

/**
 * Copies contents of source into target.
 *
 * @param target - pointer to food object
 * @param source - pointer to food object
 */
void food_copy(food_struct *target, const food_struct *source);

/**
 * Compare two food objects. foods are compared first by name, then by origin.
 *
 * @param source - pointer to food object
 * @param target - pointer to food object
 * @return - 0 if foods are the same, < 0 if source < target, > 0 if source > target
 */
int food_compare(const food_struct *source, const food_struct *target);

/**
 * Create a formatted string of a food object as (example):
 * Name:       pizza
 * Origin:     Italian
 * Vegetarian: false
 * Calories:   600
 *
 * @param string - destination string
 * @param size - maximum size of destination string
 * @param food - pointer to food object
 * @return - number of characters in string
 */
int food_string(char *string, size_t size, const food_struct *food);

/**
 * Create a formatted string of a food object key data.
 * Consists of the food title and Origin string in the format:
 * "name, origin" (Ex: "pizza, Italian")
 *
 * @param string - destination string
 * @param size - maximum size of destination string
 * @param food - pointer to food object
 * @return - number of characters in string
 */
int food_key(char *string, size_t size, const food_struct *food);

/**
 * Generates a hash value from a food name.
 * The hash is the total of the ASCII values of the
 * characters in the name.
 *
 * @param source - pointer to food object
 * @return - integer hash value for food
 */
int food_hash(const food_struct *source);

/**
 * Copies the contents of the ORIGINS array into a string formatted as:
@verbatim
Origins
 0: Canadian
 1: Chinese
...
10: New Zealand
11: English
@endverbatim
 * Note the right alignment of the id numbers - this is significant.
 * @param string - pointer to string to hold ORIGINS data
 * @param size - the declared size of string
 * @return - the number of characters copied into string
 */
int origins_menu(char *string, size_t size);

#endif /* FOOD_H_ */
