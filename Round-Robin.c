#include <stdio.h>

struct Process {
    int pid;            // Process ID
    int arrivalTime;    // Arrival Time
    int burstTime;      // Burst Time
    int remainingTime;  // Remaining Time after each time slice
    int finishTime;     // Finish Time
    int turnaroundTime; // Turnaround Time
    int waitingTime;    // Waiting Time
};

void calculateRoundRobin(struct Process processes[], int n, int timeQuantum) {
    int currentTime = 0;   // Current time in the system
    int completed = 0;     // Number of completed processes
    int i = 0;             // Process index for Round Robin rotation

    while (completed < n) {
        // Only process tasks that have remaining time
        if (processes[i].remainingTime > 0 && processes[i].arrivalTime <= currentTime) {
            // Process the current task for either the time quantum or its remaining time
            int timeSlice = (processes[i].remainingTime > timeQuantum) ? timeQuantum : processes[i].remainingTime;

            // Advance time by the time slice
            currentTime += timeSlice;
            processes[i].remainingTime -= timeSlice;

            // If the process has completed, update its finish time and calculate turnaround and waiting times
            if (processes[i].remainingTime == 0) {
                processes[i].finishTime = currentTime;
                processes[i].turnaroundTime = processes[i].finishTime - processes[i].arrivalTime;
                processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
                completed++;  // Increment the completed process count
            }
        }

        // Move to the next process (wrap around with modulo for circular rotation)
        i = (i + 1) % n;

        // If no process was available to run, increment time to avoid infinite loop
        if (processes[i].remainingTime == 0 && processes[i].arrivalTime > currentTime) {
            currentTime++;
        }
    }
}

void printResults(struct Process processes[], int n) {
    printf("\nPID\tArrival\tBurst\tFinish\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].finishTime,
               processes[i].turnaroundTime,
               processes[i].waitingTime);
    }
}

int main() {
    int n, timeQuantum;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", processes[i].pid);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
        processes[i].remainingTime = processes[i].burstTime;  // Initialize remaining time
    }

    printf("Enter Time Quantum: ");
    scanf("%d", &timeQuantum);

    calculateRoundRobin(processes, n, timeQuantum);
    printResults(processes, n);

    return 0;
}