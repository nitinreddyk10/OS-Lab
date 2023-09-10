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

int main() {
    printf("This is Program42.c\n");
    printf("Performing some computation or task of your choice...\n");
    printf("Computation/task completed.\n");
    return 0;
}