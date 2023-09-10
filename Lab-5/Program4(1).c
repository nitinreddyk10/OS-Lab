/*
Write two programs (Given Program41.c and Program42.c).
For Program41.c:
In Parent Process:
(a) Print your name, roll number, and Institution name 
(b) Print process id and its parent process id and returned value of fork() system call.

In Child Process,
(a) Print id of the process, it’s parent process id, and returned value of fork() system call.
(b) Use exec() system call to execute new program written in Program42.c. In Program42.c, write or compute anything of your choice. The executable file for Program42.c is (progam32).
(c) Write a few printf statements after operation (b).
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    printf("Parent Process:\n");
    printf("(a) Name: Your Name\n");
    printf("    Roll Number: Your Roll Number\n");
    printf("    Institution: Your Institution Name\n");

    pid_t parent_pid = getpid();
    pid_t parent_parent_pid = getppid();
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {
        // Child Process
        printf("\nIn Child Process:\n");
        printf("(a) Process ID: %d\n", getpid());
        printf("    Parent Process ID: %d\n", getppid());
        printf("    Return value of fork(): %d\n", child_pid);

        // Executing Program42.c
        execl("./program32", "program32", NULL);

        perror("Exec failed"); // This line will be reached only if exec fails
        return 1;
    } else {
        // Parent Process
        printf("\nIn Parent Process:\n");
        printf("(b) Process ID: %d\n", parent_pid);
        printf("    Parent Process ID: %d\n", parent_parent_pid);
        printf("    Return value of fork(): %d\n", child_pid);
    }

    return 0;
}