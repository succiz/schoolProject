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
using namespace std;

//prototype for thread routine
void *printMessage(void *ptr);
pthread_mutex_t mutex1=PTHREAD_MUTEX_INITIALIZER;
int counter=0;

int main(int argc, char* argv[])
{   //declare variables
	int threadNum;


	//get the agrgument from command line
    if(argc != 2)
	{
		cout<<"usage:"<<argv[0]<<endl;
		cout<<"You do not give the number of thread."<<endl;
		exit(-1);
	}
    else  
	{
		threadNum=atoi(argv[1]);   //size of thread array
	}
    
    pthread_t thread[threadNum];   //thread variables
	int threadID[threadNum];
    
    //creat thread[threadNum]
    for(int i=0;i<threadNum;i++)
    {
        threadID[i]=i;
        pthread_create(&thread[i],NULL,printMessage,(void*)&threadID[i]);
    }
    
    //main block waits for all threads to terminate
    for(int j=0;j<threadNum;j++)
    {
        pthread_join(thread[j],NULL);
    }
    
    //wait till all thread are complete before main continue
    cout<<"Counter value:"<<counter<<endl;
    
    exit(0);
}

//printMessage function is used as a start routine for the treads used.
void *printMessage(void *ptr)
{
	int *myNumber=(int*)ptr;
    cout<<"Thread "<<*myNumber<<endl;
    pthread_mutex_lock(&mutex1);
    counter++;
    pthread_mutex_unlock(&mutex1);
    
}
