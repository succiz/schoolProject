#include<stdio.h>
#include<mpi.h>

using spacename std;

int main(int argc, char*argv[])
{
    int msg;
    int myrank;
    int p;
    MPI_Status status;
     
    MPI_Init(&atgc,&argv);
    
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Comm_size(MPI_COMM_WORLD,&p);
    
    if(myrank == 0)
    {
        msg=1111;
        MPI_Send(&msg,1,MPI_INT,1,55,MPI_COMM_WORLD);
        cout<<"Process "<<myrank<<" send "<<msg<<endl;
        MPI_Recv(&msg, 1, MPI_INT,2,55,MPI_COMM_WORLD,&status);
        cout<<"Process "<<myrank<<" received "<<msg<<" from "<<status<<endl;   
    }    
    if(myrank == 1)
    {
        MPI_Recv(&msg, 1, MPI_INT,0,55,MPI_COMM_WORLD,&status);
        cout<<"Process "<<myrank<<" received "<<msg<<" from "<<status<<endl;
        MPI_Send(&msg,1,MPI_INT,2,55,MPI_COMM_WORLD);
        cout<<"Process "<<myrank<<" send "<<msg<<endl;
    }
    if(myrank == 2)
    {
        MPI_Recv(&msg, 1, MPI_INT,1,55,MPI_COMM_WORLD,&status);
        cout<<"Process "<<myrank<<" received "<<msg<<" from "<<status<<endl;
        MPI_Send(&msg,1,MPI_INT,0,55,MPI_COMM_WORLD);
        cout<<"Process "<<myrank<<" send "<<msg<<endl;
    }
    MPI_Finalize();
    return 0;
}
