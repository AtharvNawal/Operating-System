#include <stdio.h>

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int finishTime;
    int turnaroundTime;
    int waitingTime;
    int completed;
};

void calculateNonPreemptivePriority(struct Process processes[], int n) {
    int currentTime = 0, completed = 0;

    while (completed < n) {
        int minIndex = -1;
        int minPriority = 1000000;  // Large number as the initial minimum priority

        // Find the process with the highest priority (smallest number) that has arrived and is not completed
        for (int i = 0; i < n; i++) {
            if (processes[i].arrivalTime <= currentTime && !processes[i].completed && processes[i].priority < minPriority) {
                minPriority = processes[i].priority;
                minIndex = i;
            }
        }

        if (minIndex == -1) {  // If no process is available, increment time
            currentTime++;
        } else {
            // Update times for selected process
            processes[minIndex].finishTime = currentTime + processes[minIndex].burstTime;
            processes[minIndex].turnaroundTime = processes[minIndex].finishTime - processes[minIndex].arrivalTime;
            processes[minIndex].waitingTime = processes[minIndex].turnaroundTime - processes[minIndex].burstTime;
            processes[minIndex].completed = 1;

            currentTime = processes[minIndex].finishTime;
            completed++;
        }
    }
}

void printResults(struct Process processes[], int n) {
    printf("\nPID\tArrival\tBurst\tPriority\tFinish\tTurnaround\tWaiting\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t\t%d\t%d\t\t%d\n",
               processes[i].pid,
               processes[i].arrivalTime,
               processes[i].burstTime,
               processes[i].priority,
               processes[i].finishTime,
               processes[i].turnaroundTime,
               processes[i].waitingTime);
    }
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter Arrival Time, Burst Time, and Priority for Process %d: ", processes[i].pid);
        scanf("%d %d %d", &processes[i].arrivalTime, &processes[i].burstTime, &processes[i].priority);
        processes[i].completed = 0;
    }

    calculateNonPreemptivePriority(processes, n);
    printResults(processes, n);

    return 0;
}