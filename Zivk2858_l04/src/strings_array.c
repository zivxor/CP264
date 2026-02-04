/** @file  strings_array.c
 * -------------------------------------
 * @author Luka Zivkovic, 169102858, zivk2858@mylaurier.ca
 *
 * @version 2026-02-03
 *
 * -------------------------------------
 */
#include "functions.h"

void initialize_strings_array(strings_array *source, const int capacity) {
  source->count = 0;
  // allocate memory to the 2D strings array attribute
  source->strings = malloc(capacity * sizeof *source->strings);

  if (source->strings != NULL) {
    // if memory allocated, initialize all individual string pointers to NULL
    // individual string memory is allocated when strings read
    for (int i = 0; i < capacity; i++) {
      source->strings[i] = NULL;
    }
    source->capacity = capacity;
  } else {
    // memory could not be allocated
    source->capacity = 0;
  }
  return;
}

void free_strings_array(strings_array *source) {
  // free the memory for the individual strings and set pointers to NULL
  for (int i = 0; i < source->count; i++) {
    free(source->strings[i]);
    source->strings[i] = NULL;
  }
  // free the overall 2D strings array attribute
  free(source->strings);
  source->strings = NULL;
  source->capacity = 0;
  source->count = 0;
  return;
}

void read_strings(strings_array *source, FILE *fp) {
  int lines = 0;
  // chars tracks the number of characters actually read by getline
  ssize_t chars = 1;

  while ((lines < source->capacity) && (chars > -1)) {
    // read until strings array filled or end of file reached
    size_t size = 0;
    // getline assigns as much memory as necessary to store string read from fp
    // returns -1 if end of file is reached or out of memory
    chars = getline(&source->strings[lines], &size, fp);

    if (chars > -1) {
      // trim the '\n' from end of line read
      source->strings[lines][chars - 1] = '\0';
      lines++;
    }
  }
  source->count = lines;
  return;
}
