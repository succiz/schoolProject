/**************************************************************************************************************************
 * Programmer: Shuyi Zhao
 * Advanced Operating Systems
 * Programming Project #3: Ricart and Agrawala�s Distributed Mutual Exclusion Algorithm
 * Due date: Nov 21, 2012
 * Instructor: Dr. Ajay K. Katangur
 **************************************************************************************************************************
 * Program Description: Write a C or C++ program to implement the Ricart and Agrawal�s algorithm using MPI.
 *                      1. Each process has a unique rank numbered from 0 to (N - 1). Each process keeps a 
 *                         Lamport�s logical clock. Messages requesting entry into the critical section are 
 *                         of the form (Pi:Ti), where Pi is the processes rank and Ti is the sender�s timestamp 
 *                         updated according to Lamport�s logical clock rules. In the critical section a process 
 *                         sleeps for 1 second and then updates an integer variable, whose initial value is set to 0.
 *                      2. Each process records its state of being outside the critical section (RELEASED), 
 *                         requesting entry (REQUESTED) or being in the critical section (GRANTED). 
 *                         A process can randomly request entry to critical section after waiting for some time, 
 *                         if it has not already requested one or is not currently holding the critical section.
***************************************************************************************************************************/

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RELEASED   10
#define REQUESTED   20
#define GRANTED   30
#define m_size   2
#define recv_size   8
#define REQ_TAG   0
#define REP_TAG   1
#define ON   1 /* A processor is in the critical section */
#define OFF   0 /* No processor is in the critical section */

void enter_cs(int rank, int size, int *timestamp, MPI_Request* requests, int *state_status, int *cs_status, int *cs_counter, int *req_counter, int req_message[2]);
void recv_req(int rank, int size, int req_message[2], int rep_message[2], int* req_counter, int* timestamp, int req_buffer[recv_size][m_size], MPI_Request* requests, int* state_status);
void exit_cs(int rank, int rep_message[2], int* req_counter, int* cs_status, int* timestamp, int* state_status, int req_buffer[recv_size][m_size], MPI_Request* requests, int sleep_time);

//********************************************************************
//
// main Function
//
// This function performs main function, calls the other functions
//
// Return Value
// ------------
// 0                         
//
// Global Variables
// ---------------
// int rank;											MPI processor ID
// int size;                                            MPI processor numbers
// int sim_time;									    simulation time
// int sleep_time;                                      sleep time
// int req_message[2];									request message
// int rep_message[2];								    reply message
// int req_buffer[recv_size][m_size];					request buffer
// int timestamp;										timestamp
// int cs_counter;										counting how many time cs was entered
// int req_counter;										no use	
// MPI_Request* requests;								MPI request type
// time_t start, end;									start time and end time
// int state_status;									the state status of processor
// int cs_status;										no use
//
//*******************************************************************
int main(int argc, char* argv[])
{
	int rank;
    int size;
    int sim_time;
    int sleep_time;
    int req_message[2];
    int rep_message[2];
    int req_buffer[recv_size][m_size];
    int timestamp;
    int cs_counter;
    int req_counter;
    MPI_Request* requests;
    time_t start, end;
    int state_status;
    int cs_status;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if(size<2 || size>8)
    {
       printf("The number of processors should be between 2 and 8.\n");
       MPI_Finalize();
       return 0;
    }
    
    if(atoi(argv[1])<10 || atoi(argv[1])>30)
    {
       printf("The simulation time should be between 10 seconds and 30 seconds.\n");
       MPI_Finalize();
       return 0;
    }
    
    if(atoi(argv[2])<0 || atoi(argv[2])>5)
    {
       printf("The sleep time should be between 0 seconds and 5 seconds.\n");
       MPI_Finalize();
       return 0;
    }
    
    sim_time = atoi(argv[1]);
    sleep_time = atoi(argv[2]);
    time(&start);
	
	timestamp = 1;	
	state_status = RELEASED;
    requests = (MPI_Request*)malloc(size);

    req_counter = 0;
    cs_status = 0;
    
    do
    {
        int rand_num;
        
        srand(time(NULL));
        rand_num = rand() % 10;
        if (rank == rand_num)
        {    
            enter_cs(rank, size, &timestamp, requests, &state_status, &cs_status, &cs_counter, &req_counter, req_message);
            exit_cs(rank, rep_message, &req_counter, &cs_status, &timestamp, &state_status, req_buffer, requests, sleep_time);
        }
        else
			recv_req(rank, size, req_message, rep_message, &req_counter, &timestamp, req_buffer, requests, &state_status);
		
        time(&end);
    }
    while((end-start) < sim_time);
        
    MPI_Finalize();
    return 0; 
}

