#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

const int MAX_LENGTH = 256000;

int main(int argc, char *argv[])
{
    int i;
    int j;
    int id;
//    int p;
    char *message;
    double times;
    double total_time;
    double aver_time;
    MPI_Status status;
    
    
    MPI_Init (&argc, &argv);
    MPI_Comm_rank (MPI_COMM_WORLD, &id);
//    MPI_Comm_size (MPI_COMM_WORLD, &p);
    
    for(j=1; j<MAX_LENGTH; j=j+1024)
    { 
        message = (char*)malloc(j*sizeof(1));
        for(int t=0; t<j; t++)
            message[t]='i';
        total_time = 0;
        for (i=0; i < 10; i++) 
        {
            if (id == 0) 
            {
                /* Start timer */
                times =- MPI_Wtime();
//                printf("1 time:%f\n",times);
                
                MPI_Send(message, j, MPI_INT, 1, 100, MPI_COMM_WORLD);
                MPI_Recv(message, j, MPI_INT, 1, 200, MPI_COMM_WORLD, &status);
            
                /* Stop timer */
                times += MPI_Wtime();
//                printf("2 time:%f\n",times);
                total_time += times;/*?*/
//                printf("3 time:%f\n",times);
            } 
            else if (id == 1) 
            {
                MPI_Recv(message, j, MPI_INT, 0, 100,MPI_COMM_WORLD, &status);
                MPI_Send(message, j, MPI_INT, 0, 200, MPI_COMM_WORLD);
            }
            
            if (id == 0 && i == 9)
            {
               printf ("%d,%f\n",j,total_time/10 );
//            
//               ofstream myfile;
//               myfile.open("data.txt");
//               myfile<<setw(8)<<j*8<<setw(20)<<aver_time<<endl;
//               myfile.close();
            }
        }/* end for i */
        free(message);
        
    }/* end for j */
    
    MPI_Finalize();
    return 0;
    
}

