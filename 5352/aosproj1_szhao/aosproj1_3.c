//**************************************************************************************************
//NAME: Shuyi Zhao
//COSC 5352, Advanced Operationg System
//Project #1: Basic MPI Communication
//Date Assigned: Wednesday, October 3, 2012 
//Due Date: Wednesday, October 17, 2012 by 9:30 a.m. 
//Objective: PART 3
//**************************************************************************************************
//Requirements:Using the program tokenring.c as a guideline write an efficient 
//C/C++ programa that sends two tokens around the ring. One token should travel 
//in the clock-wise direction and simultaneously, another token should be sent in 
//the counter clock-wise direction. The number (n) of times the tokens should travel 
//around the ring should be read as a command line argument. Use non-blocking 
//communication so that the tokens travel independently. Let each process send 
//whichever token arrived first to its neighbor. Initially both tokens should be 
//sent by process with rank 0. The clock-wise token starts with value 0 and sent 
//first to process with rank 1; just like the example program. The counter-clock-wise 
//token should start with a value equal to n*p where 'p' is the number of processes 
//and sent first to the process with rank (p - 1). Whenever a token is received, 
//a message should be printed in the exact same format as the example program. Details:
//
//The name of your program must be aosproj1_3.c or aosproj1_3.cpp.
//The name of your executable must be aosproj1_3.
//The screenshot from jumpshot should be saved as aosproj1_3.pdf. 
    
#include "mpi.h"    
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	int rank;
	int size;
	int round;
	int token1;
	int token2;
	int send1;
	int recv1;
	int send2;
	int recv2;
   	int tag1 = 1;
   	int tag2 = 2;
	int left;
	int right;
    int i;
	MPI_Status status;
	MPI_Request request1[100], request2[100];


    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    
    if(size < 2)
    {
        printf("Token ring cannot be smaller than 2.\n");
        fflush(stdout);
        MPI_Finalize();
        return 0;
    }
    
    round = atoi(argv[1]);
    token1 = 0;
    token2 = round * size; 
    right = (rank + 1) % size; // right rank
    left = (size + rank - 1) % size; // left rank
        
    // processor 0 starts to send 0 in clock-wise and n*p in counter clock-wise    
    if(rank == 0)
    {
		MPI_Isend(&token1, 1, MPI_INT, right, tag1, MPI_COMM_WORLD, &request1[0]);
		MPI_Isend(&token2, 1, MPI_INT, left, tag2, MPI_COMM_WORLD, &request2[0]);
    }

    // n loops send in both way, each processor is waiting for its neigbours.
	for (i= 0; i < round; i++)
	{
		MPI_Irecv(&recv1, 1, MPI_INT, left, tag1, MPI_COMM_WORLD, &request1[rank-1]);
		MPI_Irecv(&recv2, 1, MPI_INT, right, tag2, MPI_COMM_WORLD, &request2[rank+1]);
		
		
	    printf("Rank %3d: received token1 %3d from rank %3d.\n", rank, token1, left);
		printf("Rank %3d: received token2 %3d from rank %3d.\n", rank, token2, right);
		fflush(stdout);
		
		send1 = recv1 + 1;	
        send2 = recv2 + 1;
        	
		sleep(1); /* To see the output printed one by one simulating message passing */

		if ((rank != 0) || (i < (round - 1)))
		{
			/* Only send it on if we are not rank 0, or there are more rounds to go */
		   MPI_Isend(&send1, 1, MPI_INT, right, tag1, MPI_COMM_WORLD, &request1[rank]);
		   MPI_Isend(&send2, 1, MPI_INT, left, tag2, MPI_COMM_WORLD, &request2[rank]);
		}
	 }

	MPI_Finalize();
	return 0;
}
