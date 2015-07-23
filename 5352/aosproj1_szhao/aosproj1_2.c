//**************************************************************************************************
//NAME: Shuyi Zhao
//COSC 5352, Advanced Operationg System
//Project #1: Basic MPI Communication
//Date Assigned: Wednesday, October 3, 2012 
//Due Date: Wednesday, October 17, 2012 by 9:30 a.m. 
//Objective: PART 3
//**************************************************************************************************
//Requirements:Write an efficient C/C++ program using MPI which adds the first 
//1024 numbers. Finally process 0 should print out the sum and the time taken 
//for computation. Run it using 1, 2, 4, 7, 8, 12, 13, 16, 32, 35, 63, 64, 125, 128 
//processes in parallel. Measure the time for each run (average over 5 iterations). 
//Store the data in a excel file, and plot a graph of time vs the number of processes. 
//Write a small report on what can be concluded from the results achieved. Details:
//        
//a.The name of your program must be aosproj1_2.c or aosproj1_2.cpp.
//b.The name of your executable must be aosproj1_2.
//c.The name of your excel file must be aosproj1_2.xlsx.
//d.The name of your report file must be aosproj1_2.docx or aosproj1_2.txt.
//e.The screenshot from jumpshot should be saved as aosproj1_2.pdf.


#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main (int argc, char *argv[])
{
   int rank; // process rank
   int size; // process number
   double elapsed_time;
   int sub_sum;
   int sum;
   int round;
   int i;

   // Initialize MPI
   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);
   MPI_Comm_size(MPI_COMM_WORLD, &size);
   MPI_Barrier(MPI_COMM_WORLD);//until all processor finished
   
   elapsed_time = - MPI_Wtime();
   
   for (round = 0; round < 5; round++)
   {
       sub_sum = 0;
       for (i=rank; i<1025; i=i+size)
           sub_sum += i;
           
       // send sub_sum to processor 0, and get the sum of them.
       MPI_Reduce(&sub_sum, &sum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
   }

   elapsed_time += MPI_Wtime();
   
   if (rank == 0)
   {
      printf("The sum of first 1024 integer is: %d\n", sum);
      printf("The running average time is: %f\n", elapsed_time/5.0);
      fflush(stdout);
   }
           
   MPI_Finalize();
   return 0;
}

