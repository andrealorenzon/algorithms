/**
 * @author Andrea Lorenzon (andrelorenzon@gmail.com)
 * @brief heap methods
 * @date Nov 6, 2019
 */

#include <stdio.h>
#include <limits.h>

#include "heap.h"
#include "../utility.h"

BinaryHeap build_heap(int * a, size_t size_a, int (*fcomp)(int,int))
{
    //wraps an array, its size and comparator function pointer
    BinaryHeap H = {H.heap = a, H.size = size_a, H.comp = fcomp}; 
    
    // free heapification at creation:
    // for all the nodes from the parent of the last, downwards...
    for (int i = parent(last(&H)); i >= 0; i--)  
    {
        heapify(&H, i);  // ...heapify the array
    }
    return H;  // return the heap object
}

// free_heap, free the heap opject's heapified array
void free_heap(BinaryHeap * H) 
{ 
    free(H->heap); 
}

// root is the first element of the heap
int root()
{ 
    return 0; 
}


// last is, well, the last element...
int last(BinaryHeap * H) 
{ 
    return H->size - 1;
}

// left child of [i] is [2i+1]
int left(int i) 
{ 
    return 2 * i + 1; 
}

// right child of [i] is [2i+2]
int right(int i) 
{ 
    return 2 * i + 2; 
}

// parent of [i] is [(i-1)/2], that floors automatically
int parent(int i) 
{ 
    return (i - 1) / 2;
}


// check if [i] is [0], returns 1 if it is, and other otherwise
int is_root(int i) 
{ 
    return i == root();
}


// checks if [i] is a valid index (<= of array size)
int is_valid(BinaryHeap * H, int i) 
{ 
    return H->size > i;
}

// returns the min (that is root).
int heap_min(BinaryHeap * H) 
{ 
    return H->heap[root()];
}

// swaps two elements in the heap array, used in heapify
void heap_swap(BinaryHeap * H, size_t i, size_t m)
{
  int tmp = H->heap[i];
  H->heap[i] = H->heap[m];
  H->heap[m] = tmp;
}