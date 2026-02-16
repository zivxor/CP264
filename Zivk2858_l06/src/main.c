/** @file  main.c
 * -------------------------------------
 * @author your name, your id, your email
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"
#include "stack_linked.h"
#include "queue_linked.h"

#define TST "===========================================\n"
#define SEP "-------------------------------------------\n"

#define FOODS_FILE  "foods.txt"

int test_stack_generic(const data_type *values, int count) {
    printf(TST);
    printf("Testing stack_linked\n");
    printf(SEP);

    data_type item;
    char string[200];
    stack_linked *source = stack_initialize();
    stack_linked *target1 = stack_initialize();
    stack_linked *target2 = stack_initialize();

    printf("source = stack_initialize():\n");

    if(!source) {
        perror("stack could not be initialized");
        return 1;
    }
    printf("stack_print(source)\n");
    stack_print(source);
    printf(SEP);
    printf("stack_empty(source): %s\n", BOOL_STR(stack_empty(source)));
    printf(SEP);

    for(int i = 0; i < count; i++) {
        data_string(string, sizeof string, &values[i]);
        printf("stack_push(source, %s)\n", string);

        if(!stack_push(source, &values[i])) {
            perror("push failed");
            return 1;
        }
    }
    printf("stack_print(source)\n");
    stack_print(source);
    printf(SEP);
    printf("stack_empty(source): %s\n", BOOL_STR(stack_empty(source)));
    printf(SEP);
    printf("stack_peek(source, &item)\n");
    stack_peek(source, &item);
    data_string(string, sizeof string, &item);
    printf("item: %s\n", string);
    printf(SEP);
    printf("stack_split_alt(target1, target2, source);\n");
    stack_split_alt(target1, target2, source);
    printf("stack_print(source)\n");
    stack_print(source);
    printf("stack_print(target1)\n");
    stack_print(target1);
    printf("stack_print(target2)\n");
    stack_print(target2);
    printf("stack_combine(source, target1, target2)\n");
    stack_combine(source, target1, target2);
    printf("stack_print(target1)\n");
    stack_print(target1);
    printf("stack_print(target2)\n");
    stack_print(target2);
    printf("stack_print(source)\n");
    stack_print(source);
    printf(SEP);
    printf("stack_copy(&target1, source)\n");
    stack_copy(&target1, source);
    printf("stack_print(target1)\n");
    stack_print(target1);
    printf(SEP);
    printf("stack_equal(source, target1): %s\n", BOOL_STR(stack_equal(source, target1)));
    printf("stack_pop(target1, &item)\n");
    stack_pop(target1, &item);
    printf("stack_equal(source, target1): %s\n", BOOL_STR(stack_equal(source, target1)));
    printf(SEP);
    printf("stack_destroy(&target1)\n");
    stack_destroy(&target1);
    printf("target1 == NULL: %s\n", BOOL_STR(target1 == NULL));
    printf(SEP);

    while(!stack_empty(source)) {
        printf("stack_pop(source, &item)\n");
        stack_pop(source, &item);
        data_string(string, sizeof string, &item);
        printf("  item: %s\n", string);
    }
    printf("\n");
    printf("stack_print(source)\n");
    stack_print(source);
    return 0;
}

int test_queue_generic(const data_type *values, int count) {
    printf(TST);
    printf("Testing queue_linked\n");
    printf(SEP);

    data_type item;
    char string[200];
    queue_linked *source = queue_initialize();
    queue_linked *target1 = queue_initialize();
    queue_linked *target2 = queue_initialize();

    printf("source = queue_initialize():\n");
    printf("queue_print(&source)\n");
    queue_print(source);
    printf(SEP);
    printf("queue_empty(&source): %s\n", BOOL_STR(queue_empty(source)));
    printf(SEP);

    for(int i = 0; i < count; i++) {
        data_string(string, sizeof string, &values[i]);
        printf("queue_insert(&source, %s)\n", string);

        if(!queue_insert(source, &values[i])) {
            perror("insert failed");
            return 1;
        }
    }
    printf("queue_print(&source)\n");
    queue_print(source);
    printf(SEP);
    printf("queue_empty(&source): %s\n", BOOL_STR(queue_empty(source)));
    printf(SEP);
    printf("queue_peek(&source, &item)\n");
    queue_peek(source, &item);
    data_string(string, sizeof string, &item);
    printf("item: %s\n", string);
    printf(SEP);
    printf("queue_split_alt(target1, target2, source);\n");
    queue_split_alt(target1, target2, source);
    printf("queue_print(source)\n");
    queue_print(source);
    printf("queue_print(target1)\n");
    queue_print(target1);
    printf("queue_print(target2)\n");
    queue_print(target2);
    printf("queue_combine(source, target1, target2)\n");
    queue_combine(source, target1, target2);
    printf("queue_print(target1)\n");
    queue_print(target1);
    printf("queue_print(target2)\n");
    queue_print(target2);
    printf("queue_print(source)\n");
    queue_print(source);
    printf(SEP);
    printf("queue_copy(&target1, source)\n");
    queue_copy(&target1, source);
    printf("queue_print(target1)\n");
    queue_print(target1);
    printf(SEP);
    printf("queue_equal(source, target1): %s\n", BOOL_STR(queue_equal(source, target1)));
    printf("queue_remove(target1, &item)\n");
    queue_remove(target1, &item);
    printf("queue_equal(source, target1): %s\n", BOOL_STR(queue_equal(source, target1)));
    printf(SEP);
    printf("queue_destroy(&target1)\n");
    queue_destroy(&target1);
    printf("target1 == NULL: %s\n", BOOL_STR(target1 == NULL));
    printf(SEP);

    while(!queue_empty(source)) {
        printf("queue_remove(source, &item)\n");
        queue_remove(source, &item);
        data_string(string, sizeof string, &item);
        printf("  item: %s\n", string);
    }
    printf("\n");
    printf("queue_print(source)\n");
    queue_print(source);
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
    const data_type values[] = {{2}, {4}, {1}, {7}, {4}, {2}, {9}, {3}, {6}, {6}, {8}};
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

    test_stack_generic(values, values_count);
    test_queue_generic(values, values_count);
    return 0;
}
