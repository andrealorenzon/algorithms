#include <stdlib.h>

#include "../utility.h"

/* functions, to do:  

sumBlocks
subtractBlocks
naiveMultiplicationAuxiliary
strassenAuxiliaryOptimized
strassen
*/


/*
 *  @Brief: pairwise sum 
 */
void sumBlocks(float **C,
                const size_t C_f_row,
                const size_t C_f_col,
                float ** A,
                const size_t A_f_row,
                const size_t A_f_col,
                float ** B,
                const size_t B_f_row,
                const size_t B_f_col,
                const size_t n
) {
    for (size_t i=0; i<n; i++) {
        for (size_t j=0; j<n; j++) {
            C[C_f_row+i][C_f_col+j] = 
                A[A_f_row+i][A_f_col+j] + 
                B[B_f_row+i][B_f_col+j];
        };
    };
};   

/*
 *  @Brief: pairwise subtraction 
 */
void subtractBlocks(float **C,
                const size_t C_f_row,
                const size_t C_f_col,
                float ** A,
                const size_t A_f_row,
                const size_t A_f_col,
                float ** B,
                const size_t B_f_row,
                const size_t B_f_col,
                const size_t n
) {
    for (size_t i=0; i<n; i++) {
        for (size_t j=0; j<n; j++) {
            C[C_f_row+i][C_f_col+j] = 
                A[A_f_row+i][A_f_col+j] + 
                B[B_f_row+i][B_f_col+j];
        }
    }
}   


/*
 *  @Brief: Auxiliary function for naive matrix multiplication
 */
void naiveMultiplicationAuxiliary(
                float **C, const size_t C_f_row, const size_t C_f_col,
                float **A, const size_t A_f_row, const size_t A_f_col,
                float **B, const size_t B_f_row, const size_t B_f_col,
                const size_t n)
{
   for (size_t i=0; i<n; i++) {
     for (size_t j=0; j<n; j++) {
       C[C_f_row+i][C_f_col+j] = 0.0;
       for (size_t k=0; k<n; k++) {
         C[C_f_row+i][C_f_col+j] += (A[A_f_row+i][A_f_col+k] * B[B_f_row+k][B_f_col+j]);
       }
     }

   }
}

/*
 *  @Brief: Auxiliary function for Strassen matrix multiplication
 */

void strassenAuxiliary(float **C, const size_t C_f_row, const size_t C_f_col,
               float **A, const size_t A_f_row, const size_t A_f_col,
               float **B, const size_t B_f_row, const size_t B_f_col,
               const size_t n)
{
    /* code here */
}