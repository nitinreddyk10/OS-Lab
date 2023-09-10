/*
A parent process creates a child process and the child process creates a grandchild process. The parent creates a pipe that is shared between the parent and the child. The parent writes a message to the pipe and the child reads it from the pipe. The child creates another pipe which is shared between the child and the grandchild. Note that this pipe is not available to the parent and is not the same as the one shared by the parent and the child. The grandchild writes another message to the pipe and the child reads it from the pipe. After obtaining the two messages from the pipes, the child prints the difference in lengths of the two messages. Moreover, each of the three processes prints the PID of its respective parent process. The contents of the two messages must be taken as user inputs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 256

int main() 
{
    int parent_to_child_pipe[2]; 
    int child_to_grandchild_pipe[2];
    pid_t child_pid, grandchild_pid;

    if (pipe(parent_to_child_pipe) == -1) 
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    char parent_message[BUFFER_SIZE];
    char grandchild_message[BUFFER_SIZE];

    printf("Parent Process (PID: %d)\n", getpid());
    printf("Enter a message for the parent: ");
    fgets(parent_message, BUFFER_SIZE, stdin);

    parent_message[strcspn(parent_message, "\n")] = '\0';

    child_pid = fork();

    if (child_pid < 0) 
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) 
    { 
        close(parent_to_child_pipe[1]); 

     
        read(parent_to_child_pipe[0], parent_message, BUFFER_SIZE);

        printf("Child Process (PID: %d, Parent PID: %d)\n", getpid(), getppid());
        printf("Message from Parent: %s\n", parent_message);

        if (pipe(child_to_grandchild_pipe) == -1) 
        {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        printf("Enter a message for the grandchild: ");
        fgets(grandchild_message, BUFFER_SIZE, stdin);

        grandchild_message[strcspn(grandchild_message, "\n")] = '\0';

        grandchild_pid = fork();

        if (grandchild_pid < 0) 
        {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (grandchild_pid == 0) 
        { 
            close(child_to_grandchild_pipe[1]); 

            read(child_to_grandchild_pipe[0], grandchild_message, BUFFER_SIZE);

            printf("Grandchild Process (PID: %d, Parent PID: %d)\n", getpid(), getppid());
            printf("Message from Child: %s\n", grandchild_message);
            int parent_message_length = strlen(parent_message);
            int grandchild_message_length = strlen(grandchild_message);
            printf("Difference in Message Lengths: %d\n", abs(parent_message_length - grandchild_message_length));
            close(child_to_grandchild_pipe[0]); 

            exit(EXIT_SUCCESS);
        } 
        else 
        { 
            close(child_to_grandchild_pipe[0]); 
            write(child_to_grandchild_pipe[1], grandchild_message, strlen(grandchild_message) + 1);
            close(child_to_grandchild_pipe[1]); 
            exit(EXIT_SUCCESS);
        }
    } 
    else 
    { 
        close(parent_to_child_pipe[0]);
        write(parent_to_child_pipe[1], parent_message, strlen(parent_message) + 1);
        close(parent_to_child_pipe[1]); 
        wait(NULL); 
        exit(EXIT_SUCCESS);
    }

    return 0;
}