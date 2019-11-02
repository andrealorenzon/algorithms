#include <stdlib.h>

#include "../utility.h"
#include "hw.h"

// functions, to do:

/*
opt_sumBlocks
opt_subtractBlocks
naiveMultiplication
strassenAuxiliaryOptimized
strassenOptimized


*/

void opt_sumBlocks(Matrix A, Matrix B, Matrix C, const size_t size)
{
    for (size_t i = 0; i < size; i++) 
    {
        for (size_t j = 0; j < size; j++) 
        {
            C.matr[C.rows + i][C.cols + j] = 
            A.matr[A.rows + i][A.cols + j] +
            B.matr[B.rows + i][B.cols + j];
        }
    }
}

void opt_subtractBlocks(Matrix A, Matrix B, Matrix C, const size_t size)
{
    for (size_t i = 0; i < size; i++) 
    {
        for (size_t j = 0; j < size; j++) 
        {
            C.matr[C.rows + i][C.cols + j] = 
            A.matr[A.rows + i][A.cols + j] -
            B.matr[B.rows + i][B.cols + j];
        }
    }
}

void naiveMultiplication(Matrix A, Matrix B, Matrix C, const size_t size)
{
    for (size_t i = 0; i < size; i++) 
    {
        for (size_t j = 0; j < size; j++) 
        {
            C.matr[C.rows + i][C.cols + j] = 0.0;
            for (size_t k = 0; k < size; k++) 
            {
                C.matr[C.rows + i][C.cols + j] += (A.matr[A.rows + i][A.cols + k] *
                                                B.matr[B.rows + k][B.cols + j]);
            }
        }
    }
}

void strassenAuxiliaryOptimized(Matrix A, Matrix B, Matrix C, Matrix M, const size_t size)
{
    if (size < (64)) {
        naiveMultiplication(A, B, C, size);
        return;
    }

    const size_t half_size = size / 2;

    Matrix A11 = {A.matr, A.rows,             A.cols};
    Matrix A12 = {A.matr, A.rows,             A.cols + half_size};
    Matrix A21 = {A.matr, A.rows + half_size, A.cols};
    Matrix A22 = {A.matr, A.rows + half_size, A.cols + half_size};
    Matrix B11 = {B.matr, B.rows,             B.cols};
    Matrix B12 = {B.matr, B.rows,             B.cols + half_size};
    Matrix B21 = {B.matr, B.rows + half_size, B.cols};
    Matrix B22 = {B.matr, B.rows + half_size, B.cols + half_size};
    Matrix C11 = {C.matr, C.rows,             C.cols};
    Matrix C12 = {C.matr, C.rows,             C.cols + half_size};
    Matrix C21 = {C.matr, C.rows + half_size, C.cols};
    Matrix C22 = {C.matr, C.rows + half_size, C.cols + half_size};
    Matrix M11 = {M.matr, M.rows,             M.cols};
    Matrix M12 = {M.matr, M.rows,             M.cols + half_size};
    Matrix M21 = {M.matr, M.rows + half_size, M.cols};
    Matrix M22 = {M.matr, M.rows + half_size, M.cols + half_size};

    // S2 = A11 + A12
    opt_sumBlocks(A11, A12, C22, half_size);
    // P2 = S2 x B22
    strassenAuxiliaryOptimized(C22, B22, C12, M22, half_size);

    // S4 = B21 - B11
    opt_subtractBlocks(B21, B11, C22, half_size);
    // P4 = A22 x S4
    strassenAuxiliaryOptimized(A22, C22, M21, M22, half_size);

    // S5 = A11 + A22
    opt_sumBlocks(A11, A22, C22, half_size);
    // S6 = B11 + B22
    opt_sumBlocks(B11, B22, C21, half_size);
    // P5 = S5 x S6
    strassenAuxiliaryOptimized(C22, C21, M12, M22, half_size);

    // S7 = A12 - A22
    opt_subtractBlocks(A12, A22, C22, half_size);
    // S8 = B21 + B22
    opt_sumBlocks(B21, B22, C21, half_size);
    // P6 = S7 x S8
    strassenAuxiliaryOptimized(C22, C21, M11, M22, half_size);

    // C11 = (P5 + P4) - P2 + P6
    opt_sumBlocks(M12, M21, C11, half_size);
    opt_subtractBlocks(C11, C12, C11, half_size);
    opt_subtractBlocks(C11, M11, C11, half_size);

    // S1 = B12 - B22
    opt_subtractBlocks(B12, B22, C21, half_size);
    // P1 = A11 x S1
    strassenAuxiliaryOptimized(A11, C21, C22, M22, half_size);

    // C12 = P1 + P2
    opt_sumBlocks(C22, C12, C12, half_size);

    // S3 = A21 + A22
    opt_sumBlocks(A21, A22, C21, half_size);
    // P3 = S3 x B11
    strassenAuxiliaryOptimized(C21, B11, M11, M22, half_size);

    // C21 = P3 + P4
    opt_sumBlocks(M11, M21, C21, half_size);

    // Partial = P5 + P1 - P3
    opt_sumBlocks(M12, C22, C22, half_size);
    opt_subtractBlocks(C22, M11, C22, half_size);

    // S9 = A11 - A21
    opt_subtractBlocks(A11, A21, M11, half_size);
    // S10 = B11 + B12
    opt_sumBlocks(B11, B12, M12, half_size);
    // P7 = S9 x S10 
    strassenAuxiliaryOptimized(M11, M12, M21, M22, half_size);

    // C22 = Partial - P7
    opt_subtractBlocks(C22, M21, C22, half_size);
}

void strassenOptimized(float **C, float **A, float **B, const size_t size)
{
    Matrix M_A = {A, 0, 0};
    Matrix M_B = {B, 0, 0};
    Matrix M_C = {C, 0, 0};
    Matrix aux = {allocateMatrix(size, size), 0, 0};
    strassenAuxiliaryOptimized(M_A, M_B, M_C, aux, size);
    deallocateMatrix((void **)aux.matr, size);
}
