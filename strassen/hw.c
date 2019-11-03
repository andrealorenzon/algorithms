#include <stdlib.h>

#include "../utility.h"
#include "hw.h"

// functions, to do:

/*
sum_blocks
sub_blocks
naive_mult
strassen_aux_opt
strassen_opt


*/

// elementwise sum of two blocks

void sum_blocks(Matrix A, Matrix B, Matrix C, const size_t size)
{
    for (size_t i = 0; i < size; i++) 
    {
        for (size_t j = 0; j < size; j++) 
        {
            C.matr[C.rows + i][C.cols + j] = A.matr[A.rows + i][A.cols + j] + B.matr[B.rows + i][B.cols + j];
        }
    }
}


// elementwise difference of two blocks

void sub_blocks(Matrix A, Matrix B, Matrix C, const size_t size)
{
    for (size_t i = 0; i < size; i++) 
    {
        for (size_t j = 0; j < size; j++) 
        {
            C.matr[C.rows + i][C.cols + j] = A.matr[A.rows + i][A.cols + j] -
                                          B.matr[B.rows + i][B.cols + j];
        }
    }
}

// naive matrix multiplication for small matrices

void naive_mult(Matrix A, Matrix B, Matrix C, const size_t size)
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

// auxiliary strassen

void strassen_aux_opt(Matrix A, Matrix B, Matrix C, Matrix M, const size_t size)
{
    if (size < (1 << 5)) {    // < 64
        naive_mult(A, B, C, size);
        return;
    }

    const size_t half_size = size / 2;                              // works only for 2^n matrices?


// submatrices initialization

    Matrix A11 = {A.matr, A.rows,A.cols};                           //upper left quadrant
    Matrix A12 = {A.matr, A.rows,A.cols + half_size};               //upper right quadrant
    Matrix A21 = {A.matr, A.rows + half_size, A.cols};              //lower left quadrant
    Matrix A22 = {A.matr, A.rows + half_size, A.cols + half_size};  //lower right quadrant

    Matrix B11 = {B.matr, B.rows,B.cols};
    Matrix B12 = {B.matr, B.rows,B.cols + half_size};
    Matrix B21 = {B.matr, B.rows + half_size, B.cols};
    Matrix B22 = {B.matr, B.rows + half_size, B.cols + half_size};
    
    Matrix C11 = {C.matr, C.rows,C.cols};
    Matrix C12 = {C.matr, C.rows,C.cols + half_size};
    Matrix C21 = {C.matr, C.rows + half_size, C.cols};
    Matrix C22 = {C.matr, C.rows + half_size, C.cols + half_size};
    
    Matrix M11 = {M.matr, M.rows,M.cols};
    Matrix M12 = {M.matr, M.rows,M.cols + half_size};
    Matrix M21 = {M.matr, M.rows + half_size, M.cols};
    Matrix M22 = {M.matr, M.rows + half_size, M.cols + half_size};

    // S2 = A11 + A12
    sum_blocks(A11, A12, C22, half_size);
    // P2 = S2 x B22
    strassen_aux_opt(C22, B22, C12, M22, half_size);

    // S4 = B21 - B11
    sub_blocks(B21, B11, C22, half_size);
    // P4 = A22 x S4
    strassen_aux_opt(A22, C22, M21, M22, half_size);

    // S5 = A11 + A22
    sum_blocks(A11, A22, C22, half_size);
    // S6 = B11 + B22
    sum_blocks(B11, B22, C21, half_size);
    // P5 = S5 x S6
    strassen_aux_opt(C22, C21, M12, M22, half_size);

    // S7 = A12 - A22
    sub_blocks(A12, A22, C22, half_size);
    // S8 = B21 + B22
    sum_blocks(B21, B22, C21, half_size);
    // P6 = S7 x S8
    strassen_aux_opt(C22, C21, M11, M22, half_size);

    // C11 = (P5 + P4) - P2 + P6
    sum_blocks(M12, M21, C11, half_size);
    sub_blocks(C11, C12, C11, half_size);
    sum_blocks(C11, M11, C11, half_size);

    // S1 = B12 - B22
    sub_blocks(B12, B22, C21, half_size);
    // P1 = A11 x S1
    strassen_aux_opt(A11, C21, C22, M22, half_size);

    // C12 = P1 + P2
    sum_blocks(C22, C12, C12, half_size);

    // S3 = A21 + A22
    sum_blocks(A21, A22, C21, half_size);
    // P3 = S3 x B11
    strassen_aux_opt(C21, B11, M11, M22, half_size);

    // C21 = P3 + P4
    sum_blocks(M11, M21, C21, half_size);

    // Partial = P5 + P1 - P3
    sum_blocks(M12, C22, C22, half_size);
    sub_blocks(C22, M11, C22, half_size);

    // S9 = A11 - A21
    sub_blocks(A11, A21, M11, half_size);
    // S10 = B11 + B12
    sum_blocks(B11, B12, M12, half_size);
    // P7 = S9 x S10 
    strassen_aux_opt(M11, M12, M21, M22, half_size);

    // C22 = Partial - P7
    sub_blocks(C22, M21, C22, half_size);
}

void strassen_opt(float **C, float **A, float **B, const size_t size)
{
    Matrix M_A = {A, 0, 0};
    Matrix M_B = {B, 0, 0};
    Matrix M_C = {C, 0, 0};
    Matrix aux = {allocate_matrix(size, size), 0, 0};
    strassen_aux_opt(M_A, M_B, M_C, aux, size);
    deallocate_matrix((void **)aux.matr, size);
}

