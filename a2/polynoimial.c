#include "polynomial.h"
#include <stdio.h>
#include <math.h>
/**
 * Compute and return the value of a polynomial of degree (n-1):
 *   p(x) = p[0]*x^{n-1} + p[1]*x^{n-2} + ... + p[n-2]*x^1 + p[n-1]*x^0
 * using Horner's algorithm (see: https://en.wikipedia.org/wiki/Horner%27s_method).
 *
 * @param p Pointer to the array of coefficients (length n).
 * @param n Number of coefficients (degree + 1).
 * @param x Value at which to evaluate the polynomial.
 * @return The computed value p(x).
 */
float horner(float *p, int n, float x){
    float result = *p; // p[0]
    for (int i = 1; i < n; ++i) {
        result = result * x + *(p + i); // p[i]
    }
    return result;
}

/**
 * Compute the derivative of a polynomial of degree (n-1):
 *   p(x) = p[0]*x^{n-1} + p[1]*x^{n-2} + ... + p[n-2]*x^1 + p[n-1]*x^0
 * and store the coefficients of the derivative polynomial in array d.
 * The derivative is:
 *   p'(x) = (n-1)*p[0]*x^{n-2} + (n-2)*p[1]*x^{n-3} + ... + p[n-2]*x^0
 *
 * @param p Pointer to the array of input polynomial coefficients (length n).
 * @param d Pointer to the array for output derivative coefficients (length n-1).
 * @param n Number of coefficients in the input polynomial.
 */
void derivative(float *p, float *d, int n){
    for (int i = 0; i < n - 1; ++i) {
        *(d + i) = (*(p + i)) * (n - 1 - i); // d[i] = p[i] * (n-1-i)
    }
}

/**
 * Compute an approximate real root x of polynomial p(x) using Newton's method
 * (see: https://en.wikipedia.org/wiki/Newton%27s_method).
 * Uses a tolerance of 1e-6 and a maximum of 100 iterations.
 *
 * @param p Pointer to the array of input polynomial coefficients (length n).
 * @param n Number of coefficients in the input polynomial.
 * @param x0 Initial guess for the root.
 * @return The computed root if found; otherwise, returns x0.
 */
float newton(float *p, int n, float x0){
    const float tolerance = 1e-6;
    const int max_iterations = 100;
    float x = x0;

    float derivative_coeffs[n - 1];
    derivative(p, derivative_coeffs, n);

    for (int i = 0; i < max_iterations; ++i) {
        float fx = horner(p, n, x);
        float fpx = horner(derivative_coeffs, n - 1, x);

        if (fpx == 0.0f) {
            // Derivative is zero, cannot proceed
            return x0;
        }

        float x_new = x - fx / fpx;

        if (fabs(x_new - x) < tolerance) {
            return x_new;
        }

        x = x_new;
    }

    return x0; // Return initial guess if no root found within max iterations
}