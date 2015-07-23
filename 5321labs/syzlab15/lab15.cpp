//NAME:        Shuyi Zhao 
//COURSE:      COSC 2437(optional)/5321(required)
//Lab #15:     Graph - Shortest Path (directed, weighted graph)
//ASSIGNED:    Apr 26, 2011
//DUE:         May  3, 2011
//OBJECTIVE:   Illustrate the shortest path algorithm

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "weightedGraph.h"

using namespace std;

void checkOpen(string& fileName);
bool openText(ifstream& myFile, string fileName);
void processGraph(ifstream& myFile, weightedGraphType& myGraph);

int main()
{
    string fileName;
    ifstream myFile;
    weightedGraphType myGraph(50);
    bool userWish=true;
    char wish;
    
    while(userWish)
    {        
        checkOpen(fileName);
        if(openText(myFile,fileName) == false)
            return 0;
        processGraph(myFile, myGraph);
        cout << "Do you want to open another data file?(Y/N)" << endl;
        cin >> wish;
        
        if(wish != 'Y' && wish != 'y')
        {
            userWish=false;
            cout << "You quit the program." << endl;
        }
        
        myFile.close();
        
    }
    system("pause");
    return 0;
}

//Purpose: check open function is to give a menu to user to determine open which file

//Pre-condition: user open program

//post-condition: open the file that user chose
void checkOpen(string& fileName)
{
    int num;
    
    cout << "Which data file you want to open?(1.wgraphSet1.dat,2.wgraphSet2.dat)" << endl;
    cin >> num;
    
    if(num == 1)
        fileName="wgraphSet1.dat";
    else if(num == 2)
        fileName="wgraphSet2.dat";
    else
    {
       cout << "Your choice dose not exist." << endl;  
       fileName="";
    }
}

//Purpose: open text function is to check if the file that user chose can be open

//Pre-condition: user chose a data file

//post-condition: the file sucessfully opened or failed open the program teminated
bool openText(ifstream& myFile, string fileName)
{
     myFile.open(fileName.c_str());
     if(myFile)
     {
         cout << endl << "Your data file successfully opened." << endl;
         return true;
     }
     else
     {
         cout << endl << "Error opening data file." << endl;
         cout << "The program will be terminated." << endl;
         return false;
     } 
}

//Purpose: process graph function is to display the graph and graph functions

//Pre-condition: data file successfully opened and graph object has been created

//post-condition: data file was writen into graph and sorted
void processGraph(ifstream& myFile, weightedGraphType& myGraph)
{
     myGraph.createWeightedGraph(myFile);
     cout << endl << "This is the graph:" << endl;
     myGraph.printGraph();
     cout << "This is depth first traversal:" << endl;
     myGraph.depthFirstTraversal();
     cout << endl << "This is breadth first traversal:" << endl;
     myGraph.breadthFirstTraversal();
     cout << endl << endl;
     myGraph.shortestPath(0);
     myGraph.printShortestDistance(0);
     cout << endl;
}
