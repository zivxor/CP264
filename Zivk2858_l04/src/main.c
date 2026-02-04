/** @file  main.c
 * -------------------------------------
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 * DO NOT CHANGE
 */
#include <stdio.h>
#include <stdlib.h>

#include "functions.h"

#define CAPACITY 20
#define MAX_LINE 128
#define IN_FILE "data.txt"
#define SHORT_FILE "short.txt"
#define LONG_FILE "long.txt"

/**
 *
 * @param source
 */
void test_strings_with_substring(strings_array *source) {
    printf("------------------------\n");
    printf("Test strings_with_substring\n\n");
    char substring[MAX_LINE] = "";
    printf("Enter substring: ");
    scanf("%128s", substring);
    strings_with_substring(source, substring);
}

void test_strings_length(strings_array *source) {
    printf("------------------------\n");
    printf("Test strings_length\n\n");

    FILE *fp_short = fopen(SHORT_FILE, "w");
    FILE *fp_long = fopen(LONG_FILE, "w");
    int length = 0;
    printf("Enter the length comparison value: ");
    scanf("%d", &length);
    strings_length(source, fp_short, fp_long, length);
    fclose(fp_short);
    fclose(fp_long);
}

/**
 * Test the file and string functions.
 *
 * @param argc - unused
 * @param args - unused
 * @return EXIT_SUCCESS
 */
int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    // define and initialize the strings array structure
    strings_array source;
    initialize_strings_array(&source, CAPACITY);

    printf("------------------------\n");
    printf("read_strings\n\n");
    FILE *fp = fopen(IN_FILE, "r");
    read_strings(&source, fp);
    fclose(fp);
    printf("count: %d\n", source.count);

    printf("------------------------\n");
    printf("Contents of source:\n\n");

    for(int i = 0; i < source.count; i++) {
        printf("%s\n", source.strings[i]);
    }
    printf("\n");

    test_strings_with_substring(&source);
    test_strings_length(&source);
    // free the strings_array memory
    free_strings_array(&source);

    return EXIT_SUCCESS;
}
