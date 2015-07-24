#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>
#include <time.h>

void sieve(long size)
{
     int i,j;
     int num = 0;
     char *sieve = (char*)calloc(size, 1);
     int sqr_size = (int)sqrt(size);

     omp_set_num_threads(8);
     #pragma omp parallel
     #pragma omp for
     for (i=2; i<=sqr_size ; i++)
     {
         if (!sieve[i])
            for(j = i+i; j < size; j+=i)
                  sieve[j] = 1;
     }

     //?
     for (i=2; i<size; i++)
         if (!sieve[i])
         {
            printf("%d ", i);
            num++;
            if (num%4 == 0)
               printf("\n");
         }

     printf("There are %d primes in %d", num, size);

     free(sieve);
}

int main()
{
    long size;

    printf("What is the bound number you want?\n");
    scanf("%d",&size);
    
    clock_t start, finish;
    double  duration;
    start = clock();
    printf("This is start:%f\n", start);
    sieve(size);

    finish = clock();
    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("\nIt use %f seconds.\n", duration);
    
    return 0;
}


