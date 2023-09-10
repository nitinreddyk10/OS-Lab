// Write a C program which will create a child process from a parent process. In parent process, define one global array and take input from the user.
// Perform following operations.

// In Parent Process:
// (a) Update the array by subtracting 3 from each element of the array.
// (b) Print the elements, address of the elements and find the minimum element after performing (a).
// (c) Print process id and it’s parent process id

// In Child Process:
// (a) Update the global array by adding 2 on each element of the array.
// (b) Print the elements, address of the elements and find the maximum element after performing (a)
// (c) Print process id and it’s parent process id

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int globalArray[10];

void printArrayInfo(int arr[], int size) {
    int min = arr[0];
    int max = arr[0];

    printf("Elements of the array:\n");
    for (int i = 0; i < size; i++) {
        printf("Element[%d]: %d\tAddress: %p\n", i, arr[i], (void *)&arr[i]);

        // Update min and max
        if (arr[i] < min) {
            min = arr[i];
        }
        if (arr[i] > max) {
            max = arr[i];
        }
    }

    printf("Minimum element: %d\n", min);
    printf("Maximum element: %d\n", max);
}

int main() {
    int n;
    printf("Enter size of array : ");
    scanf("%d",&n);
    // Initialize the global array
    for (int i = 0; i < n; i++) {
        printf("Enter element %d: ", i);
        scanf("%d", &globalArray[i]);
    }

    // Create child process
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {
        // Child process
        printf("\nChild Process:\n");

        // Update array elements in child process
        for (int i = 0; i < n; i++) {
            globalArray[i] += 2;
        }

        printArrayInfo(globalArray, n);

        printf("Child Process ID: %d\n", getpid());
        printf("Parent Process ID: %d\n", getppid());
    } else {
        // Parent process
        printf("\nParent Process:\n");

        // Update array elements in parent process
        for (int i = 0; i < n; i++) {
            globalArray[i] -= 3;
        }

        printArrayInfo(globalArray, n);

        printf("Parent Process ID: %d\n", getpid());
        printf("Parent's Parent Process ID: %d\n", getppid());
    }

    return 0;
}