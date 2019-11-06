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

// root is the first element of the heap
int root();

// last is, well, the last element...
int last(BinaryHeap * H);

// left child of [i] is [2i+1]
int left(int i); 

// right child of [i] is [2i+2]
int right(int i);

// parent of [i] is [(i-1)/2], that floors automatically
int parent(int i);

// check if [i] is [0], returns 1 if it is, and other otherwise
int is_root(int i);

// checks if [i] is a valid index (<= of array size)
int is_valid(BinaryHeap * H, int i);

// returns the min (that is root).
int heap_min(BinaryHeap * H);

// swaps two elements in the heap array, used in heapify
void heap_swap(BinaryHeap * H, size_t i, size_t m);



#endif // HEAP_H__