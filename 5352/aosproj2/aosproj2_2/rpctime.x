struct rpctime_struct{
       int number;
       char *arg_array;
       };
      
program RPCTIME_PROG{
        version RPCTIME_VERSION{
                rpctime_struct rpctime(rpctime_struct)=1;
        }=1;
}=0x20000417;
