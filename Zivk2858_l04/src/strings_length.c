/** @file  strings_length.c
 * -------------------------------------
 * @author Luka Zivkovic, 169102858, zivk2858@mylaurier.ca
 *
 * @version 2026-02-03
 *
 * -------------------------------------
 */
#include "functions.h"

void strings_length(strings_array *source, FILE *fp_short, FILE *fp_long,
                    int length) {
    for (int i = 0; i < source->count; i++) {
        int str_length = strlen(source->strings[i]);
        if (str_length < length) {
            fprintf(fp_short, "%s\n", source->strings[i]);
        } else {
            fprintf(fp_long, "%s\n", source->strings[i]);
        }
    }
}
