#ifndef __HW__

#include <stdlib.h>

/**
 * @brief Float matrix
 * @var mat  float ** for values.
 * @var row  Rows count.
 * @var col  Cols count.
 */

typedef struct Matrix
{
    float ** matr;
    const size_t rows;
    const size_t cols;
} Matrix;


// Sums two matrix blocks A, B of size "size" creating block C.
void sumBlocks(Matrix A, Matrix B, Matrix C, const size_t size);

// Subtracts two matrix blocks A, B of size "size" creating block C.
void subtractBlocks(Matrix A, Matrix B, Matrix C, const size_t size);

// Naive matrix multiplication of A, B of size "size" creating C.
void naiveMultiplication(Matrix A, Matrix B, Matrix C, const size_t size);

// Auxiliary method for the optimized implementation of Strassen's algorithm.
void strassenAuxiliaryOptimized(Matrix A, Matrix B, Matrix C, Matrix M, const size_t size);

/**
 * @brief Performs the matrix multiplication of squared matrices A, B
 *        of size n x n using the optimized Strassen algorithm.
 * @param  C     The resulting matrix.
 * @param  A, B  The squared matrices that should be multiplied.
 * @param  n     The size of a side of matrices A, B
 * 
 * The number of allocations is minimized by reusing temporarily blocks
 * of the resulting matrix C and performing allocation outside of the 
 * auxiliary function call.
 */
void strassenOptimized(float **C, float **A, float **B, const size_t n);



#endif // __HW__ 