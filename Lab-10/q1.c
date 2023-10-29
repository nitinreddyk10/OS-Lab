/*
Create a parent process and its child process using fork().
In the parent process, one array (A) is given as [2, 1, 3, 0, 5, 0, 7, 9]. Now, take one number from the user and find the remainder value when you will divide the same number by values present in each location of the array A. Handle the situation using signal if required.
In the child process, print a random value between 10 to 30. Whenever you get a value more than 20, exit form the child process using exit() system call.
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

int main() {
    int n;
    printf("Enter a number: \n");
    scanf("%d", &n);
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror("fork is unable to create\n");
       
    }
   
    else if (pid == 0) {
        float m;
        double array[] = {2, 1, 3, 0, 5, 0, 7, 9};

        for (int i = 0; i < 8; i++) {
            if (n != 0) {
                m = array[i] / n;
                array[i] = m;
            } else {
           
                fprintf(stderr, "Division by zero is not allowed.\n");
                exit(1);
            }
        }

        for (int i = 0; i < 8; i++) {
            printf("The final array: %f\n", array[i]);
        }
    }
   
    else {
        int num;
        if (n > 20) {
            srand(time(NULL));
            num = rand() % 10 + 21;
            printf("Print the random number between 10 to 30: %d\n", num);
        }
       
        }
         return 0;
    }