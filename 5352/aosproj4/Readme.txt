/**************************************************************************************************************************
 * Programmer: Shuyi Zhao
 * Advanced Operating Systems
 * Programming Project #4: Chang and Robert's Leader Election Algorithm
 * Due date: Dec 4th, 2012
 * Instructor: Dr. Ajay K. Katangur
 **************************************************************************************************************************
 * Program Description: Write a C or C++ program named election.c or election.cpp (executable name should be election) 
 *                      to implement the Chang and Robert's Leader Election Algorithm using MPI.
***************************************************************************************************************************/

1.checklist:
Makefile
aosproj4.c
aosproj4

2.compilation
Use make to compile aosproj4.c to get the execute file aosproj4

3.run:
Use such as: $mpirun -np 4 aosproj4 3
The processor number has to be greater than 3 and the 1st argrument has to be between 0 and the processor size.

4.the result
such as:
[szhao@penguin aosproj4]$ mpirun -np 4 aosproj4 3
Initially Rank:  0, Identifier: 1919802296. 
Initially Rank:  1, Identifier: 537182762. 
Initially Rank:  2, Identifier: 1320399847. 
Initially Rank:  3, Identifier: 1008649591. 
Processor 3 is initiating the election and sending the number 1008649591 to processor 0.
Phase: 1, Rank:  0, Identifier: 1919802296, Status: Active
Phase: 1, Rank:  1, Identifier: 537182762, Status: Passive
Phase: 1, Rank:  2, Identifier: 1320399847, Status: Passive
Phase: 2, Rank:  3, Identifier: 1008649591, Status: Passive
Phase: 2, Rank:  0, Identifier: 1919802296, Status: Active
I am the Leader and my Rank is: 0 and my Identifier is: 1919802296

