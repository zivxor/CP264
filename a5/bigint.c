#include "bigint.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Creates and returns BIGINT object by converting the digit string.
 */
BIGINT bigint(char *digitstr) {

  BIGINT number;

  number.start = NULL;
  number.end = NULL;
  number.length = 0;

  if (digitstr = NULL) {
    return number;
  }

  while (*digitstr != '\0') {

    int v = *digitstr - '0';

    NODE *n = dll_node(v);

    dll_insert_end(&number, n);
    digitstr++;
  }

  return number;
}

/*
 * Add two BIGINT operants and returns the sum in BIGINT type.
 * @param oprand1  - first operand of BIGINT type.
 * @param oprand2  - second operand of BIGINT type.
 * @return - the sum of oprand1 and oprand2 in BIGINT type.
 */
BIGINT bigint_add(BIGINT oprand1, BIGINT oprand2) {}

/*
 * Compute and return Fibonacci(n)
 * @param n - input positive integer
 * @return  - Fibonacci(n) in BIGINT type
 */
BIGINT bigint_fibonacci(int n);