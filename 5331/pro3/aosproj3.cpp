//****************************************************************
//
// Nhu Vo
// Advance Operationg Systems
// Programing Project 3: Producer - Consumer problem
// November 4, 2010
// Instructor: Dr. Michael C. Scherger
//
//****************************************************************

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <ctime>
using namespace std;

typedef int buffer_item;

/* data structure to get command line */
struct simArgs {
	int t;
	int l;
	int p;
	int f;
	int c;
	int d;
} simargs;

pthread_t tid;           /* thread ID */
pthread_attr_t attr;     /* set of thread attributes */
pthread_mutex_t mutex;   /* The mutex lock */
buffer_item *buffer;  	 /* the buffer */
int BUFFER_SIZE;	 /* number of buffer */
int counter = 0;         /* to count buffer */
int procounter = 0;      /* to count threads in producer */
int fprocounter = 0;     /* to count threads in faulty producer */
int concounter = 0;      /* to count threads in consumer */
int Profull = 0;         /* producer makes  buffer be  full */
int Fprofull =0;         /* faulty producer makes  buffer be  full */
int Totalfull = 0;       /* total buffer is full */
int Conempty1 = 0;       /* to count buffer empty */
int Conempty2 = 0;       /* to count buffer empty */
int Conempty = 0;        /* total buffer empty */
int *ProArray;		 /* store producer threads */
int *FproArray;		 /* store faulty producer threads */
int *ConArray;		 /* store cosumer threads */
int ProSize, FproSize, ConSize; /* number of threads */
bool simdone; /*to signal threads to quit */

void getargument(int Getargc, char * Getargv[]);      /* get command line arguments */
void initializeData();				      /* initialize mutex and buffer */
void *producer(void *param);                          /* the producer thread */
void *faultyproducer(void *param);		      /* the faulty producer thread */
void *consumer(void *param);                          /* the consumer thread */
int insert_item(buffer_item item);                    /* produce item */
int remove_item(buffer_item *item);                   /* get item */
bool isFibo(int value);                               /* check fibonacii */
int randFibo();                                       /* random fibo */
void printusage();
void printerror();

int main(int argc, char *argv[])
{
	int i;          /* Loop counter */
	simdone=1;      /* declare simdone = 1 */
	if (argc<11||argc>12)
	{
		printerror();
	}
	else
	{ 	
		getargument(argc, argv);         	/* get command line */
		pthread_t producer_id[simargs.p];	/* producer thread array */
		pthread_t faultyproducer_id[simargs.f]; /* faulty producer thread array */
		pthread_t consumer_id[simargs.c];	/* consumer thread arry */
		initializeData();              		/* Initialize the app */
		for(i = 0; i < simargs.p; i++)		/* Create the producer threads */
			pthread_create(&producer_id[i],&attr,producer,(void*) i);
		for(i = 0; i < simargs.f; i++)		 /* Create the thread */
			pthread_create(&faultyproducer_id[i],&attr,faultyproducer,(void*) i);
		for(i = 0; i < simargs.c; i++)		 /* Create the consumer threads */
			pthread_create(&consumer_id[i],&attr,consumer, (void*) i);
		sleep(simargs.t); 	/* Sleep for the specified amount of time in seconds */
		simdone=0;		/* main thread signals other threads to quit */
		/* join threads */
		for(i = 0; i < simargs.p; i++)
			pthread_join(producer_id[i], NULL);
		for(i = 0; i < simargs.f; i++)
			pthread_join(faultyproducer_id[i], NULL);
		for(i = 0; i < simargs.c; i++)
			pthread_join(consumer_id[i], NULL);
		if(simargs.d) {}
		printusage();
	}
	exit(0);

}

//*********************************************************************
//
// getargument Function
//
// This function get command line argument
//
// Reference Parameters
// Getargc        int
// Getargv[]      char
//
// Local Variables
// opt            int
//
//*********************************************************************

