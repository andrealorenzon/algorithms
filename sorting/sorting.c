#include <math.h>
#include <stdlib.h>
#include "sorting.h"
#include "../utility.h"

#include "vector.h"

/* INSERTION SORT */

void insertion_sort(int * array, size_t size)
{
    size_t j;
    for(size_t i = 1; i < size; i++)
    {
        j = i;
        while (j > 0 && array[j] < array[j-1])
        {
            swap_int(&array[j-1], &array[j]);
            j--;
        }
    }
}

void insertion_sort_float(float * array, size_t start, size_t size)
{
    size_t j;
    for(size_t i = start + 1; i < size; i++)
    {
        j = i;
        while (j > start && array[j] < array[j-1])
        {
            swap(&array[j-1], &array[j]);
            j--;
        }
    }
}

void insertion_sort_int(int * array, size_t start, size_t size)
{
    size_t j;
    for(size_t i = start + 1; i < size; i++)
    {
        j = i;
        while (j > start && array[j] < array[j-1])
        {
            swap_int(&array[j-1], &array[j]);
            j--;
        }
    }
}

void insertion_sort_vector(Vector * v)
{
    if (v->root == NULL || v->root->next == NULL)
    {
        return;
    }
    Node * temp1 = v->root->next;
    while(temp1 != NULL)
    {
        float val = temp1->val;
        int found = 0;
        Node * temp2 = v->root;
        while (temp2 != temp1)
        {
            if(temp2->val > temp1->val && !found)
            {
                val = temp2->val;
                temp2->val = temp1->val;
                found = 1;
            }
            else
            {
                if(found)
                {
                    swap(&(val), &(temp2->val));
                }
            }
            temp2 = temp2->next;
        }
        temp2->val = val;
        temp1 = temp1->next;
    }
}

/////////////////////////////////////////////////////////////////////////////
// Quick Sort
// to do: 
//  - implement partition function
//  - implement recursion auxiliary
//  - implement quicksort calling recursion

// partition

int partition(int * array, size_t low, size_t high, size_t pivot_idx)
{
    size_t pivot = array[pivot_idx];  // set a pivot
    int i = low - 1;
    int j = high + 1;

    while(1)
    {
        do
        {
            ++i;
        } while (array[i] < pivot);  

        do
        {
            j--;
        } while (array[j] > pivot);
        
        if (i >= j)
        {
            return j;
        }
        
        swap_int(&array[i], &array[j]);
    }
}


// recursive auxiliary function: calls 2 quicksort subprocesses.
// note: this could be improved by finding a way to call recursion only on the second half
// to avoid a waiting process, while the "main" process keeps processing the first half,
// stemming a new process instead of splitting in 2.
// Check slides for that before presenting project.

void quicksort_rec(int * array, size_t low, size_t high, size_t central)
{
    if(low < high)
    {
        // if central, set pivot = central, partition, otherwise set pivot = low, partition.
        int pivot = central ? partition(array, low, high, (high + low) / 2) : partition(array, low, high, low);
        // recursion
        quicksort_rec(array, low, pivot, central);
        quicksort_rec(array, pivot + 1, high, central);
    }
}

// quicksort, just calls recursion on the whole array

void quicksort(int * array, size_t size, size_t central)
{
    quicksort_rec(array, 0, size - 1, central);
}

/////////////////////////////////////////////////////////////