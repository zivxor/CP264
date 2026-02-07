/** @file  main.c
 * -------------------------------------
 * @author Heider Ali, 999999999, heali@wlu.ca
 * @author David Brown, 123456789, dbrown@wlu.ca
 *
 * @version 2025-09-01
 *
 * -------------------------------------
 */
#include "name_set.h"

// ==============================================================================================
// Definitions

#define NAME_LEN  41
#define MAX_LINE (NAME_LEN * 2 + 2)
#define FILENAME "names.txt"

/**
 * Testing for name_set structure.
 *
 * @param argc - unused
 * @param argv - unused
 * @return
 */
int main(int argc, char *argv[]) {
    setbuf(stdout, NULL);

    FILE *fp = NULL; // Input file pointer.
    int return_val = EXIT_SUCCESS;

    if((fp = fopen(FILENAME, "r")) != NULL) {
        // File open was successful!

        // define format string to avoid "Format string vulnerability in sscanf" warning
        // ex: "%40s %40s[^\n]"
        // [^\n] - removes EOL from buffer
        char read_format[18] = "";
        sprintf(read_format, "%%%ds %%%ds[^\n]", NAME_LEN - 1, NAME_LEN - 1);

        // Local storage for names
        char first_name[NAME_LEN] = "";
        char last_name[NAME_LEN] = "";
        // Initialize the name_set object
        name_set *source = name_set_initialize();
        bool appended = false;
        printf("Reading names from file:\n");
        char *buffer = NULL;
        size_t size = 0;

        // Keep reading and appending until reach EOF (End-Of-File).
        while(getline(&buffer, &size, fp) != -1) {
            // break buffer down into names using 'read_format'
            sscanf(buffer, read_format, first_name, last_name);
            appended = name_set_append(source, first_name, last_name);

            if(appended) {
                printf("%s, %s: appended to set\n", last_name, first_name);
            } else {
                printf("%s, %s: already in set\n", last_name, first_name);
            }
        }
        free(buffer);
        fclose(fp);
        printf("\nNames count: %d\n", name_set_count(source));
        printf("\nNames in set:\n");
        name_set_print(source);

        printf("\nIs most recent name in source?\n");
        bool contains = name_set_contains(source, first_name, last_name);

        if(contains) {
            printf("%s, %s: is in source\n", last_name, first_name);
        } else {
            printf("%s, %s: not in set\n", last_name, first_name);
        }

        printf("\nAttempt to re-append most recent name:\n");
        appended = name_set_append(source, first_name, last_name);

        if(appended) {
            printf("%s, %s: appended to source\n", last_name, first_name);
        } else {
            printf("%s, %s: already in set\n", last_name, first_name);
        }

        // Free the set.
        int freed = name_set_free(&source);
        printf("\nFreed %d nodes\n", freed);
        printf("set header: %p\n", source);
    } else {
        // Open input file and check if open is successful.
        printf("Cannot open file: %s\n", FILENAME);
        // Get set to have Main return an ERROR condition to OS.
        return_val = -1;
    }
    return return_val;
}
