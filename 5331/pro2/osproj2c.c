//*********************************************************
//
// Shuyi Zhao
// Operating Systems
// Project #2: Simple Pthreads and MPI Programs
//
//*********************************************************
#include<iostream>
#include<mpi.h>
#include<stdio.h>

using namespace std;

int main(int argc, char*argv[])
{
    int msg;
    int myrank;
    int p;
    MPI_Status status;
     
    MPI_Init(&argc,&argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    
	//process0 sent message to process1
    if(myrank == 0)
    {
        msg=1111;
        MPI_Send(&msg,1,MPI_INT,1,55,MPI_COMM_WORLD);
        cout<<"Process "<<myrank<<" send "<<msg<<endl;
        MPI_Recv(&msg, 1, MPI_INT,2,55,MPI_COMM_WORLD,&status);
        cout<<"Process "<<myrank<<" received "<<msg<<" from "<<status.MPI_SOURCE<<endl;   
    } 

	//process1 sent message to process2
    if(myrank == 1)
    {
        MPI_Recv(&msg, 1, MPI_INT,0,55,MPI_COMM_WORLD,&status);
        cout<<"Process "<<myrank<<" received "<<msg<<" from "<<status.MPI_SOURCE<<endl;
		msg=msg*3+1;
        MPI_Send(&msg,1,MPI_INT,2,55,MPI_COMM_WORLD);
        cout<<"Process "<<myrank<<" send "<<msg<<endl;
    }

	//process2 sent message to process0
    if(myrank == 2)
    {
        MPI_Recv(&msg, 1, MPI_INT,1,55,MPI_COMM_WORLD,&status);
        cout<<"Process "<<myrank<<" received "<<msg<<" from "<<status.MPI_SOURCE<<endl;
		msg=msg*3+1;
        MPI_Send(&msg,1,MPI_INT,0,55,MPI_COMM_WORLD);
        cout<<"Process "<<myrank<<" send "<<msg<<endl;
    }
    MPI_Finalize();
    return 0;
}
