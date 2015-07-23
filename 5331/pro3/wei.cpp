//********************************************************************
// osproj3.cpp
// Yuzhe Wei
// Operating Systems
// Programming Project #3: Producer-Consumer Problem with Faulty Threads
// Nov 1, 2010
// Instructor: Dr. Michael C. Scherger
//
//********************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <iostream>
#include <queue>
#include <assert.h>
#include "time.h"
#include <semaphore.h>

using namespace std;

//struct for argc argv
struct SimArgs
{
       int simulation_time;          //simulation time
       int buffer_length;            //buffer size
       int num_producer;             //the number of producer
       int num_faulty_producer;      //the number of faulty producer
       int num_consumer;             //the number of consumer
       bool debug;                   //debug for output
}aSimArg;



//gloable variable
bool simDone;                       //test if simulation is done
//semaphores
sem_t s;       //for mutual exclusion
sem_t n;       //number of item in the buffer
sem_t e;       //number of empty space           
sem_t a;

//Initialize buffer
queue <int> buffer;

int producerCount[10];           //array store counter for each producer
int fau_producerCount[10];       //array store counter for each faulty producer
int consumerCount[10];           //array store counter for each consumer
int bufferFullCount;              //counter count times of full buffer
int bufferEmptyCount;             //counter count times of empty buffer



void *producer_thd( void * threadid );
void *fal_prod_thd( void * threadid );
void *consumer_thd( void * threadid );
int produce_falty();
int produce_Fibo();
void consume_Fibo( int num );
void display_queue_content();
int isfib(int n);
void displayResult( SimArgs aSimArg );



int main (int argc , char * argv [])
{

     //local variable
     int opt;
     pthread_t *  producer;              //producer thread             
     pthread_t *  consumer;              //consumer thread
     pthread_t *  fau_producer;          //faulty producer thread
    
     //Initialize variable
    
     aSimArg.debug = false;                       //used for verbose messaging to screen
     
     simDone = false;                          //main thread sleeping
     bufferFullCount = 0;
     bufferEmptyCount = 0;
     
           
     //get command argument
     while( (opt = getopt ( argc , argv , "t: l: p: f: c: d" )) != -1 )
     {
          switch( opt )
          {
              case 't': aSimArg.simulation_time = atoi(optarg);//The length of time the main thread is to sleep before terminating
                  break;
              case 'l': aSimArg.buffer_length = atoi(optarg); //The length of the buffer
                  break;
              case 'p': aSimArg.num_producer = atoi(optarg);  //The number of producer threads
                  break;
              case 'f': aSimArg.num_faulty_producer = atoi(optarg);  //The number of faulty producer threads
                  break;
              case 'c': aSimArg.num_consumer = atoi(optarg);    //The number of consumer threads
                  break;
              case 'd': aSimArg.debug = true;                   //An optional debug parameter
                  break;        
          }
     }
     
     if(!aSimArg.debug)   //set default value
     {
          aSimArg.simulation_time = 30;
          aSimArg.buffer_length = 5;
          aSimArg.num_producer = 2;
          aSimArg.num_faulty_producer = 1;
          aSimArg.num_consumer = 2;
     }
     
     //initialize sem 
     sem_init(&s, 0, 1);
     sem_init(&n, 0, 0);
     sem_init(&e, 0, aSimArg.buffer_length);
     sem_init(&a, 0, 1);
     
     
     //initial each thread
     producer = (pthread_t *) malloc (aSimArg.num_producer* sizeof(pthread_t));
     fau_producer = (pthread_t *) malloc (aSimArg.num_faulty_producer* sizeof(pthread_t));
     consumer = (pthread_t *) malloc (aSimArg.num_consumer* sizeof(pthread_t));
    

     for (int i=0; i<aSimArg.num_producer; i++) 
         pthread_create(&producer[i],  NULL , producer_thd, (void *)i);
    
    //Create faulty producer thread(s)
    for (int i=0; i<aSimArg.num_faulty_producer; i++) 
         pthread_create(&fau_producer[i],  NULL , fal_prod_thd, (void *)i);
         
     //Create consumer thread(s) 
     for (int i=0; i<aSimArg.num_consumer; i++) 
         pthread_create(&consumer[i],  NULL , consumer_thd, (void *)i);
    
    //Sleep
    sleep(aSimArg.simulation_time);
    
    simDone = true;          //terminate each thread
    
    //Join Threads
    for (int i = 0; i< aSimArg.num_producer;  i++) 
        pthread_join( producer[i], NULL );
   
    for (int i=0; i<aSimArg.num_faulty_producer; i++) 
        pthread_join( fau_producer[i], NULL );
        
    for (int i=0; i<aSimArg.num_consumer; i++) 
        pthread_join( consumer[i], NULL );
         
    
    
    //Display Statistics    
    displayResult( aSimArg ); 
    
    return 0;
} 