//********************************************************************
//
// Enter critical section function
//
// This function performs enter the critical section for the processors
//
// Return Value
// ------------
// void                         
//
//
// Reference Parameters
// --------------------
// int* timestamp;										timestamp
// int rank;											MPI processor ID
// int size;                                            MPI processor numbers
// int req_message[2];									request message
// int cs_counter;										counting how many time cs was entered
// int req_counter;										no use	
// MPI_Request* requests;								MPI request type
// int state_status;									the state status of processor
//
// Local Variables
// ---------------
//  int i, j, k;                                        counter for loops
//  int flag[size];									    MPI flgs
//  int rep_recv[size-1][2];							request recieve buffer
//
//*******************************************************************
void enter_cs(int rank, int size, int* timestamp, MPI_Request *requests, int* state_status, int* cs_status, int* cs_counter, int* req_counter, int req_message[2])
{
    int i, j, k;
    int flag[size];
    int rep_recv[size-1][2];
	
    *state_status = REQUESTED;
    req_message[0] = rank;
    req_message[1] = *timestamp;
    MPI_Status status;
	
	printf("Process with rank %d and timestamp %d is requesting critical section.\n", rank, *timestamp);

    
    for (i=0; i<size; i++)
    {
        if(i != rank)
        {
			MPI_Send(req_message, 2, MPI_INT, i, REQ_TAG, MPI_COMM_WORLD);
			printf("sending request message(%d:%d) to %d \n",rank, *timestamp, i);

			MPI_Irecv(rep_recv[i], 2, MPI_INT, i, REP_TAG, MPI_COMM_WORLD, &requests[i]);
            
		}
    }
	
	for (k=0; k<size; k++)
    {
        flag[k] = 0;    
        if(k != rank)
        {
            MPI_Test(&requests[k],&flag[k],&status);
            while (!flag[k])
            MPI_Test(&requests[k],&flag[k],&status);
        }
    }

    *state_status = GRANTED;
    printf("process %d enter in critical section.\n", rank);
 
    *cs_counter++;
    MPI_Bcast(cs_counter, 1, MPI_INT,rank, MPI_COMM_WORLD);
    
    sleep(1);
    
}

//********************************************************************
//
// Recieve request function
//
// This function performs receive the requests from other processors
//
// Return Value
// ------------
// void                         
//
//
// Reference Parameters
// --------------------
// int* timestamp;										timestamp
// int rank;											MPI processor ID
// int size;                                            MPI processor numbers
// int req_message[2];									request message
// int rep_message[2];									reply message
// int cs_counter;										counting how many time cs was entered
// int req_counter;										no use	
// MPI_Request* requests;								MPI request type
// int state_status;									the state status of processor
//
// Local Variables
// ---------------
//  int i, j, k;                                        counter for loops
//  int flag[size];									    MPI flgs
//  int recv_temp[2];								    tempral recieve buffer
//  MPI_Status status;									MPI status
//  time_t t1,t2;										time counter
//
//*******************************************************************
void recv_req(int rank, int size, int req_message[2], int rep_message[2], int* req_counter, int* timestamp, int req_buffer[recv_size][m_size], MPI_Request *requests, int* state_status)
{
    int i, j, k;
    int flag[size];
    int recv_temp[2];
    MPI_Status status;
    time_t t1,t2;
 
    
            for (k=0; k<size; k++)
            {
                time(&t1);
                flag[k] = 0;    
                if(k != rank)
                {
					MPI_Irecv(recv_temp, 2, MPI_INT, k, REQ_TAG, MPI_COMM_WORLD,&requests[k]);
					//printf("The processor %d are waiting to receive the requests from %d!\n", rank, k);
                    MPI_Test(&requests[k],&flag[k],&status);
                    time(&t2);
                    
                    while (!flag[k] && (t2-t1) < 1)
                    {
                        MPI_Test(&requests[k],&flag[k],&status);
                        time(&t2);
                    }
                    
					if(flag[k])
					{
                    //printf("@@@@@@@@@@@@ recv_temp[0]:%d, [1]:%d, rank:%d \n", recv_temp[0], recv_temp[1], rank);

                    if (*state_status == GRANTED || (*state_status == REQUESTED && (recv_temp[1] > req_message[1] || (recv_temp[1] == req_message[1] && recv_temp[1] <= req_message[0]))))
                    {
                        *req_counter++;
                        
                        if (*req_counter == 1)
                        {
                            req_buffer[*req_counter-1][0] = recv_temp[0];
                            req_buffer[*req_counter-1][1] = recv_temp[1];
                        }
                        else
                        {
                            for (j = *req_counter-1; j>=0; j-- )
                            {
                                if (recv_temp[1] < req_buffer[j][1])
                                {
                                    req_buffer[j+1][1] = req_buffer[j][1];
                                    req_buffer[j][1] = recv_temp[1];
                                }
                            }
                        }

                        if(*timestamp <= recv_temp[1])
                            *timestamp = recv_temp[1] +1;
                    }
                    else
                    {    
                        rep_message[0] = rank;
                        rep_message[1] = *timestamp;
                        MPI_Send(rep_message, 2, MPI_INT, recv_temp[0], REP_TAG, MPI_COMM_WORLD);
						printf("Process %d replys to %d \n", rank, recv_temp[0]);

                    }
                  }
				  }
              }

}

//********************************************************************
//
// Exit critical section function
//
// This function performs receive the requests from other processors
//
// Return Value
// ------------
// void                         
//
//
// Reference Parameters
// --------------------
// int* timestamp;										timestamp
// int rank;											MPI processor ID
// int size;                                            MPI processor numbers
// int req_message[2];									request message
// int rep_message[2];									reply message
// int cs_counter;										counting how many time cs was entered
// int req_counter;										no use	
// MPI_Request* requests;								MPI request type
// int state_status;									the state status of processor
// int sleep_time                                       the input sleep time for after cs
//
// Local Variables
// ---------------
//  int i, j;                                        counter for loops										time counter
//
//*******************************************************************
void exit_cs(int rank, int rep_message[2], int* req_counter, int* cs_status, int* timestamp, int* state_status, int req_buffer[recv_size][m_size], MPI_Request* requests, int sleep_time)
{
    int i, j;
    *state_status = RELEASED;
    rep_message[0] = rank;
	
    
    /* reply to any queued requests(can be more than 1) */
    for(i = 0; i< *req_counter; i++)
    {
        rep_message[1] = *timestamp++;
        MPI_Send(rep_message, 2, MPI_INT, *req_buffer[i], REP_TAG, MPI_COMM_WORLD);
    }
	
	req_counter = 0;
    
    sleep(sleep_time);
    
}


