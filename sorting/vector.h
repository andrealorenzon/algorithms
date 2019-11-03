#ifndef VECTOR_H__
#define VECTOR_H__

#include <stdlib.h>

/**
 * @brief A Node for a Vector of floats
 * @var val   The float value of the node.
 * @var next  The next node in the vector.
 */
typedef struct Node
{
    float val;
    struct Node* next;
} Node;

/**
 * @brief Vector of Nodes, as a single-linked-list
 * @var length  The length of the vector
 * @var root    The root node of the vector.
 */
typedef struct Vector
{
    size_t length;
    Node* root;
} Vector;

// Node constructor
Node * build_node(float val);

// Node destructor
void free_node(Node * node);

// Vector constructor
Vector build_vector();

// Vector destructor
void free_vector(Vector V);

// Retrieve a node and its value
Node * get_node(Vector V, size_t idx);
float get_val(Vector V, size_t idx);

// Appends a new node to the end of the vector
void append(Vector * V, float val);

// Ctor and dtor for a bucket (list of vectors)
Vector* build_bucket(size_t size);
void free_bucket(Vector* B, size_t size);

#endif //VECTOR_H