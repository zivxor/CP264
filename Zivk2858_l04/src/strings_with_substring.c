/** @file  strings_with_substring.c
 * -------------------------------------
 * @author Luka Zivkovic, 169102858, zivk2858@mylaurier.ca
 *
 * @version 2026-02-03
 *
 * -------------------------------------
 */
#include "functions.h"

void strings_with_substring(strings_array *source, char *substr) {
  for (int i = 0; i < source->count; i++) {
    if (strstr(source->strings[i], substr) != NULL) {
      printf("%s\n", source->strings[i]);
    }
  }
}
