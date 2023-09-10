/*
Write two different programs (Sender and Receiver) in C to demonstrate IPC using shared memory. Process "Sender.c" will write atleast 100 bytes of data to the shared memory and process "Receiver.c" will read from the shared memory and displays it. Then, "Receiver.c" will write atleast 100 bytes of data to the same shared memory and  "Sender.c" will read and displays it
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/shm.h>
#include<sys/ipc.h>
int main()
{
    key_t key = ftok("shmfile",-019);             //creating key
   
    int shmid = shmget(key,1024,0666|IPC_CREAT);   //returning identifier
   
    char *str= (char*) shmat(shmid,(void*)0,0);         //attached shared memory
   
    printf("Data read: %s\n",str);
    shmdt(str);                                     //clearing shared memory
    shmctl(shmid,IPC_RMID,NULL);
   
   
    //Replying
    key_t key2=ftok("shmfile",-696);                //creating key
   
    char *str2=(char*) shmat(shmid,(void*)0,0);     //returning identifier
    printf("Write data: ");            
    gets(str2);
    shmdt(str2);                                    //clearing memory
    shmctl(shmid,IPC_RMID,NULL);
   
return 0;
}