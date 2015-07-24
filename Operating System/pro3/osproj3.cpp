//********************************************************************
// osproj3.cpp
// Shuyi Zhao 
// Operating Systems
// Programming Project #3: Producer-Consumer Problem 
// Mar 28, 2011
// Instructor: Dr. Michael C. Scherger
//
//********************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
using namespace std;


//Global variables
int bufferSize = 5;
sem_t mutex;
sem_t empty;
sem_t full;
int counter;//counter for items

void getArg(char*, int);
void inBuffer(int& , queue<int>& );
void outBuffer(int& , queue<int>& );
void *producer(sem_t , set_t , sem_t , queue<int>&, int& , int );
void *consumer(sem_t , set_t , sem_t , queue<int> ,int , int ,);

struct Arg
{
    int n;
    int l;
    int p;
    int c;
}myArg;

int main(int argc, char* argv[])
{
	int pCounter = 0;
	int cCounter = 0;
	int item;

	sem_init(&mutex, 0, 1);
	sem_init(&empty, 0, 10);
	sem_init(&full, 0, 0);
	queue<int> myBuffer;
	
	getArg(argv[], argc);
    counter = n * P;

	pthread_t pThread[p];   //thread variables
	int pID[p];
	for(int i=0;i<p;i++)
    {
        pID[i]=i;
        pthread_create(&pThread[i],NULL,producer,(void*)&pID[i]);
    }

	pthread_t cThread[c];   //thread variables
	int cID[c];
	for(int j=0;j<c;j++)
    {
        cID[j]=j;
        pthread_create(&cThread[j],NULL,consumer,(void*)&cID[c]);
    }

	//main block waits for producer threads to terminate
    for(int i=0;i<p;i++)
    {
        pthread_join(pthread[i],NULL);
    }

	//main block waits for consumer threads to terminate
    for(int j=0;j<c;j++)
    {
        pthread_join(cthread[j],NULL);
    }

	printMessage();

	exit(0);
}

void gatArg(char* argv[], int argc)//decide have been end? argc?
{
   if(argc <= 8)
   {
       myArg.n = atoi(argv[1]);
	   myArg.l = atoi(argv[3]);
	   myArg.p = atoi(argv[5]);
	   myArg.c = atoi(argv[7]); 
    }
    else
        cout<<"There are some errors in your arguments.";
}
    

void inBuffer(int& item, queue<int>& myBuffer)
{
     if(counter < bufferSize)
	 {
	     myQueue.push(item);
	     pCounter++;
		 return 0;
	 }
	 else
		 return -1;
}

void outBuffer(int& item, queue<int>& myBuffer)//item?
{
    if(counter > 0) 
	{  
		while(!myBuffer.empty())
		{
		    item = myBuffer.front();
			myQueue.pop();
        }			
		cCounter++;     
		return 0;      
	}
	else   
		return -1; 
}


primeFinder(int& i)//declare int i in main.
{
    do
	{    
		do
			i = ramdom();
		while(i > 10000 || i<0)
		
		isPrime(i);
	}
	while(!isPrime(i))

}

bool isPrime(int q)  //
{
    if (q < 2)
        return false;
    else if (q == 2)
        return true;
    for (int p = 2; p <= sqrt(q); p++)
    {
        if (q % p == 0)
        return false;
    }
    return true;
}

//
void *producer(sem_t mutex, set_t full, sem_t empty, queue<int>& myBuffer, int& pID, int pCounter)//mutex lock?
{
	do
	{
	    int item;
		primeFinder(item); 

		if(isPrime(item))
		{
			wait(empty);
			wait(mutex);
			
			inBuffer(item, myBuffer);
			
			cout<<"(Producer " << pID << " " << " writes " << pCounter << "/" << n << " " << item << " ): ("<< myBuffer.size() << ") : [";
			
			//output the item in myQueue
			queue<int> newQueue;
			newQueue = myBuffer;
	  		for (int j=0;j<myBuffer.size();j++)
			{
				cout << newQueue.front()<< " ";
				newQueue.pop();
			}
			cout<< "]" <<"          *FULL*   \n";
			signal(mutex);
			signal(full);
		}
		else 
			cout << "Item is not a prime!\n";
	}
    while(true);
}

//
void *consumer(sem_t mutex, set_t full, sem_t empty, queue<int> myBuffer,int counter, int cID, int cCounter)
{
	while(cCounter != counter)
	{
		wait(full);
		wait(mutex);
		
		int item;
        outBuffer(item, myBuffer);
        
		if(outBuffer(item, myBuffer) == -1)  /* if buffer is empty, the thread displays waiting */
	    {
			cout<<"Consumer " << cID << " " << "waiting " << " : (" << counter << ") : [";
	      	cout<<"]"<<"    *EMPTY*    "<<endl;

		}
		else 
		{
			cout<<"Consumer " << cID << " " << "read " << item <<" : ("<< counter << ") : [" ; 
			
            queue<int> newQueue;
			newQueue = myBuffer;
	  		for (int j=0; j<myBuffer.size(); j++)
			{
				cout << newQueue.front()<< " ";
				newQueue.pop();
			}
			cout<<" ] \n";
		}
     }
			
		signal(mutex);
		signal(empty);
		
		if(!isPrime(i))
			cout<<"The excuted item is not a prime.\n";
	}
	while(true)
}
