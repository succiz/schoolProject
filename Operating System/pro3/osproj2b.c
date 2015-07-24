//*********************************************************
//
// Shuyi Zhao
// Operating Systems
// Project #2: Simple Pthreads and MPI Programs
//
//*********************************************************

//includes
#include<iostream>
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<math.h>

using namespace std;

//prototype for thread routine
bool prime;
void *printMessage(void *ptr);
void *function1(void *ptr);
void isPrime(int);
pthread_mutex_t mutex1=PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char *argv[])
{
	
    pthread_t thread1, thread2;   //thread variables
	int *number = new int;
	int integer;
    
	if(argc != 2)
	{
	   cout<<"The number of arguments is not correct" << endl;
	   return 1;
    }
		//
	integer = atoi(argv[1]);
	*number = integer;
    
    //creat thread1 and thread2
    pthread_create(&thread1,NULL,function1,(void*)number);	
    pthread_create(&thread2,NULL,printMessage,(void*)number);
 
    //main block waits for all threads to terminate
    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

	delete number;

    exit(0);
}

// function1 is used to run isPrime function
void *function1(void *ptr)
{
	int *myNumber =(int*)ptr;

	pthread_mutex_lock(&mutex1);

	isPrime(*myNumber);
	
	pthread_mutex_unlock(&mutex1);
}
//printMessage function is used as a start routine for the treads used.
void *printMessage(void *ptr)
{
	int *myNum=(int*)ptr;
	pthread_mutex_lock(&mutex1);
    if(prime == false)
		cout<<"What you entered:"<<*myNum<<" is not a prime"<<endl;
	else
		cout << "What you entered: " << *myNum << " is a prime" << endl;
    pthread_mutex_unlock(&mutex1);
    
}

//isPrime function is used to determine if the integer passed in is a prime number
void isPrime(int a)
{
	prime = true;
	for(int i=2;i<a;i++)
	{
		if(a%i==0)
		{
			prime=false;
			break;
		}
	}
}
