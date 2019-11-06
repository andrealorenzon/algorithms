/**
 * @author Andrea Lorenzon (andrelorenzon@gmail.com)
 * @brief Helper functions / general utilities
 * @date Nov 2nd, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#include "utility.h"

#define EPSILON (0.00001)


void naive_matrix_mul(float **C, float **A, float **B,
                                const size_t A_rows, const size_t A_cols,
                                const size_t B_rows, const size_t B_cols)
{
    if (A_cols != B_rows) {return;}

    for (size_t i=0; i<A_rows; i++) 
    {   for (size_t j=0; j<B_cols; j++) 
        {   C[i][j] = 0.0;
            for (size_t k=0; k<A_cols; k++) 
            {C[i][j] += (A[i][k]*B[k][j]);}
        }
    }
}



float **allocate_matrix(const size_t rows, 
                       const size_t cols) 
{
    float **A=(float **)malloc(sizeof(float *)*rows);                           // rows malloc
    for (size_t i=0; i<rows; i++) {A[i]=(float *)malloc(sizeof(float)*cols);}   // cols malloc
    return A;
}

unsigned int **allocate_matrix_unsigned_int(const size_t rows, const size_t cols)
{
    unsigned int **A=(unsigned int **)malloc(sizeof(unsigned int *)*rows);

    for (size_t i=0; i<rows; i++) 
    {
        A[i]=(unsigned int *)malloc(sizeof(unsigned int)*cols);
    }
    return A;
}

void deallocate_matrix(void **A, 
                      const size_t rows)
{
    for (size_t i = 0; i < rows; i++) {free(A[i]);}     // inner free() -> cols
    free(A);                                            // outer free() -> rows
}                      

float **copy_matrix(float **A, 
                    const size_t rows, 
                    const size_t cols) 
{
    float **C = allocate_matrix(rows, cols);   // allocate output matrix
    for (size_t i=0; i<rows; i++) 
    {
        for (size_t j=0; j<cols; j++) {C[i][j]=A[i][j];}  // elementwise copy
    }
    return C;
}                    

void random_fill_matrix(float **A, 
                        const size_t A_rows, 
                        const size_t A_cols, 
                        int max)
{
    for (size_t i=0; i< A_rows; i++) 
    {
        for (size_t j=0; j< A_cols; j++) 
        {
   	        A[i][j]=rand()%(2*max) - max;   // random Float between -max and +max
        }
    }
}

void random_fill_matrix_unsigned_int(unsigned int **A, const size_t rows, 
                                     const size_t cols, const unsigned int max)
{
    for (size_t i=0; i< rows; i++) 
    {
        for (size_t j=0; j< cols; j++) 
        {
   	        A[i][j]=(unsigned int)(rand() % max);
        }
    }
}

// Randomly fills matrix with uniform distribution values
void random_fill_matrix_unif(float **A, const size_t rows, const size_t cols)
{
    for (size_t i=0; i< rows; i++) 
    {
        for (size_t j=0; j< cols; j++) 
        {
   	        A[i][j] = (double)rand() / (double)RAND_MAX;
        }
    }
}

int check_sorted(float * array, size_t size)
{
    if(size == 1 || size == 0)
        return 1;

    if (array[size - 1] < array[size - 2])
        return 0;

    return check_sorted(array, size - 1);
}

int check_sorted_int(int * array, size_t size)
{
    if(size == 1 || size == 0)
        return 1;

    if(array[size - 1] < array[size - 2])
        return 0;

    return check_sorted_int(array, size - 1);
}

int same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		        float **B, const size_t B_rows, const size_t B_cols)
{
    if ((A_rows != B_rows) || (A_cols != B_cols)) 
    {
        return 0;
    }
    for (size_t i=0; i<A_rows; i++) 
    {
        for (size_t j=0; j<A_cols; j++) 
        {
            if (A[i][j] != B[i][j]) 
            {
	            return 0;
            }
        }
    }
    return 1;
}

int almost_same_matrix(float **A, const size_t A_rows, const size_t A_cols,
		        float **B, const size_t B_rows, const size_t B_cols)
{
    if ((A_rows != B_rows) || (A_cols != B_cols)) 
    {
        return 0;
    }
    for (size_t i=0; i<A_rows; i++) 
    {
        for (size_t j=0; j<A_cols; j++) 
        {
            if ((A[i][j] - B[i][j]) > EPSILON)
            {
	            return 0;
            }
        }
    }
    return 1;
}


double get_execution_time(const struct timespec b_time,
                          const struct timespec e_time)
{
  return (e_time.tv_sec-b_time.tv_sec) + (e_time.tv_nsec-b_time.tv_nsec)/1E9;   // timespecs subtraction
}


void swap_int(int * a, int * b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swap(float* a, float *b)
{
	float temp = *a;
	*a = *b;
	*b = temp;
}

void copy_array_int(int *a, int *b, const size_t size)
{
    for (size_t i = 0; i < size; i++) 
    {
        a[i] = b[i];
    }
}

int max_array_int(int* array, size_t size)
{
    int max = array[0];
    for (size_t i = 0; i < size; i++)
    {
        if(array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}

int leq(int a, int b)
{
    return a <= b;
}

int geq(int a, int b)
{
    return a >= b;
}