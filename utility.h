/**
 * @author Andrea Lorenzon (andrelorenzon@gmail.com)
 * @brief Helper functions / general utilities
 * @date Nov 2nd, 2019
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include <stdlib.h>

/**
 * @brief  Naive matrix multiplication
 * @param  C               Result matrix.
 * @param  A, B            Matrices to be multiplied together.
 * @param  A_rows, A_cols  Dimensions of the A matrix.
 * @param  B_rows, B_cols  Dimensions of the B matrix. 
 */
void naive_matrix_mul(float **C, float **A, float **B,
                                const size_t A_rows, const size_t A_cols,
                                const size_t B_rows, const size_t B_cols);


/**
 * @brief Allocates a matrix of size rows, cols in memory
 * @param    rows, cols  The dimensions of the matrix.
 * @return   float       The allocated matrix.
 */
float **allocate_matrix(const size_t rows, const size_t cols);


/**
 * @brief Deallocates a matrix.
 * @param    rows  Matrix row count
 */
void deallocate_matrix(void **A, const size_t rows);

/**
 * @brief Copies a matrix.
 * @param    A           The matrix to be copied.
 * @param    rows, cols  The dimensions of the A matrix.
 * @return   float       The copied matrix.
 */
float **copy_matrix(float **A, const size_t rows, const size_t cols);

// Randomly fills matrix A with values between 0 and max.
void random_fill_matrix(float **A, const size_t A_rows, 
                          const size_t A_cols, int max);


/**
 * @brief Get the execution time in seconds.
 * @param    b_time  Beginning time object.
 * @param    e_time  End time object.
 * @return double Time in seconds.
 */
double get_execution_time(const struct timespec b_time, const struct timespec e_time);


// returns 1 if 2 matrices are equal, 0 if not.

int same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		        float **B, const size_t B_rows, const size_t B_cols);

int almost_same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		        float **B, const size_t B_rows, const size_t B_cols);                

#endif // fine header file