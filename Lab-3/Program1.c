/*
1. Write a C program to implement the Shortest Job First Scheduling Algorithm.
(i) Take input from the user only once (Process_id, Arrival Time, Burst Time) and apply SJF.
(ii) Your algorithm should work for both scenarios: (a) all tasks arrive at the same time (b) tasks may arrive at a different time.
(iii) Compute completion time, turnaround time,  waiting time and response time for each process  for the given input.
(iv) Further compute the average waiting time and average turnaround time.
(v) Print the schedule for the given input.
Note: You can use only integers for process id. Use the min heap data structure (using linked list) to implement SJF Queue.
*/

#include <stdio.h>
#include <stdlib.h>

// Structure to represent a process
struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
};

// Structure to represent a node in the min heap
struct MinHeapNode {
    struct Process* process;
    struct MinHeapNode* next;
};

// Structure to represent the min heap
struct MinHeap {
    struct MinHeapNode* head;
};

// Function to create a new process
struct Process* createProcess(int pid, int arrival, int burst) {
    struct Process* process = (struct Process*)malloc(sizeof(struct Process));
    process->process_id = pid;
    process->arrival_time = arrival;
    process->burst_time = burst;
    return process;
}

// Function to create a new min heap node
struct MinHeapNode* createMinHeapNode(struct Process* process) {
    struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node->process = process;
    node->next = NULL;
    return node;
}

// Function to insert a process into the min heap
void insertProcess(struct MinHeap* heap, struct Process* process) {
    struct MinHeapNode* node = createMinHeapNode(process);
    if (heap->head == NULL) {
        heap->head = node;
    } else {
        struct MinHeapNode* curr = heap->head;
        struct MinHeapNode* prev = NULL;
        while (curr != NULL && curr->process->burst_time < process->burst_time) {
            prev = curr;
            curr = curr->next;
        }
        if (prev == NULL) {
            node->next = heap->head;
            heap->head = node;
        } else {
            prev->next = node;
            node->next = curr;
        }
    }
}

// Function to remove and return the process with the shortest burst time
struct Process* removeShortestJob(struct MinHeap* heap) {
    if (heap->head == NULL) {
        return NULL;
    }
    struct MinHeapNode* temp = heap->head;
    heap->head = heap->head->next;
    struct Process* process = temp->process;
    free(temp);
    return process;
}

int main() {
    int num_processes;
    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    struct MinHeap heap;
    heap.head = NULL;

    for (int i = 0; i < num_processes; ++i) {
        int pid, arrival, burst;
        printf("Enter details for process %d:\n", i + 1);
        printf("Process ID: ");
        scanf("%d", &pid);
        printf("Arrival Time: ");
        scanf("%d", &arrival);
        printf("Burst Time: ");
        scanf("%d", &burst);

        struct Process* process = createProcess(pid, arrival, burst);
        insertProcess(&heap, process);
    }

    int current_time = 0;
    float total_turnaround_time = 0.0;
    float total_waiting_time = 0.0;

    printf("\nProcess Schedule:\n");
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");

    while (heap.head != NULL) {
        struct Process* current_process = removeShortestJob(&heap);
        current_time = current_time > current_process->arrival_time ? current_time : current_process->arrival_time;
        int completion_time = current_time + current_process->burst_time;
        int turnaround_time = completion_time - current_process->arrival_time;
        int waiting_time = turnaround_time - current_process->burst_time;

        printf("%d\t%d\t%d\t%d\t\t%d\t\t%d\n", current_process->process_id, current_process->arrival_time, current_process->burst_time, completion_time, turnaround_time, waiting_time);

        total_turnaround_time += turnaround_time;
        total_waiting_time += waiting_time;

        current_time = completion_time;
    }

    float avg_turnaround_time = total_turnaround_time / num_processes;
    float avg_waiting_time = total_waiting_time / num_processes;

    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);

    return 0;
}