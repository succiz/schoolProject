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

#include "rpctime.h"

//********************************************************************
//
// rpctime_1_svc
//
// This function computes the nth prime number.
//
// Return Value
// ------------
// result               Struct that contains n returns
//
//
// Reference Parameters
// --------------------
// argp     int*        The parameter
// rqstp    svc_req*    A struct defined by the RPCgen
//
// Local Variables
// ----------------
//	result    static result_type  Return result struct
//
//
//*******************************************************************
rpctime_struct *
rpctime_1_svc(rpctime_struct *argp, struct svc_req *rqstp)
{
	static rpctime_struct result;
	result.number = argp->number;
	result.arg_array = (char*)malloc(result.number);
	result.arg_array = argp->arg_array;
	
	return &result;
}
