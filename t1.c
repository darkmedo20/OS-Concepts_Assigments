#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Required for memset

// Structure to represent a process
typedef struct Process {
    int pid;            // Process ID
    int burst_time;     // Original burst time
    int remaining_time; // Remaining burst time
    int arrival_time;   // Arrival time (for future tasks, initialized to 0 here)
    int completion_time; // Time when process finishes
    int waiting_time;   // Time process waits in ready queue
    int turnaround_time; // Time from arrival to completion
    int start_time;     // Time when process first starts execution
    int has_started;    // Flag to check if process has started
} Process;

// Function to simulate Round Robin scheduling
void roundRobin(Process processes[], int n, int time_quantum) {
    // Initialize remaining_time for all processes
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].arrival_time = 0; // For this task, assume all arrive at time 0
        processes[i].completion_time = 0;
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
        processes[i].start_time = -1; // -1 indicates not yet started
        processes[i].has_started = 0;
    }

    // Queue for processes ready to execute
    int queue[n];
    int front = 0, rear = 0;

    // Add all processes to the queue initially (since arrival_time is 0 for all)
    for (int i = 0; i < n; i++) {
        queue[rear++] = i; // Store index of the process
    }

    int current_time = 0;
    int completed_processes = 0;

    printf("Gantt Chart:\n");
    printf("-------------------------------------------------------------------\n");

    // Loop until all processes are completed
    while (completed_processes < n) {
        if (front == rear) { // If queue is empty (should not happen if all arrive at 0 and have burst time > 0)
            current_time++;
            continue;
        }

        int current_process_index = queue[front++]; // Dequeue a process
        Process *p = &processes[current_process_index];

        // If process has not started yet, record its start time
        if (p->has_started == 0) {
            p->start_time = current_time;
            p->has_started = 1;
        }

        int execution_time = (p->remaining_time < time_quantum) ? p->remaining_time : time_quantum;

        printf("| P%d (%dms) ", p->pid, current_time); // Mark start of execution for this slice

        p->remaining_time -= execution_time;
        current_time += execution_time;

        printf("-> %dms ", current_time); // Mark end of execution for this slice

        if (p->remaining_time == 0) {
            p->completion_time = current_time;
            p->turnaround_time = p->completion_time - p->arrival_time;
            p->waiting_time = p->turnaround_time - p->burst_time;
            completed_processes++;
        } else {
            // If not completed, add back to the end of the queue
            queue[rear++] = current_process_index;
        }
    }
    printf("|\n");
    printf("-------------------------------------------------------------------\n\n");

    // Display results
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    printf("-------------------------------------------------------------------\n");
    float total_waiting_time = 0;
    float total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        printf("P%d\t%dms\t\t%dms\t\t%dms\n",
               processes[i].pid,
               processes[i].burst_time,
               processes[i].waiting_time,
               processes[i].turnaround_time);
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("-------------------------------------------------------------------\n");
    printf("Average Waiting Time: %.2fms\n", total_waiting_time / n);
    printf("Average Turnaround Time: %.2fms\n", total_turnaround_time / n);
}

int main() {
    int n; // Number of processes
    int time_quantum = 4; // Fixed time quantum for this task

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Dynamically allocate memory for processes
    Process *processes = (Process *)malloc(n * sizeof(Process));
    if (processes == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    printf("Enter burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("P%d Burst Time: ", processes[i].pid);
        scanf("%d", &processes[i].burst_time);
    }

    printf("\nSimulating Round Robin with Time Quantum = %dms\n\n", time_quantum);
    roundRobin(processes, n, time_quantum);

    // Free dynamically allocated memory
    free(processes);
    processes = NULL;

    return 0;
}
