/**
 * @author Andrea Lorenzon (andrelorenzon@gmail.com)
 * @brief heap test main
 * @date Nov 6, 2019
 */


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "heap.h"
#include "../utility.h"

#define ITERATIONS 1

int main()
{
    const size_t heap_size = 250000000;
    unsigned int ** matr = allocate_matrix_unsigned_int(ITERATIONS, heap_size);
    printf("\nUsing a vector of %ld Elements.\n", heap_size);
    random_fill_matrix_unsigned_int(matr, ITERATIONS, heap_size, heap_size);

    struct timespec b_timer, e_timer;
    printf("Average Time of %d iterations(s): ", ITERATIONS);
    clock_gettime(CLOCK_REALTIME, &b_timer);
    for (size_t i = 0; i < ITERATIONS; i++)
    {
        BinaryHeap H = build_heap(matr[i], heap_size, leq);
    }
    clock_gettime(CLOCK_REALTIME, &e_timer);
    printf("%lf seconds.\n", get_execution_time(b_timer, e_timer)/ITERATIONS);
    deallocate_matrix((void**)matr, ITERATIONS);

}