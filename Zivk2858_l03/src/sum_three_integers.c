/**
 * -------------------------------------
 * @file  sum_three_integers.c
 * -------------------------------------
 * @author Zivkovic Luka, 169102858, Zivk2858@mylaurier.ca
 *
 * @version 2026-01-26
 *
 * -------------------------------------
 */
#include "functions.h"

int sum_three_integers(void) {
  int a, b, c;
  printf("Enter three comma-separated integers: ");
  while (scanf("%d,%d,%d", &a, &b, &c) != 3) {
    while (getchar() != '\n')
      ;
    printf("The integers were not properly entered.\n");
    printf("Enter three comma-separated integers: ");
  }
  return a + b + c;
}
