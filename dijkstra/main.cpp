// A C++ program for Dijkstra's single source shortest path algorithm. 
// The program is for adjacency matrix representation of the graph 

#include <limits.h> 
#include <stdio.h>
#include <iostream> 
#include <vector>
#include "utility.hpp"
#include <time.h> // srand



#define MATRIX_SIZE 20   // > 8 for test purposes

// test createVector

int main(int argc, char const *argv[])
{
    // randomize rand() seed:
    srand(time(NULL));    

    // test createMatrix() to create a 10x10 matrix filled with 0s:
    
    std::vector<std::vector<int>> test = createMatrix(MATRIX_SIZE,0);
	std::cout<<"\n********************************************************\n\
    Test1: testing createMatrix()\
    \n********************************************************\n\
    \n\t0 ?= " <<test[0][1]<<std::endl;
	

    // test initialization of sparse random integer matrix

    std::vector<std::vector<int>>& adjMatrix = test;
    
    // testing diagonal = 0s
    
    std::cout<<"\n********************************************************\n\
    Test2.1: testing initializeSparseRandomIntegerMatrix()\
    \n********************************************************\n"<<std::endl;
    initializeSparseRandomIntegerMatrix(adjMatrix, MATRIX_SIZE);
    std::cout<<"\tadjMatrix on diagonal:"<<adjMatrix[0][0]<<","<<adjMatrix[1][1]<<","<<adjMatrix[2][2]<<"."<<std::endl;

    //testing that other elements are symmetrical but mostly zeros:
    std::cout<<"\n********************************************************\n\
    Test2.2: testing initializeSparseRandomIntegerMatrix()\
    \n********************************************************\n"<<std::endl;
    std::cout<<
    "\tare some random elements symmetrical w.r.t. the diagonal?\n\t" << std::endl;
    bool failed = false;
    std::cout << "i1\t|\ti2\t|\tfailed\t|\tthey are.." << std::endl;
    std::cout <<"---------------------------------------------------------------"<<std::endl;
    for (auto elem=0; elem < MATRIX_SIZE; elem++) {
        
        int i1 = rand() % MATRIX_SIZE;
        int i2 = rand() % MATRIX_SIZE;

        failed = failed || (adjMatrix[i1][i2]!=adjMatrix[i2][i1]);
        
        std::cout << i1 << "\t|\t" << i2 << "\t|\t" << failed << "\t|\t" << adjMatrix[i1][i2] << " =? " << adjMatrix[i2][i1] << std::endl;
    };
    
    std::cout << "\n\t" << (failed ? "Nope, something's wrong." : "Yeah. Test passed.") << std::endl;

    // testing representMatrix()
    std::cout<<"\n********************************************************\n\
    Test3.1: testing representMatrix(), calling on adjMatrix \
    \n********************************************************\n"<<std::endl;
    representMatrix(test, MATRIX_SIZE);

    // finally testing Dijkstra
    std::cout<<"\n********************************************************\n\
    Test4.1: testing Dijkstra's implementation\
    \n********************************************************\n";
    dijkstra(test,0);

	return 0; 
}