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

  if (digitstr == NULL) {
    return number;
  }

  while (*digitstr != '\0') {

    char v = *digitstr - '0';

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
BIGINT bigint_add(BIGINT oprand1, BIGINT oprand2) {
  BIGINT result = {0, NULL, NULL};
  NODE *p1 = oprand1.end;
  NODE *p2 = oprand2.end;
  int carry = 0;

  while (p1 != NULL || p2 != NULL || carry) {
    int v1 = (p1 != NULL) ? p1->data : 0;
    int v2 = (p2 != NULL) ? p2->data : 0;
    int sum = v1 + v2 + carry;
    carry = sum / 10;
    NODE *n = dll_node(sum % 10);
    dll_insert_start(&result, n);
    if (p1)
      p1 = p1->prev;
    if (p2)
      p2 = p2->prev;
  }
  return result;
}

/*
 * Compute and return Fibonacci(n)
 * @param n - input positive integer
 * @return  - Fibonacci(n) in BIGINT type
 */
BIGINT bigint_fibonacci(int n) {

  if (n == 0) {
    return bigint("0");
  } else if (n == 1) {
    return bigint("1");
  }

  BIGINT prev = bigint("0");
  BIGINT curr = bigint("1");

  for (int i = 1; i < n; i++) {
    BIGINT temp = bigint_add(prev, curr);
    dll_clean(&prev);
    prev = curr;
    curr = temp;
  }
  dll_clean(&prev);
  return curr;
}