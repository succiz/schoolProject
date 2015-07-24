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

int main()
{
    pthread_t thread1, thread2;   //thread variables
    boolean isPrime;
    
    //creat thread1 and thread2
    pthread_creat(&thread1,NULL,(void*) &printMessage,(void*) &i);
    pthread_creat(&thread2,NULL,(void*) &printMessage,(void*) &i);
    
    //main block waits for all threads to terminate
        pthread_join(thread1,NULL);
        pthread_join(thread2,NULL);

    
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
