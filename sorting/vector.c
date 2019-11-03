#include "vector.h"
#include <stdlib.h>
#include "../utility.h"

#include <stdio.h>

#include "vector.h"
#include "../utility.h"

// Node constructor: allocates, sets float value, and no successors

Node * build_node(float val)
{
    Node * n = (Node *)malloc(sizeof(Node));
    n->val = val;
    n->next = NULL;
    return n;
}

// Node destructor : iteratively destroy subsequent Nodes

void free_node(Node * node)
{
    if (node->next != NULL)
    {
        free_node(node->next);
    }
    free(node);
}

// Vector constructor: creates an empty vector, of lenght 0 and without root

Vector build_vector()
{
    Vector V = {V.length = 0, V.root = NULL};
    return V;
}

// Vector destructor: iteratively destroy nodes, from root

void free_vector(Vector V)
{
    if(V.root != NULL)
    {
        free_node(V.root);
    }
}

// retrieve a node from a vector: returns a pointer to the node at index idx, walking through the linked list.

Node * get_node(Vector V, size_t idx)
{
    Node * cur = V.root;
    for (size_t i = 0; i < idx; i++)
    {
        if(cur->next != NULL)
        {
            cur = cur->next;
        }
    }
    return cur;
}

// retrive float value from a vector node, given the vector and an index

float get_val(Vector V, size_t idx)
{
    return get_node(V, idx)->val;
}

// append a node to a vector: if it's empty, assign as root. otherwise, assign as "next" of last node.

void append(Vector * V, float val)
{
    if(V->length == 0)
    {
        V->root = build_node(val);
    }
    else
    {
        Node * last = get_node(*V, V->length - 1);
        last->next = build_node(val);
    }
    V->length++;
}

// constructor of a bucket: builds an array of Vectors and creates them.

Vector* build_bucket(size_t size)
{
    Vector * B = (Vector *)malloc(sizeof(Vector) * size);
    for (size_t i = 0; i < size; i++)
    {
        B[i] = build_vector();
    }
    return B;
}

// destructor of a bucket (list of vectors): iteratively destroys vectors

void free_bucket(Vector* B, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        free_vector(B[i]);
    }
    free(B);
}