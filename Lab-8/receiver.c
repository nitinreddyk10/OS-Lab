#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

// Define a structure for the message
struct message
{
    long mtype;
    int data; // Change the data type to int for receiving a number
};

int main()
{
    key_t key;
    int msgid;

    // Generate the same key as in Sender.c
    key = ftok("Sender.c", 'A');

    // Get the ID of the existing message queue
    msgid = msgget(key, 0666);

    if (msgid == -1)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Receive a message of type 1
    struct message msg;

    if (msgrcv(msgid, &msg, sizeof(msg.data), 1, 0) == -1)
    {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
 
    long long int number;
    number=msg.data;
    printf("Odd digits in %lld are: ", number);
     if (number < 0) 
     {
        number = -number; // Make it positive for processing
        printf("-");     // Print the negative sign
    }

    // Extract and print odd digits
    while (number > 0) 
    {
        int digit = number % 10;
        if (digit % 2 != 0)
        {
            printf("%d ", digit);
        }
        number /= 10;
    }
    //printf("Receiver: Received number: %d\n", msg.data);

    // Clean up: Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1)
    {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}