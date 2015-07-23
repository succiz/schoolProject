//NAME:        Shuyi Zhao
//COURSE:      COSC 2437/5321
//Lab #9:      Sorting – Quick Sort
//ASSIGNED:    Mar  8, 2011
//DUE:         Mar 22, 2011  (after Spring Break)
//OBJECTIVE:   Create an array-based list and apply the quick sort algorithm 
//              to sort the list. Count the number of key compares and the 
//              number of record moves. 

#include <iostream>
#include <fstream>
#include <iomanip>
#include "arrayListType.h"

using namespace std;

//prototype
void printList(ofstream& ,arrayListType<int>& );

const int mySize = 110;

int main()
{
	//declare
	int myElement;
	int myCompare = 0;
	int myMove = 0;
	arrayListType<int> myList(mySize);
    ifstream myInFile;
    ofstream myOutFile;
	
	//read the record from lab9.dat to myList
	myInFile.open("lab9.dat");

	myInFile >> myElement;
	
	while(!myInFile.eof())
	{   
		myList.insert(myElement);

		myInFile >> myElement;		
	}

	myInFile.close();
	
	myOutFile.open("lab9.txt");
	
	myOutFile << "This is the original list:" << endl;

    printList(myOutFile,myList);

	//quick sort
	
	myList.quickSort(myCompare, myMove);

	myOutFile << endl << "This is the sorted list:" << endl;

    printList(myOutFile,myList);
    
	myOutFile << endl << "This list has "<< myCompare << " key compares." << endl;
	
	myOutFile << "This list has " << myMove << " key moves." << endl << endl;
	
	myOutFile.close();
	
	return 0;
}

//
void printList(ofstream& file, arrayListType<int>& list)
{
    file << "Index" << setw(5) << "Num" << endl;
    
    int element;
    
    for(int index = 0; index < list.listSize(); index++)
    
    {
        list.retrieveAt(index,element);
        
        file << setw(5) << index << setw(5) << element << endl;
    }
}
