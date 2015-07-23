/*
 * Programmer: Shuyi Zhao
 * Advanced Operating Systems
 * Programming Project #2 part2: RPC program
 * Program Description: Measure the timing performance of
 *                      1. A null remote call with zero arguments and zero results.
 *                      2. A null remote call with 1 arguments and 1 result.
 *                      3. A null remote call with 2 arguments and 2 results.
 *                      4. A null remote call with 10 arguments and 10 results.
 *                      5. A null remote call with a 400 byte array as argument and a 400 byte array as result.
 *                      6. A null remote call is where the remote procedure does not do any work, and the results are returned immediately. 
 * Due date: OCT 29, 2012
 * Instructor: Dr. Ajay K. Katangur
*/

/* The main Client program*/

#include <stdio.h>
#include <stdlib.h>
#include "rpctime.h"

//********************************************************************
//
// Primefib Function
//
// This function connects a client stub to a host based on the ip address 
// using UDP. It calls the prime_1 function firstly. Then it then calls the second function fibonacci_1.
//
// Return Value
// ------------
// void                        
//
// Value Parameters
// ----------------
// num	int			              The input number (the number of arguments)
//
// Reference Parameters
// --------------------
// host     char                  The ip address of the server
//
// Local Variables
// ----------------
// *clnt       CLIENT             The client
// *result_1   rpctime_struct     Received result
// rpctime_1_arg rpctime_struct   Sended argument struct
// MAX_TIMES   const int          Hard code maxmum times for running
// time        int                Running time
// i           int                i for loop
// t1        struct timeval       The beginning time
// t2        struct timeval       The end time
//
//
//*******************************************************************
void
rpctime_prog_1(char *host, int num)
{
	CLIENT *clnt;
	rpctime_struct  *result_1;
	rpctime_struct rpctime_1_arg;
	const int MAX_TIMES = 1000;
	int time;
	int i;
	
	rpctime_1_arg.number = num;
	rpctime_1_arg.arg_array = (char*)malloc(num);

	for (i = 0; i< num; i++)
        rpctime_1_arg.arg_array[i] = 'A';

    struct timeval t1,t2;    
    gettimeofday(&t1,NULL);
    
#ifndef	DEBUG
	clnt = clnt_create (host, RPCTIME_PROG, RPCTIME_VERSION, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */
    for (i = 0; i < MAX_TIMES; i++ )
    	result_1 = rpctime_1(&rpctime_1_arg, clnt);
    	
    gettimeofday(&t2,NULL);
    time = (t2.tv_sec-t1.tv_sec)*1000000+(t2.tv_usec-t1.tv_usec); 
      
   	if (result_1 == (int *) NULL) 
  		clnt_perror (clnt, "call failed");
    else
        printf("Running time is %f microseconds.\n", (float)time/MAX_TIMES);

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

//********************************************************************
//
// Program Main Function
//
// This is the program main function
//
// Return Value
// ------------
// int                 0 or else if it exits successfully
//
// Value Parameters
// ----------------
// argc		int		   The number of arguments passed in
//
// Reference Parameters
// --------------------
// argv     char**     The arguments references
//
// Local Variables
// ----------------
// host     char**     The host name
//
//
//*******************************************************************
int
main (int argc, char *argv[])
{
    char *host;
    
	if (argc != 3) { 
    printf ("usage: %s server_host number_u_want \n", argv[0]); 
    exit (1); 
    }
     
    host = argv[1];
    
    rpctime_prog_1 (host,atoi(argv[2]));
    exit (0);
}
