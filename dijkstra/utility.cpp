#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <iostream> 
#include <vector>
#include <climits>
#include <cstdint>
#include <string>

/** @brief A utility for square matrix creation and initialization
 *  @param n dimension of the matrix
 *  @param default_value the default filler of the matrix 
 *  @return a reference to std::vector<std::vector<int>> square matrix, filled with default value
 */

std::vector<std::vector<int>>createMatrix (int n, int default_value) {
	std::vector<int> row = std::vector<int>(n, default_value);
	std::vector<std::vector<int>> v = std::vector<std::vector<int>>(n, row);
	return v;
}

/** @brief fill an adjacency matrix with random values. diagonal is zero. every node has a
* random probability of being connected to other nodes. the probability is computed
* from the total number of nodes.
* @param adjM a square int matrix, std::vector<std::vector<int>>
* @param n the dimension of the input matrix
*/

// randomly fills a zero matrix of size n with weights
void initializeSparseRandomIntegerMatrix (std::vector<std::vector<int>>& adjM, int n) {
	std::cout<<"matrix initialization called..."<<std::endl;    
	
    for (int i = 0; i<n; i++) {
        for (int j = i+1; j<n; j++) {
            if (rand()%10 < 2) {  // create only 20% of edges
                int val = rand()%10;  // get a weight between 0 and 9
                adjM[i][j] = val;
                adjM[j][i] = val;
            }
        }
        adjM[i][i] = 0;
        
    };
}

//prints a adj matrix
void representMatrix (std::vector<std::vector<int>>& adjM, int n) {
    std::cout<<"\nprinting matrix...(visualize on https://graphonline.ru/en/ )"<<std::endl;    
	
    for (auto row = adjM.begin();row != adjM.end(); ++row) {
        
        for (auto elem = (*row).begin(); elem != (*row).end(); ++elem) {
            std::cout <<  *elem << ' ';
        };
        std::cout<<std::endl;
    };
}

// minimum of distance of other nodes
int minDistance( std::vector<int> distanceVector, std::vector<bool>shortestPathSet, unsigned n) { 
    int min = INT_MAX;  // Infinite
    int min_index;

    for (int v = 0; v < n; v++) {
        if (shortestPathSet[v] == false && distanceVector[v] <= min) {
            min = distanceVector[v];
            min_index = v; 
        }
    }
    return min_index; 
}

//print distance array solution 
void printDijkstra(std::vector<int>dist) 
{ 
    printf("Vertex \t-> Distance from Source\n"); 
    for (auto i = 0; i < dist.size(); ++i){
        std::cout << i << "\t->\t"<< (dist[i]==2147483647 ? "no way" : (std::to_string(dist[i]))) <<"\n"; 
    }
    
} 

//Dijkstra
 
void dijkstra(std::vector<std::vector<int>> graph, int source) 
{ 
    // count nodes
    int n = graph.size();

    // vector of distances from every node to the source, initialized to Infinite
    std::vector<int> distance (n, INT_MAX); 
    
    // true if a node is already in shortest path tree or if the shortest distance of
    // the node from the source is already computed. Initialize to FALSE.
    std::vector<bool> shortPathSet (n,false);
       
    // Initialize source-source distance to 0 
    distance[source] = 0; 
  
    // Find shortest path for all vertices 
    for (int count = 0; count < n - 1; count++) { 
        // Pick the minimum distance vertex from the set of vertices not 
        // yet processed. u is always equal to source in the first iteration. 
        int u = minDistance(distance, shortPathSet, n); 
  
        // flag the vertex as done 
        shortPathSet[u] = true; 
  
        // Update distance value of the adjacent vertices of the picked vertex. 
        for (int v = 0; v < n; v++) 
  
            // Update distance[v]...

            if (!shortPathSet[v] &&   // ...IF: it has to be in shortPathSet....
                graph[u][v] && // .. and there is actually an edge..
                distance[u] != INT_MAX  &&  // ..and the distance is not infinite..
                distance[u] + graph[u][v] < distance[v]) // .. and it is a convenient path

                distance[v] = distance[u] + graph[u][v];  // ...then update distance.
    } 
  
    // print the constructed distance array 
    printDijkstra(distance); 
} 