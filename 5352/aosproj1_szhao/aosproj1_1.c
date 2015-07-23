//**************************************************************************************************
//NAME: Shuyi Zhao
//COSC 5352, Advanced Operationg System
//Project #1: Basic MPI Communication
//Date Assigned: Wednesday, October 3, 2012 
//Due Date: Wednesday, October 17, 2012 by 9:30 a.m. 
//Objective: PART 1
//**************************************************************************************************
//Requirements: Assume a telephone number is represented using 10 digits. 
//Write a multi-process program using C/C++ and MPI that will send messages between 
//ranks in the order of the digits in a phone number. For example in case of 3618252478 
//the messages would be sent from 3 to 6 to 1 to 8 to 2 to 5 to 2 to 4 to 7 to 8. 
//The telephone number should only be read by the process, whose rank is equal to 
//the first digit of the telephone number using command line arguments. 
//The other processes should receive the telephone number as part of the message. 
//Each process should also print the received message to standard output. Details:
//
//The name of your program must be aosproj1_1.c or aosproj1_1.cpp.
//The name of your executable must be aosproj1_1.
//The screenshot from jumpshot should be saved as aosproj1_1.pdf.

#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main (int argc, char *argv[])
{
   int rank; // process rank
   char message[10];
   int size;
   int i;
   int j;
   char send[11];
   char recv[11];


   MPI_Status status;
   MPI_Request request;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   
   //check if the argument is satisfied.
   if (size != 10)
   {
      printf("Have to be 10 processors. Please run it again.\n");
      MPI_Finalize();
      return 0 ;
   }
            
   send[10]='\0';
   recv[10]='\0';
   
   for(i = 0; i<10; i++)
         message[i] = argv[1][i];
         
   //start passing message
   for (j=0; j<10; j++)
   {
       if (rank == message[j]-'0')
       {
           // the first processor start sending message
           if(j == 0)
           {
                MPI_Isend(message,10,MPI_CHAR,message[j+1]-'0',52,MPI_COMM_WORLD,&request);
                printf("Process %3d is the first processor, and sending the phone number: %s \n", rank, message);
           }
    
           // other processores receive message
           if (j != 0)
           {
             MPI_Irecv(recv,10,MPI_CHAR,message[j-1]-'0',52,MPI_COMM_WORLD,&request);
             //wait until receive the message 
             MPI_Wait(&request, &status);
             printf("Process %3d received this message: %s\n", rank, recv);
             fflush(stdout);
           }
            //the other processors send message except the last one
            if (j != 9) 
            {
                     
             int k;
             for(k=0; k<10; k++)
                 send[k] = recv[k];
                 
             MPI_Isend(send,10,MPI_CHAR,message[j+1]-'0',52,MPI_COMM_WORLD,&request);
           }
           
       }

   }

   MPI_Finalize();
   return 0;      
}
