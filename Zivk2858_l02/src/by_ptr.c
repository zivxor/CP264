/**
 * -------------------------------------
 * @file  by_ptr.c
 * -------------------------------------
 * @author Zivkovic Luka , 169102858, zivk2858@mylaurier.ca
 *
 * @version 2024-05-04
 *
 * -------------------------------------
 */
#include "by_ptr.h"

void fill_values_by_ptr(int *values, int size) {

    for(int i = 0; i < size; i++) {
        *(values + i) = i + 1;
    }
}

void fill_squares_by_ptr(int *values, long int *squares, int size) {

    for (int i = 0; i < size; i++){
        *(squares + i) = (*(values + i)) * (*(values + i));
    }
    

}

void print_by_ptr(int *values, long int *squares, int size) {

    printf("Value  Square\n");
    printf("-----  ----------\n");
    for (int i = 0; i < size; i++){
        printf("%5d  %10ld\n", *(values + i), *(squares + i));
    }

}
