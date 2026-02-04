#include "fibonacci.h"

#include <limits.h>
#include <stdio.h>

int iterative_fibonacci(int n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  int prev = 0, curr = 1;
  for (int i = 2; i <= n; ++i) {
    long sum = (long)prev + curr;
    if (sum > INT_MAX)
      return -1;
    prev = curr;
    curr = sum;
  }
  return curr;
}

int recursive_fibonacci(int n) {
  if (n == 0)
    return 0;
  if (n == 1)
    return 1;
  long prev = recursive_fibonacci(n - 2);
  if (prev == -1)
    return -1;
  long curr = recursive_fibonacci(n - 1);
  if (curr == -1)
    return -1;
  long sum = prev + curr;
  if (sum > INT_MAX)
    return -1;
  return sum;
}

int dpbu_fibonacci(int *a, int n) {
  a[0] = 0;
  if (n == 0) {
    return 0;
  }
  if (n == 1) {
    return 1;
  }
  a[1] = 1;
  for (int i = 2; i <= n; ++i) {
    long sum = (long)a[i - 2] + a[i - 1];
    if (sum > INT_MAX)
      return -1;
    a[i] = sum;
  }
  return a[n];
}

int dptd_fibonacci(int *a, int n) {
  if (n == 0) {
    a[0] = 0;
    return 0;
  }
  if (n == 1) {
    a[0] = 0;
    a[1] = 1;
    return 1;
  }
  if (a[n] != 0)
    return a[n]; // Assume initialized to 0
  int f_nm2 = dptd_fibonacci(a, n - 2);
  if (f_nm2 == -1)
    return -1;
  int f_nm1 = dptd_fibonacci(a, n - 1);
  if (f_nm1 == -1)
    return -1;
  long sum = (long)f_nm2 + f_nm1;
  if (sum > INT_MAX)
    return -1;
  a[n] = sum;
  return a[n];
}