void getargument(int Getargc, char * Getargv[])
{
	int opt = 0; 
	simargs.d=0;
	while((opt = getopt ( Getargc , Getargv , "t:l:p:f:c:d" )) != EOF)
 	{
		switch( opt )
		{
			case 't': simargs.t = strtol ( optarg , (char **) NULL , 10 );
			break;
			case 'l': simargs.l = strtol ( optarg , (char **) NULL , 10 );
			break;
			case 'p': simargs.p = strtol ( optarg , (char **) NULL , 10 );
			break;
			case 'f': simargs.f = strtol ( optarg , (char **) NULL , 10 );
			break;
			case 'c': simargs.c = strtol ( optarg , (char **) NULL , 10 );
			break;
			case 'd': simargs.d++;
			break;
		}
	}

}

//*********************************************************************
//
// initializeData Function
//
// This function initializes the mutex, and the buffers
//
//*********************************************************************
 
void initializeData()
{
	pthread_mutex_init(&mutex, NULL);
	pthread_attr_init(&attr);
	BUFFER_SIZE=simargs.l;
	buffer = (buffer_item*) malloc(simargs.l*sizeof(buffer_item));
	ProSize = simargs.p;
	ProArray = (int*) malloc(simargs.p*sizeof(int));
	FproSize = simargs.f;
	FproArray = (int*) malloc(simargs.f*sizeof(int));
	ConSize = simargs.c;
	ConArray = (int*) malloc(simargs.c*sizeof(int));	
}

//*********************************************************************
//
// Producer Function
//
// This function generate a Fibonacci number. Producer will (try to)
// insert it into the buffer
// Reference Parameters
// param        void
//
// Local Variables
// item        buffer_item (int)
// takspro     int
//
//*********************************************************************

void *producer(void *param)
{
	buffer_item item;
	int taskpro;
	taskpro = (int)param;
	/* while simdone ==1, threads run */	
	while(simdone==1)
	{
		sleep(1);		    /* sleep in 1 second */
		item = randFibo(); 	    /* generate a random Fibonacci number */
		pthread_mutex_lock(&mutex); /* acquire the mutex lock */
		if(insert_item(item)==-1)   /* if buffer is full, threads display wating */
		{
	      		cout<<"Producer "<<taskpro<<" "<<" waiting "<<" : ("<<counter<<") : [";
	  		for (int j=0;j<counter;j++)
				cout<<buffer[j]<<" ";
			cout<< "]" <<"          *FULL*    "<<endl;
			
		}
		else /* if buffer empty, threads insert item */
		{
			ProArray[taskpro]++;  /* count each thread */
			procounter++;         /* number Non-Fautly produce item */
			cout<<"Producer "<<taskpro<<" "<<" writes "<<" "<<item<<" : ("<<counter<<") : [";
			for (int j=0;j<counter;j++)
 				cout<<buffer[j]<<" ";
			if(counter ==simargs.l){
				cout<< "]" <<"          *FULL*    "<<endl;
				Profull++;
			}
			else
				cout<< "]"<<endl;

		}
		pthread_mutex_unlock(&mutex); /* release the mutex lock */
		sched_yield();                /* when buffer is full, the thread, which is running, yield to another thread */
	} 
}

//*********************************************************************
//
// Faulty Producer Function
// This function generate a random number. Producer will (try to)
// insert it into the buffer
//
// Reference Parameters
// param        void
//
// Local Variables
// item        buffer_item (int)
// taksfpro     int
//
//*********************************************************************

