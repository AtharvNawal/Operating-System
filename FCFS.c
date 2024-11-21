#include <stdio.h>

struct Process {
    int pid;           // Process ID
    int arrivalTime;   // Arrival time
    int burstTime;     // Burst time
    int finishTime;    // Finish time
    int turnaroundTime;// Turnaround time
    int waitingTime;   // Waiting time
};

void calculateTimes(struct Process processes[], int n) {
    int currentTime = 0;
    
    for (int i = 0; i < n; i++) {
        // If the process arrives after the current time, update current time to its arrival
        if (currentTime < processes[i].arrivalTime) {
            currentTime = processes[i].arrivalTime;
        }

        // Calculate Finish Time
        processes[i].finishTime = currentTime + processes[i].burstTime;
        
        // Update current time to this process's finish time
        currentTime = processes[i].finishTime;

        // Calculate Turnaround Time (TAT = FT - AT)
        processes[i].turnaroundTime = processes[i].finishTime - processes[i].arrivalTime;
        
        // Calculate Waiting Time (WT = TAT - BT)
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
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

    // Calculate and display average Turnaround Time and Waiting Time
    float totalTurnaroundTime = 0, totalWaitingTime = 0;
    for (int i = 0; i < n; i++) {
        totalTurnaroundTime += processes[i].turnaroundTime;
        totalWaitingTime += processes[i].waitingTime;
    }
    
    printf("\nAverage Turnaround Time: %.2f", totalTurnaroundTime / n);
    printf("\nAverage Waiting Time: %.2f\n", totalWaitingTime / n);
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process %d: ", processes[i].pid);
        scanf("%d %d", &processes[i].arrivalTime, &processes[i].burstTime);
    }

    // Sort processes by Arrival Time (optional if processes are already ordered)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (processes[i].arrivalTime > processes[j].arrivalTime) {
                struct Process temp = processes[i];
                processes[i] = processes[j];
                processes[j] = temp;
            }
        }
    }

    // Calculate Finish Time, Turnaround Time, and Waiting Time
    calculateTimes(processes, n);

    // Print results
    printResults(processes, n);

    return 0;
}