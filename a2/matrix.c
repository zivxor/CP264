#include <math.h>
#include "matrix.h"
#include <stdio.h>

/**
 * Calculates the Euclidean norm (length) of a vector.
 * Use sqrt function from math.h to calculate the square root.
 * 
 * @param v Pointer to the vector.
 * @param n Number of elements in the vector.
 * @return The Euclidean norm of the vector.
 */
float norm(float *v, int n){
    float sum = 0.0f;
    for (int i = 0; i < n; ++i) {
        sum += (*(v + i)) * (*(v + i)); // v[i] * v[i]
    }
    return sqrtf(sum);
}

/**
 * Normalizes a vector (scales it to unit length).
 * @param vin Pointer to the input vector.
 * @param vout Pointer to the output vector (normalized).
 * @param n Number of elements in the vector.
 */
void normalize(const float *vin, float *vout, int n){
    float length = norm((float *)vin, n);
    if (length == 0.0f) {
        // Handle zero-length vector case (could set vout to zero vector)
        for (int i = 0; i < n; ++i) {
            *(vout + i) = 0.0f;
        }
        return;
    }
    for (int i = 0; i < n; ++i) {
        *(vout + i) = (*(vin + i)) / length; // vout[i] = vin[i] / length
    }
}

/**
 * Multiplies a matrix by a scalar value.
 * @param A Pointer to the input matrix.
 * @param scalar Scalar value to multiply.
 * @param B Pointer to the output matrix (result).
 * @param rows Number of rows in the matrix.
 * @param cols Number of columns in the matrix.
 */
void matrix_scalar_multiply(const float *A, float scalar, float *B, int rows, int cols){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            *(B + i * cols + j) = (*(A + i * cols + j)) * scalar; // B[i][j] = A[i][j] * scalar
        }
    }
}

/**
 * Computes the transpose of a matrix.
 * @param A Pointer to the input matrix (rows x cols).
 * @param B Pointer to the output matrix (cols x rows).
 * @param rows Number of rows in the input matrix.
 * @param cols Number of columns in the input matrix.
 */
void matrix_transpose(const float *A, float *B, int rows, int cols){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            *(B + j * rows + i) = *(A + i * cols + j); // B[j][i] = A[i][j]
        }
    }
}

/**
 * Adds two matrices element-wise.
 * @param A Pointer to the first input matrix.
 * @param B Pointer to the second input matrix.
 * @param C Pointer to the output matrix (sum).
 * @param rows Number of rows in the matrices.
 * @param cols Number of columns in the matrices.
 */
void matrix_add(const float *A, const float *B, float *C, int rows, int cols){
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            *(C + i * cols + j) = (*(A + i * cols + j)) + (*(B + i * cols + j)); // C[i][j] = A[i][j] + B[i][j]
        }
    }
}


/* Multiplies two matrices.
 * @param A Pointer to the first input matrix (rowsA x colsA).
 * @param B Pointer to the second input matrix (colsA x colsB).
 * @param C Pointer to the output matrix (rowsA x colsB).
 * @param rowsA Number of rows in matrix A.
 * @param colsA Number of columns in matrix A and rows in matrix B.
 * @param colsB Number of columns in matrix B.
 */
void matrix_multiply(const float *A, const float *B, float *C, int rowsA, int colsA, int colsB){
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            *(C + i * colsB + j) = 0.0f; // Initialize C[i][j] to 0
            for (int k = 0; k < colsA; ++k) {
                *(C + i * colsB + j) += (*(A + i * colsA + k)) * (*(B + k * colsB + j)); // C[i][j] += A[i][k] * B[k][j]
            }
        }
    }
}