//********************************************************************
//
// Producer Thread Function
//
// This function produce Fibonacci number into the buffer
//
// Return Value
// ------------
// none
//
// Parameters
// --------------------
// void *threadid        the index of producer thread array
//
// Local Variables
// ---------------
// int        num                integer hold the Fibonacci number
//*******************************************************************
void *producer_thd( void * threadid )
{
     //local variable
     int num;
     // initialize  counter
     producerCount[(int) threadid] = 0;
     
     while(!simDone)
     {
          num = produce_Fibo();
          
          
          
          if(!sem_trywait(&e))               //decrement one buffer space
          {
               if(!sem_trywait(&s))          //critical section start
               {
                    buffer.push( num );      //append
                                         
                    cout << "PRODUCER   " << (int) threadid << "   writes   "
                         << num << " (" << buffer.size() << ") "
                         << ": " <<" [ ";
                    display_queue_content();
                    cout << " ] ";
                   if( buffer.size() == aSimArg.buffer_length)
                    {
                         cout << "   *FULL*";
                         bufferFullCount++;            //increase full buffer counter
                    }
                    cout << endl;             
                    producerCount[(int) threadid]++;   //increment producer counter  
                    sem_post(&s);          //critical section end
                    sem_post(&n);          //increase the number in the buffer                                     
               }
               else
               {
                    if(!sem_trywait(&a))
                    {
                        cout << "PRODUCER   " << (int) threadid << "   waiting   "
                            << " (" << buffer.size() << ") "
                             << ": " <<" [ ";
                        display_queue_content();
                        cout << " ] \n";
                        sem_post(&a);
                    }
               }
         }
         else
         {
              if(!sem_trywait(&a))
              {
                 cout << "PRODUCER   " << (int) threadid << "   waiting   "
                     << " (" << buffer.size() << ") "
                         << ": " <<" [ ";
                display_queue_content();
                cout << " ] \n";
                if( buffer.size() == aSimArg.buffer_length)
                {
                     cout << "   *FULL*";
                     bufferFullCount++;            //increase full buffer counter
                }
                sem_post(&a);
              }
         }
     }
} 




//********************************************************************
//
// Faulty Producer Thread Function
//
// This function produce random number into buffer
//
// Return Value
// ------------
// None
//
// Value Parameters
// ----------------
// void *threadid        the index of producer thread array
//
// Local Variables
// ---------------
// num        int         the integer hold a random number
//
//*******************************************************************
void *fal_prod_thd( void * threadid )
{
     //local variable
     int num;
     // initialize counter 
     fau_producerCount[(int) threadid ] = 0;
     
     while(!simDone)
     {
          num = produce_falty();                 //get a random number
         
          if(!sem_trywait(&e))                   //decrement one buffer space
          {    
               if(!sem_trywait(&s))              //critical section start
               {
                    buffer.push(num);
                    cout << "FAULTY PRODUCER   " << (int) threadid 
                         << "   writes   " << num << " (" << buffer.size() << ") "
                         << ": " <<" [ ";
                    display_queue_content();
                    cout << " ] ";
                    if( buffer.size() == aSimArg.buffer_length)
                    {
                         cout << "   *FULL*";
                         bufferFullCount++;            //increase full buffer counter
                    }
                    cout << endl;                            
                    fau_producerCount[(int) threadid ]++;  //increase counter
                    sem_post(&s);              //critical section end
                    sem_post(&n);              //increase the number in the buffer
               }
               else
               {
                    if(!sem_trywait(&a))
                    {
                      cout << "FAULTY PRODUCER   " << (int) threadid 
                           << "   waiting   " << " (" << buffer.size() << ") "
                           << ": " <<" [ ";
                      display_queue_content();
                      cout << " ] \n";
                      sem_post(&a);
                    }
                   
               }
          }
          else  //full
          {
               if(!sem_trywait(&a))
               {
                 cout << "FAULTY PRODUCER   " << (int) threadid << "   waiting   "
                      << " (" << buffer.size() << ") "
                         << ": " <<" [ ";
                 display_queue_content();
                 cout << " ] \n";
                 if( buffer.size() == aSimArg.buffer_length)
                 {
                     cout << "   *FULL*";
                     bufferFullCount++;            //increase full buffer counter
                 }
                 sem_post(&a);
               }
          }
      }
}



