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
void heap_swap(BinaryHeap * H, size_t i, size_t j)
{
  int tmp = H->heap[i];
  H->heap[i] = H->heap[j];
  H->heap[j] = tmp;
}

/**
 * @brief Restores the heap property. Used in other methods.
 * 
 * @param  Heap  The heap.
 * @param  i  The index from which the heapification process will start.
 */
void heapify(BinaryHeap * Heap, int i)
{
    int currentNode = -1;   // sets currentNode and startingNode to their beginning values
    int startingNode = i;

    // Left and right child
    int leftChild, rightChild;

    while(startingNode != currentNode)
    {
        
        // sets current node to the starting node from which I have to heapify the heap
        currentNode = startingNode;
        // identifies its children
        rightChild = right(currentNode);
        leftChild = left(currentNode);
        // if the left child is alredy ok with the comparation function, leave starting node where it is, otherwise sets startingNode to leftChild
        startingNode = is_valid(Heap, leftChild) && Heap->comp(Heap->heap[leftChild], Heap->heap[startingNode]) ? leftChild : startingNode;
        // do the same for the right node
	    startingNode = is_valid(Heap, rightChild) && Heap->comp(Heap->heap[rightChild], Heap->heap[startingNode]) ? rightChild : startingNode;
        // if the value of startingNode changed, swap values of start and current nodes
        if(startingNode != currentNode)
        {
            heap_swap(Heap, startingNode, currentNode);
        }
    }
}