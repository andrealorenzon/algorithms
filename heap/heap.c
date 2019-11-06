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