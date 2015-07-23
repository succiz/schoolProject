// For test with timestamp = 1

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
	printf("process %d, %d \n", rank, timestamp);
	
	
	state_status = RELEASED;
	printf("process %d, status: %d\n", rank, state_status);

    requests = (MPI_Request*)malloc(size);
	//recv_requests = (MPI_Request*)malloc(size);

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

void enter_cs(int rank, int size, int* timestamp, MPI_Request *requests, int* state_status, int* cs_status, int* cs_counter, int* req_counter, int req_message[2])
{
    int i, j, k;
    int flag[size];
    int rep_recv[size-1][2];
    //req_recv = (int*)malloc(size);
	
    *state_status = REQUESTED;
    req_message[0] = rank;
    req_message[1] = *timestamp;
	//req_message = {rank, timestamp};
    MPI_Status status;
	
	printf("Process with rank %d and timestamp %d is requesting critical section.\n", rank, *timestamp);

    
    for (i=0; i<size; i++)
    {
        if(i != rank)
        {
            printf("this is i des:%d\n", i);
			MPI_Send(req_message, 2, MPI_INT, i, REQ_TAG, MPI_COMM_WORLD);
			printf("sending message(%d:%d) to %d \n",rank, *timestamp);
			printf("!!! req_message 0:%d, 1:%d\n", req_message[0], req_message[1]);

			MPI_Irecv(rep_recv[i], 2, MPI_INT, i, REP_TAG, MPI_COMM_WORLD, &requests[i]);
			
			//MPI_Wait(&send_requests[i],&status);
			//MPI_Wait(&recv_requests[i],&status);
            for (k=0; k<size; k++)
            {
                flag[k] = 0;    
                if(j != rank)
                {
                    MPI_Test(&requests[k],&flag[k],&status);
                    while (!flag[k])
                        MPI_Test(&requests[k],&flag[k],&status);
                }
             }
            
		}
    }
     
	//timestamp++;
    //req_counter++;
    //MPI_Bcast(&req_couner, 1, MPI_INT,rank, MPI_COMM_WORLD);
    
    //for (j=0; j< size; j++)
    //{
    //    if(j != rank)
    //        MPI_Irecv(rep_recv[j], 2, MPI_INT, j, REP_TAG, MPI_COMM_WORLD, &requests[j]);
    //}
    
    //MPI_Waitall(size-1,requests[],MPI_STATUSES_IGNORE);
    //for (k=0; k<size; k++)
    //{
    //    flag[k] = 0;    
    //    if(j != rank)
    //    {
    //        MPI_Test(&requests[k],&flag[k],&status);
    //        while (!flag[k])
    //            MPI_Test(&requests[k],&flag[k],&status);
    //    }
    //}

    *state_status = GRANTED;
    printf("process %d enter in critical section.\n", rank);
//    *cs_status = ON;
 //   MPI_Bcast(cs_status, 1, MPI_INT,rank, MPI_COMM_WORLD);
    
    //req_counter--;
    //MPI_Bcast(&req_couner, 1, MPI_INT,rank, MPI_COMM_WORLD);
 
    *cs_counter++;
    MPI_Bcast(cs_counter, 1, MPI_INT,rank, MPI_COMM_WORLD);
    
    sleep(1);
    
}

void recv_req(int rank, int size, int req_message[2], int rep_message[2], int* req_counter, int* timestamp, int req_buffer[recv_size][m_size], MPI_Request *requests, int* state_status)
{
    int i, j, k;
    int flag[size];
    int recv_temp[2];
    MPI_Status status;
 
    for(i=0; i<size; i++)
	{
		if(i != rank)
		{-
			MPI_Irecv(recv_temp, 2, MPI_INT, i, REQ_TAG, MPI_COMM_WORLD,&requests[i]);
			//printf("try this recv_temp[0]:%d, [1]:%d, rank:%d \n", recv_temp[0], recv_temp[1], rank);
            
            for (k=0; k<size; k++)
            {
                flag[k] = 0;    
                if(j != rank)
                {
                    MPI_Test(&requests[k],&flag[k],&status);
                    while (!flag[k])
                        MPI_Test(&requests[k],&flag[k],&status);
	
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
                        printf("recv 0:%d\n", recv_temp[0]);
                        MPI_Send(rep_message, 2, MPI_INT, recv_temp[0], REP_TAG, MPI_COMM_WORLD);
                    }
                  }
              }
		}
	}
}

void exit_cs(int rank, int rep_message[2], int* req_counter, int* cs_status, int* timestamp, int* state_status, int req_buffer[recv_size][m_size], MPI_Request* requests, int sleep_time)
{
    int i, j;
    *state_status = RELEASED;
    rep_message[0] = rank;
    MPI_Bcast(cs_status, 1, MPI_INT, rank, MPI_COMM_WORLD);
	
    
    /* reply to any queued requests(can be more than 1) */
    for(i = 0; i< *req_counter; i++)
    {
        rep_message[1] = *timestamp++;
        MPI_Send(rep_message, 2, MPI_INT, *req_buffer[i], REP_TAG, MPI_COMM_WORLD);
    }
	
	req_counter = 0;
    
    sleep(sleep_time);
    
}