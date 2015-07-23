//NAME:        Shuyi Zhao
//COURSE:      COSC 2437/5321
//Lab #14:     Graph Traversals
//ASSIGNED:    Apr 19, 2011
//DUE:         Apr 26, 2011
//OBJECTIVE:   Illustrate the depth first traversal and the breadth first 
//             traversal for three graphs.


#include <iostream>
#include <fstream>
#include <iomanip>
#include "graphType.h"

using namespace std;

int main()
{
    char fileName[50];
    ifstream myFile;
    graphType myGraph(50);
    bool userWish=true;
    char wish;
    
    while(userWish)
    {
        cout << "Which data file you want to open?(dataSet1.dat:dataSet2.dat:dataSet3.dat)" << endl;
        cin >> fileName;
        
        myFile.open(fileName);
        if(myFile)
           cout << endl << "Your data file successfully opened." << endl;
        else
        {
           cout << endl << "Error opening data file." << endl;
           cout << "The program will be terminated." << endl;
           return 0;
        } 
        
        myGraph.creatGraph(myFile);
        cout << endl << "This is the graph:" << endl;
        myGraph.printGraph();
        cout << "This is depth first traversal:" << endl;
        myGraph.depthFirstTraversal();
        cout << endl << "This is breadth first traversal:" << endl;
        myGraph.breadthFirstTraversal();
        cout << endl << endl;
        
        cout << "Do you want to open another data file?(Y/N)" << endl;
        cin >> wish;
        
        if(wish != 'Y' && wish != 'y')
        {
            userWish=false;
            cout << "You quit the program." << endl;
        }
        
        myFile.close();
        
    }

    return 0;
}
