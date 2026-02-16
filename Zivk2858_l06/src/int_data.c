/** @file  int_data.c
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 */
// ==============================================================================================
// Includes
#include "int_data.h"

// ==============================================================================================
// Functions

void int_copy(int_struct *target, const int_struct *source) {
    target->value = source->value;
}

int int_string(char *string, size_t size, const int_struct *source) {
    return snprintf(string, size, "%d", source->value);
}

int int_compare(const int_struct *source, const int_struct *target) {
    int result = 0;

    if(source->value < target->value) {
        result = -1;
    } else if(source->value > target->value) {
        result = 1;
    }
    return result;
}
