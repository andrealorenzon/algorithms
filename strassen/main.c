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
#define MAX_SIZE 1024   // 2^n please

int main(int argc, char const *argv[])
{
    /*
    to do:
    - test naive multiplication
    - test strassen
    - test strassen optimized
    
    */
    
    // initialize matrices:
    float **C0 = allocate_matrix(MAX_SIZE, MAX_SIZE);
    float **C1 = allocate_matrix(MAX_SIZE, MAX_SIZE);
    float **C2 = allocate_matrix(MAX_SIZE, MAX_SIZE);
    float **A  = allocate_matrix(MAX_SIZE, MAX_SIZE);
    float **B  = allocate_matrix(MAX_SIZE, MAX_SIZE);

    // fill matrices:
    random_fill_matrix(A, MAX_SIZE, MAX_SIZE, VALUE_RANGE);
    random_fill_matrix(B, MAX_SIZE, MAX_SIZE, VALUE_RANGE);

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
        naive_matrix_mul(C0, A, B, i, i, i, i);
        clock_gettime(CLOCK_REALTIME, &endTime);
        naiveTime = get_execution_time(beginTime, endTime);

        clock_gettime(CLOCK_REALTIME, &beginTime);
        strassen(C1, A, B, i);
        clock_gettime(CLOCK_REALTIME, &endTime);
        strassenTime = get_execution_time(beginTime, endTime);

        clock_gettime(CLOCK_REALTIME, &beginTime);
        strassen_opt(C2, A, B, i);
        clock_gettime(CLOCK_REALTIME, &endTime);
        optimizedTime = get_execution_time(beginTime, endTime);

/*  // correctness, up to machine epsilon

        correctness = almost_same_matrix(C0,i,i,C0,i,i)*4000+ 
                        almost_same_matrix(C0, i, i, C1, i, i)  +  
                        almost_same_matrix(C1, i, i, C2, i, i)*20 + 
                        almost_same_matrix(C0, i, i, C2, i, i) *300;
*/

        correctness = same_matrix(C0,i,i,C0,i,i)*1000+ 
                        same_matrix(C0, i, i, C1, i, i)*4  +  
                        same_matrix(C1, i, i, C2, i, i)*30 + 
                        same_matrix(C0, i, i, C2, i, i) *200;



        printf("%zd\t%lf\t%lf\t%lf\t%d\n", i, naiveTime, strassenTime, optimizedTime, correctness);
        //       ^ fix this zd in d if int later

         
    }
    printf("Corr: \n1000: \tC0=C0\n200: \tC0=C2\n30: \tC1=C2\n4: \tC0=C1\n\n");
    return 0;
}
