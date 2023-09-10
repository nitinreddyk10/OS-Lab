/*
Write a C program to implement First Come First Serve CPU Scheduling Algorithm.
(i) Take input from the user only once (Process_id, Arrival Time, Burst Time) and apply FCFS.
(ii) Your algorithm should work for both scenario: (a) all tasks arrive at the same time (b) tasks may arrive at a different time.
(iii) Compute completion time, turnaround time,  waiting time and response time for each process  for the given input.
(iv) Further compute the average waiting time and average turnaround time.
(v) Print the schedule for the given input.
Note: You can use only integers for process id. Use the linked list implementation for the Queue. 
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Process {
    int p_id; // Process ID
    int arrival_time; // Arrival Time
    int burst_time; // Burst Time
    int completion_time; // Completion Time
    int turnaround_time; // Turnaround Time
    int waiting_time; // Waiting Time
    int response_time; // Response Time
} Process;

// Linked List Node
typedef struct Node {
    Process data;
    struct Node* next;
} Node;

// Queue structure
typedef struct Queue {
    Node* front;
    Node* rear;
} Queue;

// Function to create an empty queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}

// Function to enqueue a process into the queue
void enqueue(Queue* queue, Process process) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = process;
    newNode->next = NULL;

    if (queue->rear == NULL) {
        queue->front = queue->rear = newNode;
        return;
    }

    queue->rear->next = newNode;
    queue->rear = newNode;
}

// Function to dequeue a process from the queue
Process dequeue(Queue* queue) {
    if (isQueueEmpty(queue)) {
        Process emptyProcess = {-1, -1, -1, -1, -1, -1, -1};
        return emptyProcess;
    }

    Node* temp = queue->front;
    Process process = temp->data;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL;
    }

    free(temp);
    return process;
}

// Function to calculate completion time, turnaround time, waiting time, and response time
void calculateTimes(Process processes[], int n) {
    int current_time = 0;
    Queue* queue = createQueue();

    for (int i = 0; i < n; i++) {
        while (current_time < processes[i].arrival_time) {
            Process emptyProcess = {-1, -1, -1, -1, -1, -1, -1};
            enqueue(queue, emptyProcess);
            current_time++;
        }

        enqueue(queue, processes[i]);
        current_time += processes[i].burst_time;

        processes[i].completion_time = current_time;
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        processes[i].response_time = processes[i].waiting_time; // FCFS has the same response time as waiting time
    }

    while (!isQueueEmpty(queue)) {
        dequeue(queue);
        current_time++;
    }

    free(queue);
}

// Function to print the FCFS schedule and compute average waiting time and average turnaround time
void printScheduleAndComputeAverage(Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    printf("\nP_id\tAT\tBT\tCT\tTAT\tWT\tRT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n", processes[i].p_id, processes[i].arrival_time, processes[i].burst_time,
               processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time,
               processes[i].response_time);

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("\nAvg waiting time: %lf\n", (double)total_waiting_time / n);
    printf("Avg turnaround time: %lf\n", (double)total_turnaround_time / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    Process* processes = (Process*)malloc(n * sizeof(Process));

    printf("Enter Process ID, Arrival Time, and Burst Time for each process:\n");

    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].p_id, &processes[i].arrival_time, &processes[i].burst_time);
    }

    calculateTimes(processes, n);

    printf("\nFCFS Schedule\n");
    printScheduleAndComputeAverage(processes, n);

    free(processes);

    return 0;
}