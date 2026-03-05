/** @file  data.h
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 * Comment out data types not in use.
 * data_type is defined as an alias to an external data type.
 */
#ifndef DATA_H_
#define DATA_H_

#define BOOL_STR(x) ((x)?"true":"false")  // converts bool type to string

#define USE_INT
//#define USE_FOOD

#ifdef USE_INT

// ========================================
// Definitions for integer data

#include "int_data.h"

// defines 'data_type' as an alias to some other type.
typedef int_struct data_type;

// defines aliases for 'data_type' functions
#define data_copy(x, y) int_copy(x, y)
#define data_string(x, y, z) int_string(x, y, z)
#define data_compare(x, y) int_compare(x, y)

#endif

#ifdef USE_FOOD

// ========================================
// Definitions for food data

#include "food_utilities.h"

#define DATA_STRING_SIZE 2048

// defines 'data_type' as an alias to some other type.
typedef food_struct data_type;

// defines aliases for 'data_type' functions
#define data_copy(x, y) food_copy(x, y)
#define data_string(x, y, z) food_string(x, y, z)
#define data_compare(x, y) food_compare(x, y)

#endif

#endif /* DATA_H_ */
