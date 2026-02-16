/** @file  food_utilities.h
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 * DO NOT CHANGE CONTENTS
 */
#ifndef FOOD_UTILITIES_H_
#define FOOD_UTILITIES_H_

#include "food.h"

// ==============================================================================================
// Definitions

#define FOODS_CAPACITY 20

/** food array structure\n
 * Array initialized to FOODS_CAPACITY when memory allocated to array at declaration
 */
typedef struct {
/** current capacity of the items array */
    int capacity;
/** number of food items */
    int count;
/** pointer to food items array */
    food_struct items[FOODS_CAPACITY];
} food_array;

// ==============================================================================================
// Prototypes

/**
 * Initializes a food_array object.
 *
 * @param source  - pointer to a food_array object
 */
void food_array_init(food_array *source);

/**
 * Read a food object from the keyboard.
 *
 * @param source - pointer to food object
 */
void food_get(food_struct *source);

/**
 * Initialize a food object from delimited string data. String is in format:
 * "Lasagna|7|false|135"
 *
 * @param source - pointer to food object
 * @param line - delimited string of food data
 * @return - true if food data is properly read
 */
bool food_read(food_struct *source, const char *line);

/**
 * Read a file of formatted food string data into an array of food objects.
 * Size of array is increased as necessary to fit all objects in data file
 * into source.
 *
 * @param fp - pointer to food data file open for reading
 * @param source - pointer to foods array structure
 */
void foods_read(FILE *fp, food_array *source);

/**
 * Write a food object to a file.
 *
 * @param fp - pointer to food data file open for writing
 * @param source - pointer to food object
 */
void food_write(FILE *fp, const food_struct *source);

/**
 * Write an array of food objects to a file.
 *
 * @param fp - pointer to food data file open for writing
 * @param source - pointer to foods structure
 */
void foods_write(FILE *fp, const food_array *source);

/**
 * Copy all vegetarian foods in source to target.
 *
 * @param source - pointer to array of food objects
 * @param target - pointer to array of food objects
 */
void foods_get_vegetarian(const food_array *source, food_array *target);

/**
 * Copy all foods of type origin in source to target.
 *
 * @param source - pointer to array of food objects
 * @param target - pointer to array of food objects
 * @param origin - origin value to compare against
 */
void foods_get_origin(const food_array *source, food_array *target, int origin);

#endif /* FOOD_UTILITIES_H_ */
