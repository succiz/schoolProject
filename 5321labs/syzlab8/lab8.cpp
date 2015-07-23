//NAME:       Shuyi Zhao
//COURSE:     COSC 2437/5321
//Lab #8:     Hashing
//ASSIGNED:   Mar  1, 2011
//DUE:        Mar  8, 2011
//OBJECTIVE:  Create a Hash Table then search for values in the table.
//            Count the number of probes and display the probe sequence.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <math.h>
#include "hashT.h"
#include "linkedQueue.h"

using namespace std;

//prototype
int hashFunction(int,int);

//global constant
const int mySize=39;

int main()
{
    //declare variables
	int myInsertKey;
	int mySrch;
	int pCount;
	int hashIndex;
	float loadFactor;
	bool found;
	linkedQueueType<int> probeSequence;
	hashT<int> myHash(mySize);
	ifstream myInFile;
	ifstream mySrchFile;

    //open input file
	myInFile.open("lab8.dat");
	myInFile>>myInsertKey;
	
    //insert element from input file to hash table
	while(!myInFile.eof())
	{   
		hashIndex = hashFunction(myInsertKey,mySize);
		myHash.insert(hashIndex,myInsertKey);
		myInFile >> myInsertKey;
	}

	//print out hash table
	cout<<"Here is the Hash Table:"<<endl;
    myHash.print();
    cout<<endl<<"***********************************************"<<endl;
    loadFactor = static_cast<float>(myHash.getLength()) / mySize;
    cout<<"The load factor is: "<<loadFactor<<endl;
    cout<<"***********************************************"<<endl<<endl;
    
    myInFile.close();
    
    //open input search file
    mySrchFile.open("lab8srch.dat");
    mySrchFile>>mySrch;
    
    cout<<"Here is the search result:"<<endl;
    
    //search every element from file in hash table
    while(!mySrchFile.eof())
    {
        //calculate the key
        hashIndex=hashFunction(mySrch,mySize);
        
        //search the element in hash table
        myHash.search(hashIndex,mySrch,found,pCount,probeSequence);
        
        //show if the element in hash table
        if(found == true)
            cout<<endl<<mySrch<<" was found."<<endl;
        else
            cout<<endl<<mySrch<<" was not found."<<endl;
            
        cout<<setw(6)<<"Number"<<setw(8)<<"Compare"<<"  probe Sequence"<<endl;  
        
        //display element and the number of key compares  
        cout<< setw(3) << mySrch << setw(8) << pCount << "     " ;
        
        //diaplay probe sequence
        for(int i=0;i<pCount;i++)
        {
            cout << probeSequence.front() << " " ;
            probeSequence.deleteQueue();
        }
        
        cout<<endl;
        
        mySrchFile>>mySrch;
    }
    
    mySrchFile.close();
    
    return 0;
}

//hash function to get address from a key
int hashFunction(int myInsertKey, int mySize)
{
     return (myInsertKey%mySize);
}
