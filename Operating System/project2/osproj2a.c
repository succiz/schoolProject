//includes
#include<unistd.h>
#include<sys/types.h>
#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>

//prototype for thread routine
void printMessage(void *ptr);
pthread_mutex_t mutex1=PTHREAD_MUTEX_INITIALIZER;
int counter=0;

int main(int argc, char* argv[])
{
    if(argc != 2)
       cout<<"usage:"<<argv[0];
    else  
        int threadNum=atoi(argv[1]);   //size of thread array
    
    pthread_t thread[threadNum];   //thread variables
    
    cout<<"How many threads do you want?"<<endl;
    cin threadNum;//???pass in number via command line = this or pass *argv[] from main()?

    //creat thread[threadNum]
    for(int i=0;i<threadNum;i++)
    {
        pthread_creat(&thread[i],NULL,(void*) &printMessage,(void*) &i);
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
void printMessage(void *ptr)
{
    cout<<"Thread "<<i<<endl;
    pthread_mutex_lock(&mutex1);
    counter++;
    pthread_mutex_unlock(&mutex1);
    
}
