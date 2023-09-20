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
    int data; // Change the data type to int for sending a number
};

int main()
{
    key_t key;
    int msgid;

    // Generate a unique key for the message queue
    key = ftok("Sender.c", 'A');

    // Create a message queue, or get the ID of an existing one
    msgid = msgget(key, 0666 | IPC_CREAT);

    if (msgid == -1)
    {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    // Create a message of type 1
    int num;
    printf("Enter the number that needs to be send(atleast 10 numbers)\n");
    scanf("%d",&num);
    struct message msg;
    msg.mtype = 1;
    msg.data = num; // Set the integer data you want to send

    // Send the message to the receiver
    if (msgsnd(msgid, &msg, sizeof(msg.data), 0) == -1)
    {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }

    printf("Sender: Sent number to Receiver.\n");

    return 0;
}