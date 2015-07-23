//NAME:        Shuyi Zhao
//COURSE:      COSC 5321
//Lab #10:     Sorting ¨C Heap Sort
//ASSIGNED:    Mar 22, 2011
//DUE:         Mar 29, 2011
//OBJECTIVE:   Add to the previous lab by creating a second array-based list 
//             and applying the heap sort algorithm to sort the list. Count 
//             the number of key compares and the number of record moves. 
#include <iostream>
#include <fstream>
#include <iomanip>
#include "arrayListType.h"

using namespace std;

//prototype
template <class elemType>
void printList(ofstream& , arrayListType<elemType>& );

const int mySize = 110;

int main()
{
	//declare variables
	int myElement; //element in myList
	int myCompare1 = 0;//compare key for quick sort
	int myMove1 = 0;//move key for quick sort
	int myCompare2 = 0;//compare key for heap sort
	int myMove2 = 0;//move key for heap sort
	arrayListType<int> myList(mySize);//unsorted list
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
	
	//open output file ready to write
	myOutFile.open("lab10.txt");
	
	//write quick original list
	myOutFile << "This is the original list:" << endl;

    printList(myOutFile,myList);

	//quick sort
	arrayListType<int> myList1;
	
	myList1 = myList;
	
	myList1.quickSort(myCompare1, myMove1);

	myOutFile << endl << "This is the quick sorted list:" << endl;

    printList(myOutFile,myList1);
    
	//heap sort
	arrayListType<int> myList2;
	
	myList2 = myList;
	
	myList2.heapSort(myCompare2, myMove2);

	myOutFile << endl << "This is the heap sorted list:" << endl;

    printList(myOutFile,myList2);
    
    //write compare key and move key table
    myOutFile << endl << setw(22) << "Compare Key" << setw(10) << "Move Key" << endl << endl;
    
   	myOutFile << setw(10) << "Quick Sort "<< setw(11) << myCompare1 
              << setw(10) <<myMove1 << endl << endl;
    
    myOutFile << setw(10) << "Heap Sort  "<< setw(11) << myCompare2 
              << setw(10) <<myMove2 << endl;
	
    
	myOutFile.close();
	//system("pause");
	return 0;
}

//Purpose: printList function is to write sorted(quick and heap) list into lab10.txt

//Pre-condition: list has been sorted by quick or heap sort

//post-condition: sorted list was writen into lab10.txt file
template <class elemType>
void printList(ofstream& file, arrayListType<elemType>& list)
{
    file << "Index" << setw(5) << "Num" << endl;
    
    int element;
    
    for(int index = 0; index < list.listSize(); index++)
    
    {
        list.retrieveAt(index,element);
        
        file << setw(5) << index << setw(5) << element << endl;
    }
}