//********************************************************************
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
// void *threadid        the index of producer thread array
//
// Local Variables
// ---------------
// num        int         the integer hold the first number in the buffer queue
//
//*******************************************************************
void *consumer_thd( void * threadid )
{
     //local variable
     int num;
     // initialize counter 
     consumerCount[(int) threadid ] =0;
     
     while(!simDone)
     {
          if(!sem_trywait(&n))        //sem decrease : one item in buffer is taken
          {               
               if(!sem_trywait(&s))   //critical section start
               {
                    num = buffer.front();       //for output
                    buffer.pop(); 
                    cout << "CONSUMER   " << (int) threadid 
                         << "   reads   " << num << " (" << buffer.size() << ") "
                         << ": " <<" [ ";
                    display_queue_content();
                    cout << " ] ";
                    if(buffer.size() == 0)
                    {
                         cout <<"   *EMPTY*";
                         bufferEmptyCount++;             //increase  counter
                    }
                                                                                        
                  
                    sem_post(&e);            //increase one buffer space
                    if(buffer.size() != 0)
                    {
                        
                         consume_Fibo( num ); 
                         consumerCount[(int) threadid ] ++;
                         
                    }   
                    cout << endl;
                    sem_post(&s);            //critical section end              
               } 
               else
               {
                    if(!sem_trywait(&a))
                    {
                      cout << "CONSUMER   " << (int) threadid 
                           << "   waiting   " << " (" << buffer.size() << ") "
                           << ": " <<" [ ";
                      display_queue_content();
                      cout << " ] ";
                      sem_post(&a);
                   }
               }                                               
          }
          else  //empty
          {       if(!sem_trywait(&a))
                    {
                        if(buffer.size() == 0)
                       {
                     cout << "CONSUMER   " << (int) threadid 
                           << "   waiting   " << " (" << buffer.size() << ") "
                           << ": " <<" [ ";
                      display_queue_content();
                      cout << " ]    *EMPTY*\n";
                      bufferEmptyCount++;             //increase  counter
                    }
                    sem_post(&a);
                 }
          }                    
     }     
}


//********************************************************************
//
// Produce Random Number Function
//
// This function is to produce a random number 
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
// a       int          the random number to return
//
//*******************************************************************
int produce_falty()
{
     int a;
     srand(time(0));
     a = rand()%30000;
     return a;
}


//********************************************************************
//
// Produce Random Number Function
//
// This function is to produce a Fibonacci number 
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
// a       int          the random number then set to the Fibonacci number
//
//*******************************************************************
int produce_Fibo()
{
     int a;
     srand(time(0));
     a = rand()%30000;     
     
     while(!isfib(a)) 
     {
         a = rand()%30000; 
        
     }
     return a;
}


//********************************************************************
//
// Consume Fibonacci Number Function
//
// This function is to indicate if the number is Fibonacc number
//
// Return Value
// ------------
// None                    
//
// Value Parameters
// ----------------
// num      int          a integer need to be tested
//
// Local Variables
// ---------------
// None
//
//*******************************************************************
void consume_Fibo( int num )
{
     num = isfib(num);
     if (!num && aSimArg.debug )
         cout <<"*NOT FIBONACCI*    ";
}