void *faultyproducer(void *param)
 {	
	buffer_item item;
	int taskfpro;
	taskfpro = (int)param;
	while(simdone==1)
	 {
		sleep(1);		    /* sleep in 1 second */
		item = rand()%999+1; 	    /* generate a random number from 0 to 999*/
		pthread_mutex_lock(&mutex); /* acquire the mutex lock */
		if(insert_item(item)==-1)   /* if buffer is full, the thread display waiting */
		{
			cout<<"*Producer "<<taskfpro<<" "<<" waiting "<<" : ("<<counter<<") : [";
	   		for (int j=0;j<counter;j++)
				cout<<buffer[j]<<" ";cout<< "]" <<"          *FULL*    "<<endl;

		}
		else    /* if buffer is empty, the thread insert to buffer */
		{
			FproArray[taskfpro]++; /* count each thread */
			fprocounter++;         /* number Faulty thread produce item */
         		cout<<"*Producer "<<taskfpro<<" "<<" writes "<<" "<<item<<" : ("<<counter<<") : [";
		      	for (int j=0;j<counter;j++)
			cout<<buffer[j]<<" ";
			if(counter == simargs.l)
			{
				cout<< "]" <<"          *FULL*    "<<endl;
				Fprofull++;
			}
			else{
		        	cout<< "]" <<endl;
		  	}
	
      		}
		pthread_mutex_unlock(&mutex); /* release the mutex lock */
		sched_yield();                /* when buffer is full, the thread, which is runing, yield to another thread */
	}
}

//*********************************************************************
//
// Consumer Function
//
// This function alternates between (trying to)remove a number out of 
// the buffer and verified if it is part of the Fibonacci sequence
//
// Reference Parameters
// param        void
//
// Local Variables
// item        buffer_item (int)
// taksfpro     int
//
////*********************************************************************

void *consumer(void *param) 
{
	buffer_item item;
	int taskcon;
	taskcon = (int)param;
	/* while simdone ==1, consumer threads remove item in buffer */
	while(simdone==1) 
	 {
		sleep(1);
		pthread_mutex_lock(&mutex); /* acquire the mutex lock */
		if(remove_item(&item)==-1)  /* if buffer if empty, the thread display waiting */
		 {
			cout<<"Consumer "<<taskcon<<" "<< "waiting "<< " : ("<<counter<<") : [";
	      	cout<<"]"<<"    *EMPTY*    "<<endl;

		}
		else 
		{
			ConArray[taskcon]++; /* count each thread */
			concounter++;         /* number consumer remove items */
	
			if(isFibo(item)) /* if the number is Fibonacci, remove buffer */ 
			{	
				cout<<"Consumer "<<taskcon<<" "<< "read "<< item<<" : ("<<counter<<") : ["; 
	   			if(counter==0)
           			{
           				cout<<"]"<<"      *Empty*       "<<endl;
					Conempty1++;
    				}
				else
	  			{
           				for (int j=0;j<counter;j++)
	        	 			cout<<buffer[j]<<" ";
  	    				cout<<"]"<<endl;	
      			
	  			}
			}
			else /* if the number is not Fibonacci, remove buffer and display NOT FIBONCCI */
			{
				cout<<"Consumer "<<taskcon<<" "<< "reads "<< item<<" : ("<<counter<<") : [";
				if(counter==0)
				{
	  				cout<<"]"<<"             NOT FIBONACCI"<<"    *EMPTY*    "<<endl;
					Conempty2++; /* to count number of buffer is empty */

	  			}
				else
				{
	  				for (int j=0;j<counter;j++)
		  				 cout<<buffer[j]<<" ";
	      				cout<<"]"<<"          NOT FIBONACCI"<<endl;
				}
			}

		}
		pthread_mutex_unlock(&mutex); /* release the mutex lock */
		sched_yield();                /* when the buffer is empty, the thread is running yield to another thread */

	}
}

//*********************************************************************
//
// Insert_item Function
//
// This function add an item to the buffer. When the buffer is not full
// add the item and increment the counter. When buffer is full, return -1
//
// Return value
// int          0 if buffer is not full, -1 if buffer is full
//
// Reference Parameters
// item        buffer_item (int)
//
//*********************************************************************

int insert_item(buffer_item item)
{
	if(counter < BUFFER_SIZE) 	/* If the buffer is not full*/
	{
		buffer[counter] = item; /* add the item to buffer */
		counter++;              /* increase the counter */
		return 0;		/* return 0 */
	}
	else				/* if the buffer is full, return -1 */
		return -1;
}

//***************************************************************************
// Remove_item Function
//
// This function remove an item from the buffer. When the buffer is not empty
// remove the item and decrement the counter. When buffer is full, return -1
//
// Return value
// int          0 if buffer is not full, -1 if buffer is full
//
// Reference Parameters
// item        buffer_item (int)
//
//***************************************************************************

