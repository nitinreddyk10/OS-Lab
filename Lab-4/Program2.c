/*
 Write a C program to implement round-robin scheduling.
(i)Take input from the user as P_id, arrival time, burst Time, and time quantum.
(ii) Show the turnaround time, waiting time, and response time for each task.
(iii) Compute average turnaround time, waiting time, and response time.
(iv) Count the number of context switches (excluding the count at the beginning of the first execution process and the end of the last execution process)
(v) Your algorithm should work for both the scenario: (a) all tasks arrive at the same time (b) tasks may arrive at a different time
*/

#include <stdio.h>
#include <stdlib.h>

struct Process {
    int p_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

void round_robin_scheduling(struct Process processes[], int n, int time_quantum) {
    int current_time = 0;
    int completed = 0;
    int context_switches = 0;
    int *queue = malloc(n * sizeof(int));
    int front = 0, rear = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                queue[rear] = i;
                rear = (rear + 1) % n;
            }
        }

        if (front == rear) {
            current_time++;
            continue;
        }

        int current_process_index = queue[front];
        front = (front + 1) % n;
        struct Process *current_process = &processes[current_process_index];

        if (current_process->response_time == -1) {
            current_process->response_time = current_time - current_process->arrival_time;
        }

        if (current_process->remaining_time <= time_quantum) {
            current_time += current_process->remaining_time;
            current_process->remaining_time = 0;
            current_process->turnaround_time = current_time - current_process->arrival_time;
            current_process->waiting_time = current_process->turnaround_time - current_process->burst_time;
            completed++;
        } else {
            current_time += time_quantum;
            current_process->remaining_time -= time_quantum;
        }

        context_switches++;
    }

    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    for (int i = 0; i < n; i++) {
        total_turnaround_time += processes[i].turnaround_time;
        total_waiting_time += processes[i].waiting_time;
        total_response_time += processes[i].response_time;
    }
    double average_turnaround_time = (double)total_turnaround_time / n;
    double average_waiting_time = (double)total_waiting_time / n;
    double average_response_time = (double)total_response_time / n;

    printf("P_ID\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\n", processes[i].p_id, processes[i].turnaround_time,
               processes[i].waiting_time, processes[i].response_time);
    }

    printf("\nAverage Turnaround Time: %.2lf\n", average_turnaround_time);
    printf("Average Waiting Time: %.2lf\n", average_waiting_time);
    printf("Average Response Time: %.2lf\n", average_response_time);
    printf("Context Switches: %d\n", context_switches);

    free(queue);
}

int main() {
    int n, time_quantum;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);

    struct Process *processes = malloc(n * sizeof(struct Process));
    for (int i = 0; i < n; i++) {
        printf("Enter details for process %d:\n", i + 1);
        processes[i].p_id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].turnaround_time = 0;
        processes[i].waiting_time = 0;
        processes[i].response_time = -1;
    }

    round_robin_scheduling(processes, n, time_quantum);

    free(processes);

    return 0;
}