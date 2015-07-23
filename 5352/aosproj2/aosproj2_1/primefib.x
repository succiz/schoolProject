struct prime_time{
       int nth_number;
       int time;
       };
typedef struct prime_time result_type;       

program PRIMEFIB_PROG{
        version PRIMEFIB_VERSION{
                result_type prime(int number)=1;
                result_type fib(int number)=2;
        }=1;
}=0x20000017;
