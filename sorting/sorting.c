#include <math.h>
#include <stdlib.h>
#include "sorting.h"
#include "../utility.h"
#include "../heap/heap.h"  // for heapsort

#include "vector.h"

/* INSERTION SORT */

void insertion_sort(int * array, size_t size)
{
    size_t key;                                    // key of the parsed element
    for(size_t i = 1; i < size; i++)               // for every element of the array
    {
        key = i;                                   // set the key equal to the current element index
        while (key > 0 && array[key] < array[key-1])// this cycle checks if there are elements lesser than the key before
        {
            swap_int(&array[key-1], &array[key]);  // in that case, it swaps them with the key element
            key--;                                 // then make a step back by reducing the key, rinse and repeat
        }
    }
}

void insertion_sort_float(float * array, size_t start, size_t size) // same but for float
{
    size_t key;
    for(size_t i = start + 1; i < size; i++)
    {
        key = i;
        while (key > start && array[key] < array[key-1])
        {
            swap(&array[key-1], &array[key]);
            key--;
        }
    }
}

void insertion_sort_int(int * array, size_t start, size_t size) // same but for int
{
    size_t key;
    for(size_t i = start + 1; i < size; i++)
    {
        key = i;
        while (key > start && array[key] < array[key-1])
        {
            swap_int(&array[key-1], &array[key]);
            key--;
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

// partition
// Casagrande's algorithm
int partition(int * array, size_t low, size_t high, size_t pivot_idx)
{
    size_t pivot = array[pivot_idx];  // set a pivot
    int i = low - 1;                  // set low index
    int j = high + 1;                 // set high index

    while(1)                          // to skip useless swaps, keep doing the following...
    {
        do                            // increase i until a value lower than the pivot is found
        {
            ++i;
        } while (array[i] < pivot);  

        do
        {
            j--;
        } while (array[j] > pivot);   // reduce j until a value higher than the pivot is found
        
        if (i >= j)                   // if i reaches j, the partition is complete
        {
            return j;                 // return the j index
        }
        
        swap_int(&array[i], &array[j]);  // if it's not complete, perform a swap and start again
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

// counting sort

/* COUNTING SORT */

void counting_sort(int * array, size_t size, size_t bound)
{
    int * c = (int *)calloc(bound, sizeof(int));   // allocate an array of "bound" x 0s int
    int * res = (int *)malloc(sizeof(int) * size); // allocate a result array of size "size" int

    for (int i = 0; i < size; i++)             // for every element, use it as an index, and  
        c[array[i]]++;                         // increase c[element] value by 1
    
    for (int j = 1; j < bound; j++)            // perform a cumulative sum of c
        c[j] += c[j - 1];
    
    for (int i = size - 1; i >= 0; i--)        // for every element of the original array
    {                                          // preparation of result array:
        res[c[array[i]] - 1] = array[i];       // sort it by getting the element'th object and placing it in results, in the appropriate place
        c[array[i]]--;                         // reduce the element counter by 1
    }

    copy_array_int(array, res, size);  // overwrite original array
    free(c);                           // free used memory for c and res
    free(res);
}

/* RADIX SORT */

void radix_sort(int * array, size_t size)
{
    int max = max_array_int(array, size); // compute max of the array values
    for (size_t i = 1; max / i > 0; i *= 10)   // for every digit of the max value....
    {  // perform a counting sort on that digit in this way:
        int * c = (int *)calloc(10, sizeof(int));  // allocate a counter 0-vector of 10 elements
        int * res = (int *)malloc(sizeof(int) * size); // allocate a result vector of as many elements as the origina array size

        for (size_t j = 0; j < size; j++)  //for every original element
        {
            c[(array[j] / i) % 10]++; // increase the counter array correspondent value by one. The value is the element%10
        }
        for (int j = 1; j < 10; j++) //for every counter element but the first...
        {
            c[j] += c[j - 1];  //..perform a cumulative sum, like for counting sort.
        }
        for (int j = size - 1; j >= 0; j--)   // for every element of the original array...
        {
            res[c[(array[j] / i) % 10] - 1] = array[j];  // sort it by getting the element'th object and placing it in results, in the appropriate place
            c[(array[j] / i) % 10]--; // and reduce the element counter by 1
        }
        copy_array_int(array, res, size); // overwrite original array
        free(c);  // free used memory for c and res
        free(res);
    }
}

/* BUCKET SORT */

void bucket_sort(float * array, size_t size)
{
    Vector * B = build_bucket(size);  // build a bucket (vector of vectors) of the same size of the array

    for (size_t i = 0; i < size; i++)  // for every element
    {
        append(&B[(int)(array[i] * size)], array[i]); // insert the element in the relative bucket
    }
    for (size_t i = 0; i < size; i++)
    {
        insertion_sort_vector(&B[i]); // perform an insertion sort on every bucket
    }
    int idx = 0;
    for(size_t i = 0; i < size; i++)
	{
		for(size_t j = 0; j < B[i].length; j++)
		{
            array[idx] = get_val(B[i], j);  // concatenate bucket elements
            idx++;
		}
    }
	free_bucket(B, size);  // free bucket memory
}


/* HEAP SORT*/

void heapsort(int * array, size_t size)
{
    BinaryHeap H = build_heap(array, size, geq);
    for (int i = size - 1; i >= 1; i--)
    {
        array[i] = remove_min(&H);
    }
}