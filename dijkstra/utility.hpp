#pragma once

#include <stdio.h>
#include <iostream> 
#include <vector>
#include <cstdint>
#include <climits>
#include <string>

/** @brief A utility for square matrix creation and initialization
 *  @param n dimension of the matrix
 *  @param default_value the default filler of the matrix 
 *  @return std::vector<std::vector<int>> square matrix, filled with default value
 */

std::vector<std::vector<int>> createMatrix (int n, int default_value);

/** @brief fill an adjacency matrix with random values. diagonal is zero. every node has a
* random probability of being connected to other nodes. the probability is computed
* from the total number of nodes.
* @param adjM a square int matrix, std::vector<std::vector<int>>
* @param n the dimension of the input matrix
*/

void initializeSparseRandomIntegerMatrix (std::vector<std::vector<int>>& adjM, int n);

/** @brief prints a matrix
* @param adjM a square int matrix, std::vector<std::vector<int>>
* @param n the dimension of the input matrix
*/
void representMatrix (std::vector<std::vector<int>>& adjM, int n);

/**
 * @brief a utility function to find the vertex with the minimum
 * distance value from the set of vertices not yet included in the shortest path tree.
 * 
 * @param distanceVector int vector of node distances 
 * @param shortestPathSet boolean vector that states if every node is in the shortest path yet
 * @param n nodes size
 * 
 * @returns the index of the nearest node
 */

int minDistance( std::vector<int> distanceVector, std::vector<bool>shortestPathSet, unsigned n); 
    
/**
 * @brief A utility function to print the  distance array 
 * @param dist the distance array
 */

void printDijkstra(std::vector<int>dist);

/**
 * @brief Dijkstra's implementation
 * 
 * @param adjM a n*n, symmetric, adjacency matrix
 * @param src source node
 * @param n size of the matrix
 */


void dijkstra(std::vector<std::vector<int>> graph, int source);