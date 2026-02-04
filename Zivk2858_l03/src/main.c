/**
 * -------------------------------------
 * @file  main.c
 * -------------------------------------
 * @author Zivkovic Luka, 169102858, Zivk2858@mylaurier.ca
 *
 * @version 2026-01-26
 *
 * -------------------------------------
 */
#include "functions.h"

/**
 * Converts an array of int to a string.
 *
 * @param buffer - pointer to string
 * @param size - maximum size of buffer
 * @param source - pointer to an array of int
 * @param count - number of integers in source
 * @return - size of buffer
 */
static int int_array_string(char *buffer, size_t size, int *source, int count) {
    int len = snprintf(buffer, size, "{");

    if(count > 0) {
        int i = 0;

        for(; i < (count - 1); i++) {
            len += snprintf(buffer + len, size - len, "%d, ", source[i]);
        }
        len += snprintf(buffer + len, size - len, "%d", source[i]);
    }
    len += snprintf(buffer + len, size - len, "}");
    return len;
}

// Test functions.

static void test_sum_integers(void) {
    printf("Test: sum_integers\n\n");
    int sum = sum_integers();
    printf("Sum: %d\n\n", sum);
}

static void test_sum_three_integers(void) {
    printf("Test: sum_three_integers\n\n");
    int sum = sum_three_integers();
    printf("Sum: %d\n\n", sum);
}

static void test_int_array_read(void) {
    printf("Test: int_array_read\n\n");
    char buffer[STRING_BIG];
    int size = 4;
    int array[size];
    int_array_read(array, size);
    int_array_string(buffer, sizeof buffer, array, size);
    printf("%s\n", buffer);
}

/**
 * Test the Lab 3 input functions.
 *
 * @param argc - count of elements in args
 * @param args - array of strings passed on command line
 * @return EXIT_SUCCESS
 */
int main(int argc, char *args[]) {
    setbuf(stdout, NULL);

    test_sum_integers();
    test_sum_three_integers();
    test_int_array_read();
    return EXIT_SUCCESS;
}
