/**
 * @author Andrea Lorenzon (andrelorenzon@gmail.com)
 * @brief heap struct and methods
 * @date Nov 6, 2019
 */
#ifndef HEAP_H__
#define HEAP_H__

#include <stdlib.h>

/**
 * @brief Integer binary heap struct
 * @var heap  A pointer to the array of integers of the heap.
 * @var size  The size of the array of values.
 * @var comp  The comparison function used by the binary heap.
 */

typedef struct BinaryHeap
{
    int * heap;
    size_t size;
    int (* comp) (int, int);
} BinaryHeap;

/**
 * @brief binary heap constructor
 * @param  a       integer array to be heapified.
 * @param  size_a  The size of the array.
 * @param  fcomp   The comparison function used as heap property.
 */
BinaryHeap build_heap(int * a, size_t size_a, int (*fcomp)(int,int));

// destructor
void free_heap(BinaryHeap * H);

#endif // HEAP_H__