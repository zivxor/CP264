#include "mysort.h"
#include <stdio.h>

void swap(void **x, void **y) {
  void *temp = *x;
  *x = *y;
  *y = temp;
}
/**
 * Use selection sort algorithm to sort array of pointers such that their
 * pointed values are in increasing order.
 *
 * @param *a[] - array of void pointers.
 * @param left - the start index of pointer in array.
 * @param right - the end index of pointer in array
 */
void selection_sort(void *a[], int left, int right) {
  for (int i = left; i <= right; i++) { // loop from left until right index
    int min_idx = i;
    for (int j = i + 1; j <= right; j++) {
      if (*(float *)a[j] < *(float *)a[min_idx]) {
        min_idx = j;
      }
    }
    // Swap a[i] and a[min_idx]
    void *temp = a[i];
    a[i] = a[min_idx];
    a[min_idx] = temp;
  }
}

/**
 * Use quick sort algorithm to sort array of pointers such that their pointed
 * values are in increasing order.
 *
 * @param *a[] - array of void pointers.
 * @param left - the start index of pointer in array.
 * @param right - the end index of pointer in array
 */
void quick_sort(void *a[], int left, int right) {
  if (left < right) {
    void *pivot = a[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
      if (*(float *)a[j] < *(float *)pivot) {
        i++;
        swap(&a[i], &a[j]);
      }
    }
    swap(&a[i + 1], &a[right]);
    int pivotIndex = i + 1;

    quick_sort(a, left, pivotIndex - 1);
    quick_sort(a, pivotIndex + 1, right);
  }
}

/**
 * Use either selection or quick sort algorithm to sort array of pointers
 * such that their pointed values are in order defined by the comparison
 * function
 *
 * @param *a[] - array of void pointers.
 * @param left - the start index of pointer in array.
 * @param right - the end index of pointer in array
 * @param (*cmp) - pointer to a comparison function for comparing pointers
 *                by their pointed values.
 */
void cmp_sort(void *a[], int left, int right, int (*cmp)(void *, void *)) {
  for (int i = left; i < right; i++) {
    int min = i;
    for (int j = i + 1; j <= right; j++) {
      if (cmp(a[j], a[min]) < 0) {
        min = j;
      }
    }
    if (min != i) {
      swap(&a[i], &a[min]);
    }
  }
}