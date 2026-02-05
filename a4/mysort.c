#include "mysort.h"
#include <stdio.h>

void swap(void **x, void **y) {
  void *temp = *x;
  *x = *y;
  *y = temp;
}
int cmp(void *x, void *y) {
  float a = *(float *)x;
  float b = *(float *)y;
  if (a > b)
    return 1;
  else if (a < b)
    return -1;
  else
    return 0;
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
    void *pivot = a[right]; // Choose the last element as the pivot
    int i = left - 1; // i will track the end of the "less than pivot" section
    for (int j = left; j < right; j++) { // j scans from left to right-1
      if (cmp(a[j], pivot) < 0) { // If current element is less than pivot
        i++; // Move the boundary of "less than pivot" section
        swap(&a[i],
             &a[j]); // Swap current element into the "less than pivot" section
      }
    }
    swap(&a[i + 1],
         &a[right]); // Place the pivot after the last "less than" element
    int pivotIndex = i + 1; // The pivot is now at its correct sorted position

    quick_sort(a, left, pivotIndex - 1); // Recursively sort the left partition
    quick_sort(a, pivotIndex + 1,
               right); // Recursively sort the right partition
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
  if (left < right) {
    void *pivot = a[right];
    int i = left - 1;
    for (int j = left; j < right; j++) {
      if ((*cmp)(a[j], pivot) < 0) {
        i++;
        swap(&a[i], &a[j]);
      }
    }
    swap(&a[i + 1], &a[right]);
    cmp_sort(a, left, i, cmp);
    cmp_sort(a, i + 2, right, cmp);
  }
}