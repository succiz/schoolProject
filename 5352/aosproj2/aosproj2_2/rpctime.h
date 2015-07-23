/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _RPCTIME_H_RPCGEN
#define _RPCTIME_H_RPCGEN

#include <rpc/rpc.h>


#ifdef __cplusplus
extern "C" {
#endif


struct rpctime_struct {
	int number;
	char *arg_array;
};
typedef struct rpctime_struct rpctime_struct;

#define RPCTIME_PROG 0x20000417
#define RPCTIME_VERSION 1

#if defined(__STDC__) || defined(__cplusplus)
#define rpctime 1
extern  rpctime_struct * rpctime_1(rpctime_struct *, CLIENT *);
extern  rpctime_struct * rpctime_1_svc(rpctime_struct *, struct svc_req *);
extern int rpctime_prog_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define rpctime 1
extern  rpctime_struct * rpctime_1();
extern  rpctime_struct * rpctime_1_svc();
extern int rpctime_prog_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_rpctime_struct (XDR *, rpctime_struct*);

#else /* K&R C */
extern bool_t xdr_rpctime_struct ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_RPCTIME_H_RPCGEN */