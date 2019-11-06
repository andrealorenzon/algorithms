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
