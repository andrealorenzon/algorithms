#ifndef SORTING_H__
#define SORTING_H__

#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

/* INSERTION SORT */

/**
 * @brief Insertion sort
 * @param  array  A pointer to the array to be sorted.
 * @param  start  The beginning of the array to be sorted.
 * @param  size   The dimension of the array of integers.
 */
void insertion_sort(int * array, size_t size);
void insertion_sort_float(float * array, size_t start, size_t size);
void insertion_sort_int(int * array, size_t start, size_t size);

// Performs insertion sort on a vector of nodes.
void insertion_sort_vector(Vector * v);


#endif // SORTING_H__