//NAME:        Shuyi Zhao 
//COURSE:      COSC 2437(optional)/5321(required)
//Lab #15:     Graph - Shortest Path (directed, weighted graph)
//ASSIGNED:    Apr 26, 2011
//DUE:         May  3, 2011
//OBJECTIVE:   Illustrate the shortest path algorithm
//The function createWeightedGraph() needs to be implemented.
// Exercise 3 in Chapter 12

#ifndef H_weightedGraph
#define H_weightedGraph

//***************************************************************
// Author: D.S. Malik
//
// class weightedGraphType
// This class specifies the operations to find the weight of the
// shortest path from a given vertex to every other vertex in a
// graph.
//****************************************************************

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cfloat>          //contains constant DBL_MAX
#include "graphType.h"

using namespace std;

class weightedGraphType: public graphType
{
public:
    void createWeightedGraph();
      //Function to create the graph and the weight matrix.
      //Postcondition: The graph using adjacency lists and 
      //    its weight matrix is created.
      
    void createWeightedGraph(ifstream&);
      //Function to create the graph and the weight matrix by passing a ifstream file.
      //Postcondition: The graph using adjacency lists and 
      //    its weight matrix is created.

    void shortestPath(int vertex);
      //Function to determine the weight of a shortest path 
      //from vertex, that is, source, to every other vertex 
      //in the graph.
      //Postcondition: The weight of the shortest path from vertex
      //    to every other vertex in the graph is determined.

    void printShortestDistance(int vertex);
      //Function to print the shortest weight from the vertex 
      //specified by the parameter vertex to every other vertex in 
      //the graph.
      //Postcondition: The weight of the shortest path from vertex
      //    to every other vertex in the graph is printed.

    weightedGraphType(int size = 0); 
      //Constructor
      //Postcondition: gSize = 0; maxSize = size;
      //    graph is an array of pointers to linked lists.
      //    weights is a two-dimensional array to store the weights
      //       of the edges.
      //    smallestWeight is an array to store the smallest weight
      //       from source to vertices.

    ~weightedGraphType();
      //Destructor
      //The storage occupied by the vertices and the arrays
      //weights and smallestWeight is deallocated.

protected:
    double **weights;   //pointer to create weight matrix
    double *smallestWeight; //pointer to create the array to store
                     //the smallest weight from source to vertices
};


void weightedGraphType::createWeightedGraph()
{
    cout << "Write the definition of the "
         << "function createWeightedGraph." << endl;

} //createWeightedGraph

void weightedGraphType::createWeightedGraph(ifstream& graphFile)
{
    int vertex;
    int adjacentVertex;
    double weight;

    if (gSize != 0)	//if the graph is not empty, make it empty
        clearGraph(); 
    graphFile >> gSize;	//get the number of vertices
    
    for (int index = 0; index < gSize; index++)
    {
        graphFile >> vertex;
        graphFile >> adjacentVertex;
        while (adjacentVertex != -999)
        {
            graph[vertex].insertLast(adjacentVertex);
            graphFile >> adjacentVertex;
        } //end while
    } // end for
    
    //initialize 2-D weights array with DBL_MAX
    for(int a=0; a < gSize; a++)
        for(int b=0; b < gSize; b++)
            weights[a][b]= DBL_MAX;
    
    for (int i=0; i < gSize; i++)
    {
        graphFile >> vertex;
        graphFile >> adjacentVertex;
        while (adjacentVertex != -999)
        {
            graphFile >> weight;
            weights[vertex][adjacentVertex] = weight;
            graphFile >> adjacentVertex;
        }
    }
}

void weightedGraphType::shortestPath(int vertex)
{
    for (int j = 0; j < gSize; j++)
        smallestWeight[j] = weights[vertex][j];

    bool *weightFound;
    weightFound = new bool[gSize];

    for (int j = 0; j < gSize; j++)
        weightFound[j] = false;

    weightFound[vertex] = true;
    smallestWeight[vertex] = 0;

    for (int i = 0; i < gSize - 1; i++)
    {
        double minWeight = DBL_MAX;
        int v;

        for (int j = 0; j < gSize; j++)
            if (!weightFound[j])
                if (smallestWeight[j] < minWeight)
                {
                    v = j;
                    minWeight = smallestWeight[v];
                }

        weightFound[v] = true;

        for (int j = 0; j < gSize; j++)
            if (!weightFound[j])
                if (minWeight + weights[v][j] < smallestWeight[j])
                    smallestWeight[j] = minWeight + weights[v][j];
    } //end for
} //end shortestPath

void weightedGraphType::printShortestDistance(int vertex)
{
    cout << "Source Vertex: " << vertex << endl;
    cout << "Shortest distance from source to each vertex."
         << endl;
    cout << "Vertex  Shortest_Distance" << endl;

    for (int j = 0; j < gSize; j++)
        cout << setw(4) << j << setw(12) << smallestWeight[j]
             << endl;
    cout << endl;
} //end printShortestDistance

    //Constructor
weightedGraphType::weightedGraphType(int size)
                  :graphType(size)
{
    weights = new double*[size];

    for (int i = 0; i < size; i++)
        weights[i] = new double[size];

    smallestWeight = new double[size];
}

    //Destructor
weightedGraphType::~weightedGraphType()
{
    for (int i = 0; i < gSize; i++)
       delete [] weights[i];

    delete [] weights;
    delete smallestWeight;
}

#endif
