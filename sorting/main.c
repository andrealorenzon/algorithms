#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../utility.h"
#include "sorting.h"

#define MAX_SIZE 67000
#define PRINT_STOP 1000
#define INSERTION_STOP 100000
#define IMPLEMENTED_ALGORITHMS_BY_NOW 6  

int main(int argc, char *argv[]) {
    struct timespec b_time, e_time;
    double insert_time, quick_time, heap_time, count_time, radix_time, bucket_time;
    int all_sorted = 0;
    printf("Size\t\tInsertion\tQuick\t\tHeap\t\tCount\t\tRadix\t\tBucket\t\tAll Sorted\n");
    printf("----\t\t---------\t-----\t\t----\t\t-----\t\t-----\t\t------\t\t----------\n");
 
    for (size_t i = 256; i < MAX_SIZE; i *= 2) 
    {
        
// allocate a (5 x MAX_SIZE) matrix. Every row will be used for a different algorithm.

        unsigned int ** mat = allocate_matrix_unsigned_int(IMPLEMENTED_ALGORITHMS_BY_NOW, i);
        random_fill_matrix_unsigned_int(mat, IMPLEMENTED_ALGORITHMS_BY_NOW, i, MAX_SIZE);

        // Matrix of uniformly distributed float values for Bucket sort.
        float ** mat_unif = allocate_matrix(1, i);
        random_fill_matrix_unif(mat_unif, 1, i);

        // Used to validate sorting results.
        int * sorted = (int *)malloc(sizeof(int) * 6);

        // execute insertion sort
        // Stop it to avoid slowing everything down at large sizes
        if(i <= INSERTION_STOP)
        {
            clock_gettime(CLOCK_REALTIME, &b_time);
            insertion_sort(mat[0], i);
            clock_gettime(CLOCK_REALTIME, &e_time);
            insert_time =  get_execution_time(b_time, e_time);
        }
        
        // execute quicksort

        clock_gettime(CLOCK_REALTIME, &b_time);
        //call quicksort without centra pivot
        quicksort(mat[1], i, 0); // set pivot = 1 for central pivot. times do not change.
        clock_gettime(CLOCK_REALTIME, &e_time);
        quick_time =  get_execution_time(b_time, e_time);


        // execute heapsort

        clock_gettime(CLOCK_REALTIME, &b_time);
        //heapsort(mat[2], i);
        quicksort(mat[2], i, 0);
        clock_gettime(CLOCK_REALTIME, &e_time);
        heap_time =  get_execution_time(b_time, e_time);

        // counting sort

        clock_gettime(CLOCK_REALTIME, &b_time);
        counting_sort(mat[3], i, MAX_SIZE);  // <<<<<<<<<<<<<<<<< REMEMBER TO SET INDEX TO THE APPROPRIATE ROW!!!
        clock_gettime(CLOCK_REALTIME, &e_time);
        count_time =  get_execution_time(b_time, e_time);


        // radix sort

        clock_gettime(CLOCK_REALTIME, &b_time);
        radix_sort(mat[4], i); // <<<<<<<<<<<<<<<<< REMEMBER TO SET INDEX TO THE APPROPRIATE ROW!!!
        clock_gettime(CLOCK_REALTIME, &e_time);
        radix_time =  get_execution_time(b_time, e_time);
        
        // bucket sort

        clock_gettime(CLOCK_REALTIME, &b_time);
        bucket_sort(mat_unif[0], i);
        clock_gettime(CLOCK_REALTIME, &e_time);
        bucket_time =  get_execution_time(b_time, e_time);



        // Validate the sorting process
        for (size_t j = 0; j < IMPLEMENTED_ALGORITHMS_BY_NOW; j++)
        {
            sorted[j] = check_sorted_int(mat[j], i);
        }
        sorted[5] = check_sorted(mat_unif[0], i);
        // end validation


        all_sorted = sorted[0] && sorted[1] && sorted[2] && sorted[3] && sorted[4] && sorted[5];

        if(i <= INSERTION_STOP)
        {

            printf("%ld\t\t%lf\t%lf\t%lf\t%lf\t%lf\t%f\t\t%s\n",
                    i, insert_time
                    ,quick_time, 
                    heap_time, 
                    count_time, 
                    radix_time, 
                    bucket_time, 
                    all_sorted ? "True":"False"
                    );

        }

        else if (i <= PRINT_STOP)
        {
            int all_sorted = sorted[1] && sorted[2] && sorted[3] && sorted[4] && sorted[5];
            printf("%ld\t\t\t\t%lf\t%lf\t%lf\t%lf\t%lf\t%s\n",
                    i, quick_time, heap_time, count_time, 
                    radix_time, bucket_time, all_sorted ? "True":"False");
        }
        else
        {
            int all_sorted = sorted[1] && sorted[2] && sorted[3] && sorted[4] && sorted[5];
            printf("%ld\t\t\t%lf\t%lf\t%lf\t%lf\t%lf\t%s\n",
                    i, quick_time, heap_time, count_time, 
                    radix_time, bucket_time, all_sorted  ? "True":"False");
        }

        deallocate_matrix((void **)mat, IMPLEMENTED_ALGORITHMS_BY_NOW);
        deallocate_matrix((void **)mat_unif, 1);
        free(sorted);
        
    }
    return 0;
}