//********************************************************************
//
// Traversal Buffer Queue Function
//
// This function is to traverse each item in the buffer queue
//
// Return Value
// ------------
// None                    
//
// Value Parameters
// ----------------
// none
//
// Local Variables
// ---------------
// tempQueue           queue             copy the buffer queue 
//
//*******************************************************************
void display_queue_content()
{
     queue <int> tempQueue;
     while (!buffer.empty()) 
     { 
          if( aSimArg.debug )
               cout << buffer.front() <<"   "; //display each items in the buffer queue
          tempQueue.push(buffer.front());//copy buffer to a temp queue 
          buffer.pop(); 
     }
     
     while (!tempQueue.empty())     //restore items to buffer
     { 
         buffer.push(tempQueue.front());//copy buffer to a temp queue 
         tempQueue.pop(); 
     }
}
     
     
     
//********************************************************************
//
// Test Fibonacci Number Function
//
// This function is to test is the number is a Fibonacci Number
//
// Return Value
// ------------
// int             if is Fibonacci Number  return a integer
//                 otherwise, return 0;                   
//
// Value Parameters
// ----------------
// n         int   the number need to be tested
//
// Local Variables
// ---------------
// a         integer array        if a[0]+ a[i]> n  , false
// i         integer 
// j         integer 
//*******************************************************************
int isfib(int n) 
{ 
     int a[2]={1,1}; 
     int i=0,j=3; 
     if(n==1) 
         return 1; 
     if(n==2) 
         return 3; 
     while((a[0]+ a[1]) <n) 
     { 
          a[i]=a[0] +a[1]; 
          i=1-i; 
          j++; 
     } 
     if((a[0]+ a[1])==n) 
         return j; 
     else 
         return 0; 
} 


//********************************************************************
//
// Display Statistics  Function
//
// This function is to display the statistics 
//
// Return Value
// ------------
// None
//             
// Value Parameters
// ----------------
// aSimArg        SimArgs
//
// Local Variables
// ---------------
// totalProduce            integer             sum of total produce number
// totalFauProduce         integer             sum of total faulty produce number
// totalConsume            integer             sum of total consume number
//*******************************************************************
void displayResult( SimArgs aSimArg )
{
     int totalProduce = 0;
     int totalFauProduce = 0;
     int totalConsume = 0;
     cout << "PRODUCER / CONSUMER SIMULATION COMPLETE\n"
          << "=======================================\n"
          << "Simulation Time:                    " << aSimArg.simulation_time << endl
          << "Size of Buffer:                     " << aSimArg.buffer_length << endl
          << "Number of Producer Threads:         " << aSimArg.num_producer << endl
          << "Number of Faulty Producer Threads:  " << aSimArg.num_faulty_producer << endl
          << "Number of Consumer Threads:         " << aSimArg.num_consumer << endl << endl << endl;
     
     for(int i =0; i < aSimArg.num_producer; i++ )
         totalProduce += producerCount[i];
         
     for(int i =0; i < aSimArg.num_faulty_producer; i++ )
         totalFauProduce += fau_producerCount[i];
     
     for(int i =0; i < aSimArg.num_consumer; i++ )
         totalConsume += consumerCount[i];
             
     cout << "Total Number of Non-Faulty Items Produced:              " << totalProduce << endl;
     for(int i =0; i < aSimArg.num_producer; i++ )
         cout << "  Thread "<< i << ":" << "                    " << producerCount[i] << endl;  
             
     cout << "Total Number of Faulty Items Produced:                  " << totalFauProduce << endl; 
     for(int i =0; i < aSimArg.num_faulty_producer; i++ )
         cout << "  Thread "<< i << ":" << "                    " << fau_producerCount[i] << endl;
                      
     cout << "Total Number of Items Consumed:                   " << totalConsume << endl; 
     for(int i =0; i < aSimArg.num_consumer; i++ )
         cout << "  Thread "<< i << ":" << "                    " << consumerCount[i] << endl;

     cout << "Total Number Of Times Buffer Was Full:            " << bufferFullCount << endl; 
     cout << "Total Number Of Times Buffer Was Empty:           " << bufferEmptyCount << endl;
        
}
     
     
     
