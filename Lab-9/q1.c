/*
Write a program to create five threads using pthread library. Find the sum of first 1000 numbers using five threads, where each thread can calculate sum of 200 numbers in each (parallel counting using threads). After completion of threads operation, print the final sum from the main function.
*/

//CS21B2028
#include <pthread.h>
#include <stdio.h>

int sum[5];

//function to calculate sum of 200 numbers 
void *threads_fn(void * arg)
{
    int id=(int)arg;
    int start=id*200;
    int i=1;
    
    while(i<=200)
    {
        sum[id]+=(i+start);
        i++;
    }
    return NULL;
}

int main()
{
    //CREATING 5 THREADS USING PTHREAD LIBRARY
    pthread_t t1,t2,t3,t4,t5;
    pthread_create(&t1,NULL,&threads_fn,(void *)0);
    pthread_create(&t2,NULL,&threads_fn,(void *)1);
    pthread_create(&t3,NULL,&threads_fn,(void *)2);
    pthread_create(&t4,NULL,&threads_fn,(void *)3);
    pthread_create(&t5,NULL,&threads_fn,(void *)4);
    
    //Parent thread will wait until it completes
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);
    pthread_join(t4,NULL);
    pthread_join(t5,NULL);
    
    //printing final sum
    printf("Total sum : %d\n",sum[0]+sum[1]+sum[2]+sum[3]+sum[4]);
    return 0;   
}