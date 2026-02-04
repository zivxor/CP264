/**
 * -------------------------------------
 * @file  sum_integers.c
 * -------------------------------------
 * @author Zivkovic Luka, 169102858, Zivk2858@mylaurier.ca
 *
 * @version 2026-01-26
 *
 * -------------------------------------
 */
#include "functions.h"
#include <stdio.h>

int sum_integers(void) {
  int total = 0;
  int num;
  printf("Enter integers, one per line: \n");
  while (scanf("%d", &num) == 1) {
    total += num;
  }
  return total;
}