int remove_item(buffer_item *item)
 {

	/* When the buffer is not empty remove the item
	and decrement the counter */
	if(counter > 0) /* if the buffer is not empty */
	{
		*item = buffer[0];  /* remove the item */
		for (int i=0;i<counter;i++)   /* remove FIFO */
			buffer[i]=buffer[i+1];
		counter--;     /* decrease the item */
		return 0;      /* return 0 */
	}
	else    /* if the buffer is empty, return -1 */
		return -1;
}

//***************************************************************************
//
// isFibo Function
//
// This function verified if the number is part of the Fibonacci sequence.
//
// Return value
// bool          true/false if the number is Fibonacci
//
// Reference Parameters
// value         int
//
// Local values
// a            int
// b            int
// c            int
//
//***************************************************************************

bool isFibo(int value)
{
	int a = 1, b = 1;
	int c;
	while (value>=b)
	{
		c = a + b;
		a = b;
		b = c;
		if (value==b) 
			return true;
	}
	return false;
}

//***************************************************************************
//
// randFibo Function
//
// This function creates the random Fibonacci number
//
// Return value
// int          iSecret if the nunber is Fibonacci
//
// Local values
// iSecret            int
//
//***************************************************************************

int randFibo()
{
	int iSecret;
	srand ( time(NULL) );
	while (true)
	{
		iSecret=rand()%999+1;
		if (isFibo(iSecret)) 
		return iSecret;
	}
}

//***************************************************************************
//
// printusage Function
//
// This function print the arguments
//
// Local values
// i         int  
//
//***************************************************************************

void printusage()
{
	int i;
	cout<<endl;
	cout<<"PRODUCER / CONSUMER SIMUALTION COMPLETE "<<endl;
	cout<<"======================================= "<<endl;
	cout<<"Simulation Time:                    "<<simargs.t<<endl;
   	cout<<"Size of Buffer:                     "<<simargs.l<<endl;
   	cout<<"Number of Producer Threads:         "<<simargs.p<<endl;   
	cout<<"Number of Faulty Producer Threads:  "<<simargs.f<<endl;
   	cout<<"Number of Consumer Threads:         "<<simargs.c<<endl;
   	cout<<endl;
   	cout<<endl;
	cout<<"Total Number of Non-Faulty Items Produced:  "<<procounter<<endl;
	for( i =0; i<simargs.p;i++)
		cout<<"Thread "<<i<<" :                         "<<ProArray[i]<<endl;
	cout<<endl;
	cout<<"Total Number of Faulty Items Produced:      "<<fprocounter<<endl;
	for( i =0; i<simargs.f;i++)
		cout<<"Thread "<<i<<" :                         "<<FproArray[i]<<endl;
	cout<<endl;
	cout<<"Total Number of Items Consumed:             "<<concounter<<endl;
	for (i = 0; i<simargs.c; i++)
		cout<<"Thread "<<i<<" :                         "<<ConArray[i]<<endl;
	Totalfull = Profull + Fprofull;
	cout<<endl;
	cout<<"Total Number Of Times Buffer Was Full:      "<< Totalfull<<endl;
	Conempty = Conempty1 + Conempty2;
	cout<<"Total Number Of Times Buffer Was Empty:     "<<Conempty<<endl;

}

//***************************************************************************
//
// printerro Function
//
// This function print the error when missing arguments
//
//***************************************************************************

void printerror()
{
	cout<<endl;
	cout<< "INVALID COMMAND " <<endl;
	cout<<"The length of time the main thread is to sleep before terminating (-t)"<<endl;
	cout<<"The length of the buffer (-l) "<<endl;
	cout<<"The number of producer threads (-p) "<<endl;
	cout<<"The number of faulty producer threads (-f) "<<endl;
	cout<<"The number of consumer threads (-c) "<<endl;
	cout<<"An optional debug parameter (-d) "<<endl;
	cout<<"Exit program"<<endl;
	
}



