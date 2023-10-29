/*
Implement Banker's algorithm. Consider 6 processes and 4 types of resources.
Define the ALLOCATION and  MAX matrix  and the AVAILABLE array. Find the NEED matrix. You must ensure that your  initial allocation will always lead to the system in  safe state.
Now, take the input from the user for any process as additional request. Find that this request will lead to safe  or unsafe state.
For eg. P1=(0, 0, 1, 1)
Check whether additional P1 request will lead to safe state or not,
(a) If safe then print "SAFE", sequence of safe processes and update the  ALLOCATION, MAX and NEED Matrix
(b) If unsafe then print "UNSAFE" and discard the request without updating the above matrix.
You must take multiple times the input from the user.
*/

#include <stdio.h>

#define NUM_PROCESSES 6
#define NUM_RESOURCES 4

int processAllocation[NUM_PROCESSES][NUM_RESOURCES] = {
    {0, 1, 0, 0},
    {2, 0, 0, 1},
    {3, 0, 2, 0},
    {2, 1, 1, 0},
    {0, 0, 2, 1},
    {0, 1, 3, 0}
};

int processMaxDemand[NUM_PROCESSES][NUM_RESOURCES] = {
    {7, 5, 3, 2},
    {3, 2, 2, 2},
    {9, 5, 2, 2},
    {2, 2, 2, 3},
    {4, 3, 3, 3},
    {6, 3, 3, 2}
};

int availableResources[NUM_RESOURCES] = {3, 2, 2, 2};

void calculateNeed(int needMatrix[][NUM_RESOURCES], int maxMatrix[][NUM_RESOURCES], int allocationMatrix[][NUM_RESOURCES]) {
    printf("Need Matrix\n");
    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            needMatrix[i][j] = maxMatrix[i][j] - allocationMatrix[i][j];
            printf("%d ", needMatrix[i][j]);
        }
        printf("\n");
    }
}

void displayMatrix(int matrix[][NUM_RESOURCES], int numRows, int numCols) {
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int isSafeState(int requestProcess, int requestedResources[], int needMatrix[][NUM_RESOURCES], int availableResources[], int allocationMatrix[][NUM_RESOURCES]) {
    int workResources[NUM_RESOURCES];
    int finish[NUM_PROCESSES] = {0};
    int safeSequence[NUM_PROCESSES];
    int count = 0;

    for (int i = 0; i < NUM_RESOURCES; i++) {
        workResources[i] = availableResources[i];
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (finish[i] == 0) {
            int canAllocate = 1;
            for (int j = 0; j < NUM_RESOURCES; j++) {
                if (requestedResources[j] > needMatrix[i][j] || requestedResources[j] > workResources[j]) {
                    canAllocate = 0;
                    break;
                }
            }
            if (canAllocate) {
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    workResources[j] -= requestedResources[j];
                    allocationMatrix[i][j] += requestedResources[j];
                    needMatrix[i][j] -= requestedResources[j];
                }

                finish[i] = 1;
                safeSequence[count] = i;
                count++;
                for (int j = 0; j < NUM_RESOURCES; j++) {
                    workResources[j] += allocationMatrix[i][j];
                }
                i = -1;
            }
        }
    }

    if (count == NUM_PROCESSES) {
        printf("SAFE, Safe sequence: ");
        for (int i = 0; i < NUM_PROCESSES; i++) {
            printf("P%d", safeSequence[i]);
            if (i < NUM_PROCESSES - 1) {
                printf(" -> ");
            }
        }
        printf("\n");
        return 1;
    } else {
        printf("UNSAFE, Request not granted.\n");
        return 0;
    }
}

int main() {
    int needMatrix[NUM_PROCESSES][NUM_RESOURCES];
    calculateNeed(needMatrix, processMaxDemand, processAllocation);

    while (1) {
        int requestingProcess;
        int resourceRequest[NUM_RESOURCES];

        printf("Enter the process number (1 to 6) for an additional request (0 to exit): ");
        scanf("%d", &requestingProcess);

        if (requestingProcess == 0) {
            printf("Exiting\n");
            break;
        }

        if (requestingProcess < 1 || requestingProcess > NUM_PROCESSES) {
            printf("Invalid process number.\n");
            continue;
        }

        printf("Enter the request for process P%d\n", requestingProcess);
        for (int i = 0; i < NUM_RESOURCES; i++) {
            printf("Enter the request for resource %d: ", i + 1);
            scanf("%d", &resourceRequest[i]);
        }

        if (isSafeState(requestingProcess - 1, resourceRequest, needMatrix, availableResources, processAllocation)) {
            for (int i = 0; i < NUM_RESOURCES; i++) {
                availableResources[i] -= resourceRequest[i];
                processAllocation[requestingProcess - 1][i] += resourceRequest[i];
                needMatrix[requestingProcess - 1][i] -= resourceRequest[i];
            }
        }
    }

    return 0;
}