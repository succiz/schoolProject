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
#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <queue>
#include <sstream>

using namespace std;


//Global variables
int bufferSize = 5;
sem_t mutex;
sem_t empty;
sem_t full;
int counter;//counter for items
int pCounter = 1;
int cCounter = 1;
int item1;
int item2;
int itemCounter=0;
int fullTimes = 0;       /* producer makes  buffer is  full */
int emptyTimes = 0;        /* consumer makes buffer is empty */
int pArray[10];		 /* store producer threads */
int cArray[10];		 /* store cosumer threads */
queue<int> myBuffer;

struct Arg
{
    int n;
    int l;
    int p;
    int c;
}myArg;

int inBuffer(int& );
int outBuffer(int& );
void *producer(void* ptr);
void *consumer(void* ptr);
void primeFinder(int& );
bool isPrime(int );
void printMessage();



int main(int argc, char* argv[])
{

			
	if(argc == 9)
    {
       myArg.n = atoi(argv[2]);
	   myArg.l = atoi(argv[4]);
	   myArg.p = atoi(argv[6]);
	   myArg.c = atoi(argv[8]); 
    }
    else
        cout<<argc<<"There are some errors in your arguments.\n";
        
	sem_init(&mutex, 0, 1);
	sem_init(&empty, 0, myArg.l);
	sem_init(&full, 0, 0);
        
    counter = myArg.n * myArg.p;
    
	pthread_t pThread[myArg.p];   //thread variables
	int pID[myArg.p];
	for(int i=0;i<myArg.p;i++)
    {
            
        pID[i]=i;
        pthread_create(&pThread[i],NULL,producer,(void*)&pID[i]);
    }

	pthread_t cThread[myArg.c];   //thread variables
	int cID[myArg.c];
	for(int j=0;j<myArg.c;j++)
    {
        cID[j]=j;
        pthread_create(&cThread[j],NULL,consumer,(void*)&cID[j]);
    }

	//main block waits for producer threads to terminate
    for(int i=0;i<myArg.p;i++)
    {
        pthread_join(pThread[i],NULL);
    }

	//main block waits for consumer threads to terminate
    for(int j=0;j<myArg.c;j++)
    {
        pthread_join(cThread[j],NULL);
    }

	printMessage();

	exit(0);
}
    
//********************************************************************
//
// In Buffer Queue Function
//
// This function is to put each item in the buffer queue
//
// Return Value
// ------------
// int                   
//
// Value Parameters
// ----------------
// item1    int
//
// Local Variables
// ---------------
// NONE
//
//*******************************************************************
int inBuffer(int& item1)
{
     if(itemCounter < bufferSize)
	 {
	     myBuffer.push(item1);
	     itemCounter++;
		 return 0;
	 }
	 else
		 return -1;
}

//********************************************************************
//
// Out Buffer Queue Function
//
// This function is to take each item out the buffer queue
//
// Return Value
// ------------
// int                   
//
// Value Parameters
// ----------------
// item2    int
//
// Local Variables
// ---------------
// NONE
//
//*******************************************************************
int outBuffer(int& item2)
{
    if(itemCounter > 0) 
	{  
        item2 = myBuffer.front();
	 	myBuffer.pop();		
		itemCounter--;     
		return 0;      
	}
	else   
		return -1; 
}

//********************************************************************
//
// Produce Random Prime Number Function
//
// This function is to produce a random prime number 
//
// Return Value
// ------------
// int                    
//
// Value Parameters
// ----------------
// None
//
// Local Variables
// ---------------
// i       int          the random prime number to return
//
//*******************************************************************
void primeFinder(int& i)//declare int i in main.
{
    do
	{    
		i = random() % 10000;
	}
	while(!isPrime(i));
}

//********************************************************************
//
// Consume Prime Number Function
//
// This function is to indicate if the number is prime number
//
// Return Value
// ------------
// bool                    
//
// Value Parameters
// ----------------
// q      int          a integer need to be tested
//
// Local Variables
// ---------------
// p      int
//
//*******************************************************************
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

