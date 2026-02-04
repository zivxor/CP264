#include <stdio.h>
#include "mychar.h"
/**
 * Determine the type of a character.
 *
 * @param c - input character
 * @return 0 if `c` is a digit
 *        1 if `c` is an arithmetic operator
 *        2 if `c` is the left parenthesis `(`
 *        3 if `c` is the right parenthesis `)`
 *        4 if `c` is an English letter
 *       -1 otherwise
 */
int mytype(char c){
    if (c >= '0' && c <= '9') {
        return 0; // digit
    } else if (c == '+' || c == '-' || c == '*' || c == '/') {
        return 1; // arithmetic operator
    } else if (c == '(') {
        return 2; // left parenthesis
    } else if (c == ')') {
        return 3; // right parenthesis
    } else if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
        return 4; // English letter
    } else {
        return -1; // other
    }
}


/**
 * Flip the case of an English letter.
 *
 * @param c - input character
 * @return the uppercase/lowercase counterpart if `c` is an English letter;
 *         otherwise returns `c` unchanged.
 */
char case_flip(char c){
    if (c >= 'a' && c <= 'z') {
        return c - ('a' - 'A'); // convert to uppercase
    } else if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A'); // convert to lowercase
    } else {
        return c; // unchanged
    }
}

/**
 * Convert a digit character to its integer value.
 *
 * @param c - input character
 * @return the integer value if `c` is a digit character; otherwise -1.
 */
int digit_to_int(char c){
    if (c >= '0' && c <= '9') {
        return c - '0'; // convert character to integer
    } else {
        return -1; // not a digit
    }
}