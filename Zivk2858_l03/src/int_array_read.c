/**
 * -------------------------------------
 * @file  int_array_read.c
 * -------------------------------------
 * @author Zivkovic Luka, 169102858, Zivk2858@mylaurier.ca
 *
 * @version 2026-01-26
 *
 * -------------------------------------
 */
#include "functions.h"
#include <stdio.h>

void int_array_read(int *array, int size) {
  int count = 0;
  printf("Enter %d values for an array of int.\n", size);
  while (count < size) {
    printf("Value for index %d: ", count);
    int number;
    if (scanf("%d", &number) == 1) {
      *(array + count) = number;
      count++;
    } else {
      printf("Not a valid integer\n");
      while (getchar() != '\n')
        ;
    }
  }
}
