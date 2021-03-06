/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "rpctime.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

rpctime_struct *
rpctime_1(rpctime_struct *argp, CLIENT *clnt)
{
	static rpctime_struct clnt_res;

	memset((char *)&clnt_res, 0, sizeof(clnt_res));
	if (clnt_call (clnt, rpctime,
		(xdrproc_t) xdr_rpctime_struct, (caddr_t) argp,
		(xdrproc_t) xdr_rpctime_struct, (caddr_t) &clnt_res,
		TIMEOUT) != RPC_SUCCESS) {
		return (NULL);
	}
	return (&clnt_res);
}
