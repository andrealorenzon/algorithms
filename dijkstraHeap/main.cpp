/**
 * @author Andrea Lorenzon (andrelorenzon@gmail.com)
 * @brief Dijkstra with heaps
 * @date Nov 16, 2019
 */

     
    #include <iostream>
    #include <queue>
    #include <vector>
    #include <climits>
    #include <chrono>
    
    #include "../utility.h"



    using namespace std::chrono;


    #define INF INT_MAX //Infinity
     
    //Maximum possible number of vertices.
    const int size=32768; 

    //Adjacency list
    std::vector<std::pair<int,int> > adjM[size];

    //vector for shortest distances
    int distances[size]; 

    //vector to record if a node is already visited
    bool alreadyVisited[size]={0}; 
     
    void Dijkstra(int source, int n) //Algorithm for SSSP
    {
         //Set initial distances to Infinity
        for(int node=0;node<size;node++)
            distances[node]=INF;
        
        //Custom Comparator for Determining priority for priority queue (shortest edge comes first)
        class order{public: bool operator ()(   std::pair<int, int>&p1 , \
                                                std::pair<int, int>&p2){
                                                    return p1.second>p2.second;
                                                }
                    };
        
        //Priority queue heap to store vertex,weight pairs
        // uses custom comparator "order" previously defined
        std::priority_queue<std::pair<int,int> , \
                            std::vector<std::pair<int,int> >, \
                            order>  \
                            priorityQueueNodes; 

        //Pushing the source with distance from itself as 0
        
        distances[source] = 0;
        priorityQueueNodes.push( std::make_pair(source,0)); 

        while(!priorityQueueNodes.empty())
        {
            //Current vertex. The shortest distance for this has been found
            std::pair<int, int> curr=priorityQueueNodes.top(); 

            //remove that node from the queue
            priorityQueueNodes.pop();

            //'pathTotalCost' the final shortest distance for this vertex
            int currentVertex=curr.first;
            int pathTotalCost=curr.second; 

            //If the vertex is already visited, no point in exploring adjacent vertices
            if(!alreadyVisited[currentVertex]) {
                
            

                alreadyVisited[currentVertex]=true;

                //Iterating through all adjacent vertices
                for(int i=0;i<adjM[currentVertex].size();i++) {
                    
                    // If this node is not visited and the current parent node distance+distance from there to this 
                    // node is shorted than the initial distace set to this node, update it

                    int currentNodeIndex = adjM[currentVertex][i].first;
                    int currentNodeWeight = adjM[currentVertex][i].second;

                    bool notVisited = !alreadyVisited[currentNodeIndex];

                    if( notVisited && currentNodeWeight+pathTotalCost<distances[currentNodeIndex]) {
                        
                        //Set the new distance and add to priority queue
                        priorityQueueNodes.push(std::make_pair(currentNodeIndex,
                                                            (distances[currentNodeIndex]=currentNodeWeight+pathTotalCost))); 
                    }
                }
            }
        }
    }
     
    int main() //Driver Function for Dijkstra SSSP
    {    
        //Number of nodes:
        int nVertices,nEdges,vertex1,vertex2,weight1;
        
        std::cout<<"Enter number of vertices and edges in the graph\n";
        std::cin>>nVertices>>nEdges;
        
        std::cout<<"Vertex 1, vertex 2, edge weight:\n";
        


        //Building Graph
        for(int i=0;i<nEdges;++i) 
        {
            //read input: vertex1, Vertex2, weight of edge
            //std::cin>>vertex1>>vertex2>>weight1; 
            vertex1 = rand() % nVertices;
            vertex2 = rand() % nVertices;
            weight1 = rand() % 10;

            //update adj. matrices of both vertices
            adjM[vertex1].push_back(std::make_pair(vertex2,weight1));
            adjM[vertex2].push_back(std::make_pair(vertex1,weight1));
        }
        
        // std::cout<<"Enter source node:\n";
        int source = 1;
        // std::cin>>source;
        struct timespec beginTime, endTime;
       
        auto start = high_resolution_clock::now();
        Dijkstra(source,nEdges);//SSSP from source (Also passing number of vertices as parameter)
        auto stop = high_resolution_clock::now();
        auto heapTime = duration_cast<microseconds>(stop - start); 

        
        std::cout << "Dijkstra algorithm performed in " << heapTime.count() << " microseconds." << std::endl;


        std::cout<<"Source is: "<<source<<". \nThe shortest distance to every other vertex from here is: \n";
        for(int edge=1;edge<=nVertices;edge++)//Printing final shortest distances from source
        {
            //std::cout<<"Vertex: "<<edge<<" , Distance: ";
            //distances[edge]!=INF? std::cout<<distances[edge]<<"\n" : std::cout<<"-1\n";
        }
        std::cout<<"done"<<std::endl;
        return 0;
    }