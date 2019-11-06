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


/* QUICKSORT */

/**
 * @brief Partitions the array, putting all elements lower than the pivot before it, and
 *        all element higher than the pivot after it.
 * @param  array      A pointer to the array of integers to be sorted.
 * @param  low        The lower bound index of the array.
 * @param  high       The upper bound index of the array. 
 * @param  pivot_idx  The index of the pivot value used for partition.
 * @return int    The index of the pivot after the partitioning.
 */
int partition(int * array, size_t low, size_t high, size_t pivot_idx);

/**
 * @brief Recursive quicksort auxiliary method.
 * @param  array    A pointer to the array of integers to be sorted.
 * @param  low      The lower bound index of the array.
 * @param  high     The upper bound index of the array. 
 * @param  central  If 1, uses the central pivot, else uses low.
 */
void quicksort_rec(int * array, size_t low, size_t high, size_t central);

/**
 * @brief Quicksort algorithm
 * @param  array      A pointer to the array of integers to be sorted.
 * @param  size       The size of the array to be sorted.
 * @param  pivot_idx  The index of the pivot value used for partition.
 * @param  central  If 1, uses the central pivot, else uses low.
 */
void quicksort(int * array, size_t size, size_t central);

/* HEAP SORT */
/**
 * @brief Heapsort algorithm.
 * @param  array  A pointer to the array of integers to be sorted.
 * @param  size   The dimension of the array of integers.
 */
void heapsort(int * array, size_t size);

/* COUNTING SORT*/

/**
 * @brief Counting sort algorithm.
 * @param  array  A pointer to the array of integers to be sorted.
 * @param  size   The dimension of the array of integers.
 * @param  bound  The upper bound for the domain of values in array.
 */
void counting_sort(int * array, size_t size, size_t bound);

#endif // SORTING_H__