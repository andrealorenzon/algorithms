/**
 * @author Andrea Lorenzon (andrelorenzon@gmail.com)
 * @brief Main to test Strassen algorithm
 * @date Nov 2nd, 2019
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../utility.h"
#include "strassen.h"
#include "hw.h"

#define VALUE_RANGE 5
#define MAX_SIZE 512   // 2^n please

int main(int argc, char const *argv[])
{
    /*
    to do:
    - test naive multiplication
    - test strassen
    - test strassen optimized
    
    */
    
    // initialize matrices:
    float **C0 = allocateMatrix(MAX_SIZE, MAX_SIZE);
    float **C1 = allocateMatrix(MAX_SIZE, MAX_SIZE);
    float **C2 = allocateMatrix(MAX_SIZE, MAX_SIZE);
    float **A  = allocateMatrix(MAX_SIZE, MAX_SIZE);
    float **B  = allocateMatrix(MAX_SIZE, MAX_SIZE);

    // fill matrices:
    randomFillMatrix(A, MAX_SIZE, MAX_SIZE, VALUE_RANGE);
    randomFillMatrix(B, MAX_SIZE, MAX_SIZE, VALUE_RANGE);

    // timing:
    struct timespec beginTime, endTime;
    double naiveTime, strassenTime, optimizedTime;
    int correctness=0;

    // run for matrices up to MAX_SIZE, in powers of 2:

    printf("Size\tNaive\t\tStrassen\tStrassen Opt.\tCorrectness\n");
    printf("----\t-----\t\t--------\t-------------\t-----------\n");    

    for (size_t i = 2; i <= MAX_SIZE; i *= 2)
    {
        
        clock_gettime(CLOCK_REALTIME, &beginTime);
        naiveMatrixMultiplication(C0, A, B, i, i, i, i);
        clock_gettime(CLOCK_REALTIME, &endTime);
        naiveTime = getExecutionTime(beginTime, endTime);

        clock_gettime(CLOCK_REALTIME, &beginTime);
        strassen(C1, A, B, i);
        clock_gettime(CLOCK_REALTIME, &endTime);
        strassenTime = getExecutionTime(beginTime, endTime);

        clock_gettime(CLOCK_REALTIME, &beginTime);
        strassenOptimized(C2, A, B, i);
        clock_gettime(CLOCK_REALTIME, &endTime);
        optimizedTime = getExecutionTime(beginTime, endTime);

        correctness = matrixEquals(C0,i,i,C0,i,i)*4000+ matrixEquals(C0, i, i, C1, i, i)  +  matrixEquals(C1, i, i, C2, i, i)*20 + matrixEquals(C0, i, i, C2, i, i) *300;

        printf("%zd\t%lf\t%lf\t%lf\t%d\n", i, naiveTime, strassenTime, optimizedTime, correctness);
        //       ^ fix this zd in d if int later

         
    }
    printf("Corr: \n4: C0=C0\n3: C0=C2\n2: C1=C2\n1: C0=C1\n\n");
    return 0;
}