////********************************************************************
//
// Producer Thread Function
//
// This function produce prime number into the buffer
//
// Return Value
// ------------
// none
//
// Parameters
// --------------------
// void *pID[i]        the index of producer thread array
//
// Local Variables
// ---------------
// int        item2                integer hold the prime number
//*******************************************************************
void *producer(void* ptr)
{
	int *myNumber=(int*)ptr;
	pArray[*myNumber]=0;

    while(pArray[*myNumber] < myArg.n)
    {
        sem_wait(&empty);
        sem_wait(&mutex);
			
        primeFinder(item1);
        if(isPrime(item1))
        {
            if(inBuffer(item1) == -1)   
            {
            
 		        cout<<"Producer "<<*myNumber<<" "<<" waiting "<<" : ("<<itemCounter<<") : [";
     		    queue<int> newQueue;
                newQueue = myBuffer;
 		        for (int j=0; j<myBuffer.size(); j++)
                {
			  	    cout << newQueue.front()<< " ";
		            newQueue.pop();
		        }
			    cout<< "]" <<"      *FULL*    \n";
			
            }//end if(inBuffer(item1))
   	       else /* if buffer empty, threads insert item */
            {
  	            pArray[*myNumber]++;  /* count each thread  */
  	        
		        cout<<"(Producer "<<*myNumber<<" writes "<<" "<<pArray[*myNumber]<<"/"<<myArg.n<<" "<<item1<<") : ("<<itemCounter<<") : [";
		        
		        queue<int> newQueue;
                newQueue = myBuffer;
                for (int j=0; j<itemCounter; j++)
                {
  	               cout << newQueue.front()<< " ";
                   newQueue.pop();
                }
		        if(itemCounter == myArg.l)
                {
			        cout<< "]" <<"          *FULL*    \n";
			        fullTimes++;
		        }
		        else
			       cout<< "]\n"<<endl;
            }//end else
        }//end if(isPrime())
        pCounter++;

		sem_post(&mutex);
		sem_post(&full);
    }//end while()	

}

////********************************************************************
//
// Consumer Thread Function
//
// This function is to consume one item in the buffer 
//
// Return Value
// ------------
// None
//
// Value Parameters
// ----------------
// void *cID[i]        the index of producer thread array
//
// Local Variables
// ---------------
//int    item2         the integer hold the first number in the buffer queue
//
//*******************************************************************
void *consumer(void* ptr)
{
    int *myNumber=(int*)ptr;
    cArray[*myNumber]=0;
    
   	while(cCounter < counter)
	{
		sem_wait(&full);
		sem_wait(&mutex);
        
		if(outBuffer(item2) == -1)  /* if buffer is empty, the thread displays waiting */
		{
		    cout<<"(Consumer "<<*myNumber<<" "<<" waiting "<<" : ("<<itemCounter<<") : [";
			cout<< "]" <<"          *EMPTY*    \n";
			
		}
		else /* if buffer empty, threads insert item */
		{
            cArray[*myNumber]++;
            cout <<"(Consumer "<<*myNumber<<" "<<" reads   "<<cCounter<<"   "<<item2<<") : ("<<itemCounter<<") : [";
			
		    queue<int> newQueue;
            newQueue = myBuffer;
            for (int j=0; j<itemCounter; j++)
            {
  	            cout << newQueue.front()<< " ";
                newQueue.pop();
            }

			if(itemCounter == 0)
            {
				cout << "]" <<"          *empty*    \n";
				emptyTimes++;
			}
			else
				cout<< "]\n";
				
		 }
        cCounter++;
		sem_post(&mutex);
		sem_post(&empty);
		
		if(!isPrime(item2))
			cout<<"The excuted item is not a prime.\n";
      }
}

//***************************************************************************
//
// printusage Function
//
// This function prints the arguments
//
// Local values
// i         int  
//
//***************************************************************************

void printMessage()
{
	int i;
	cout<<endl;
	cout<<"PRODUCER / CONSUMER SIMUALTION COMPLETE "<<endl;
	cout<<"======================================= "<<endl;
	cout<<"Number of Item Per Producer Thread:              "<<myArg.n<<endl;
   	cout<<"Size of Buffer:                                  "<<myArg.l<<endl;
   	cout<<"Number of Producer Threads:                      "<<myArg.p<<endl;   
   	cout<<"Number of Consumer Threads:                      "<<myArg.c<<endl;
   	cout<<"\n\n";

	cout<<"Total Number of Items Consumed:             "<< cCounter-1 << endl;
	for (i = 0; i<myArg.c; i++)
		cout<<"Thread "<<i<<" :                         "<< cArray[i] <<endl;
	
	cout<<"Total Number Of Times Buffer Was Full:      "<< fullTimes <<endl;

	cout<<"Total Number Of Times Buffer Was Empty:     "<< emptyTimes <<endl;

}
