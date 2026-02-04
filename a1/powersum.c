#include <stdio.h>
#include "powersum.h"
/**
 * Check whether computing b raised to the power n would overflow an `int`.
 *
 * @param b the base (non-negative integer)
 * @param n the exponent (non-negative integer)
 * @return 1 if an overflow would occur, otherwise 0
 */
int power_overflow(int b, int n){
    if (n == 0) {
        return 0; // b^0 = 1, no overflow
    }
    int result = 1;
    for (int i = 0; i < n; i++) {
        if (b != 0 && result > (2147483647 / b)) {
            return 1; // overflow would occur
        }
        result *= b;
    }
    return 0; // no overflow
}

/**
 * Compute b to the power n (b^n).
 *
 * @param b the base (non-negative integer)
 * @param n the exponent (non-negative integer)
 * @return b^n if the result fits in an `int`; returns 0 if overflow occurs.
 */
int mypow(int b, int n){
    if (power_overflow(b, n)) {
        return 0; // indicate overflow
    }
    int result = 1;
    for (int i = 0; i < n; i++) {
        result *= b;
    }
    return result;
}

/**
 * Compute and return the sum of powers: 1 + b + b^2 + ... + b^n.
 *
 * @param b the base (non-negative integer)
 * @param n the exponent (non-negative integer)
 * @return the computed sum if it fits in an `int`; returns 0 if overflow occurs.
 */
int powersum(int b, int n){
    int sum = 0;
    for (int i = 0; i <= n; i++) {
        int term = mypow(b, i);
        if (term == 0) {
            return 0; // overflow occurred in power calculation
        }
        if (sum > (2147483647 - term)) {
            return 0; // overflow would occur in sum
        }
        sum += term;
    }
    return sum;
}