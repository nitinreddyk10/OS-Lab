/*
Write a program using pipe() and fork() in which parent process takes one string as input. The same is sent to the child using pipe1 and child will reverse it. After the reversing is completed, the child process will send it (reversed string) to parent process using pipe2. Subsequently, parent process will read the string and displays it.
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


int main()
{
    int pipe1[2]; 
    int pipe2[2];
    
    int n=32;

    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) 
    {
        perror("Pipe creation failed");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();

    if (pid == -1) 
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) 
    {
    
        close(pipe1[1]); 
        close(pipe2[0]); 

        char input[n];
        char reversed[n];

        read(pipe1[0], input, n);
        int length = strlen(input);
        for (int i = 0; i < length; i++) {
            reversed[i] = input[length - i - 1];
        }
        reversed[length] = '\0';
        write(pipe2[1], reversed, strlen(reversed) + 1);
        close(pipe1[0]);
        close(pipe2[1]);
        exit(EXIT_SUCCESS);
    } 
    else 
    {
        // Parent process
        close(pipe1[0]);
        close(pipe2[1]);

        printf("Enter a string: \n");
        char input[n];
        scanf("%s",input);

        write(pipe1[1], input, strlen(input) + 1);
        close(pipe1[1]);

        char reversed[n];
        read(pipe2[0], reversed, n);
        
        printf("Reversed string: %s\n", reversed);
        close(pipe2[0]);
        wait(NULL);
        exit(EXIT_SUCCESS);
    }

    return 0;
}