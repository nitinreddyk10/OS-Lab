/*
Given 2 threads, schedule the order of execution in such a way that Thread A has to wait for Thread B and vice versa. In other words, given the code below you must guarantee that Statement A1 happens before Statement B2 and Statement B1 happens before Statement A2.
*/

//CS21B2028

#include <pthread.h>
#include <stdio.h>
//#include <unistd.h>

//initialising mutex locks

pthread_mutex_t mutexA= PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutexB= PTHREAD_MUTEX_INITIALIZER;

//function for thread1 
void* thr_A(void * arg)
{
  printf("I am statement A1\n");
  //lock A
  pthread_mutex_lock(&mutexA);
  //Unlock B to print B1
  pthread_mutex_unlock(&mutexB); //jump
  printf("I am statement A2\n");
  //Unlock B to print B2
  pthread_mutex_unlock(&mutexB);
  return NULL;  
}

//function for thread2
void* thr_B(void * arg)
{
   printf("I am statement B1\n");
   //lock B
   pthread_mutex_lock(&mutexB);
   //unlock A to print A2
   pthread_mutex_unlock(&mutexA);//jump
   //lock B so it shouldnt execute B2 before A2
   pthread_mutex_lock(&mutexB);
   printf("I am statement B2\n");
   //unlock A
   pthread_mutex_unlock(&mutexA);
    return NULL;
}

int main()
{
    //creation of threads
    pthread_t thr1,thr2;
    
    pthread_mutex_lock(&mutexA);
    pthread_create(&thr1,NULL,thr_A,NULL);
    pthread_create(&thr2,NULL,thr_B,NULL);
    
    pthread_join(thr1,NULL);
    pthread_join(thr2,NULL);
    
    pthread_mutex_destroy(&mutexA);
    pthread_mutex_destroy(&mutexA);
    
    return 0;
}