/** @file  main.c
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "data.h"
#include "bst_linked.h"

#define TST "===========================================\n"
#define SEP "-------------------------------------------\n"

int test_bst_generic(const data_type *values, int count) {
    printf(TST);
    printf("Testing bst_linked\n");
    printf(SEP);

    data_type item;
    char string[200];
    bst_linked *source = bst_initialize();

    printf("source = bst_initialize():\n");

    if(!source) {
        perror("bst could not be initialized");
        return 1;
    }
    printf("bst_print(source)\n");
    bst_print(source);
    printf(SEP);
    printf("bst_empty(source): %s\n", BOOL_STR(bst_empty(source)));
    printf(SEP);

    for(int i = 0; i < count; i++) {
        data_string(string, sizeof string, &values[i]);
        printf("bst_insert(source, %s)\n", string);
        bst_insert(source, &values[i]);
    }
    printf("bst_print(source)\n");
    bst_print(source);
    printf(SEP);
    printf("bst_empty(source): %s\n", BOOL_STR(bst_empty(source)));
    printf(SEP);
    printf("bst_count(source): %d\n", bst_count(source));
    printf(SEP);

    // other tests here
    printf("\nother tests here\n\n");

    printf(SEP);
    printf("bst_destroy(&source)\n");
    bst_destroy(&source);
    return 0;
}

/**
 * Change commenting in data.h in order to use a given data type.
 *
 * @param argc - unused
 * @param argv - unused
 * @return
 */
int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

#ifdef USE_INT
    // integer test values
    const data_type values[] = {{11}, {7}, {6}, {9}, {8}, {15}, {12}, {18}};
    int values_count = sizeof values / sizeof *values;
#endif

#ifdef USE_FOOD
    // food test values
    food_array foods;
    food_array_init(&foods);
    FILE *fp = fopen(FOODS_FILE, "r");
    foods_read(fp, &foods);
    fclose(fp);
    const data_type *values = foods.items;
    int values_count = foods.count;
#endif

    test_bst_generic(values, values_count);
    return 0;
}
