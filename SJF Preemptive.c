// Non- preemptive - Shortest job first (SJF) scheduling      [interrupte btw the current process]  - higher priority or shorter burst time
// Shortest Remaining Time First (SRTF)
// minimizing waiting time and turnaround time

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process {
    int pid;           // Process ID (unique identifier for each process)
    int AT;            // Arrival Time (when the process arrives in the ready queue)
    int BT;            // Burst Time (total CPU time required by the process)
    int remaining_BT;  // Remaining Burst Time (updates as process executes) - BT is left after preemption
    int ST;            // Start Time (when the process starts execution)
    int FT;            // Finish Time (when the process completes execution)
    int TT;            // Turnaround Time (total time in the system: TT = FT - AT)
    int WT;            // Waiting Time (time spent waiting: WT = TT - BT)
    int done;          // Completion flag (0 = not completed, 1 = completed)
};

int main() {
    int n;
    struct process p[100];
    float avg_TT = 0;
    float avg_WT = 0;
    int total_TT = 0;
    int total_WT = 0;
    int completed = 0;
    int currentTime = 0;
    int prev = -1; // track the previously executing process, track ST

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time of process %d: ", i + 1);
        scanf("%d", &p[i].AT);
        printf("Enter burst time of process %d: ", i + 1);
        scanf("%d", &p[i].BT);
        p[i].pid = i + 1;
        p[i].remaining_BT = p[i].BT; // process not executed yet
        p[i].done = 0; // Mmrk all processes as not completed
        printf("\n");
    }

    while (completed < n) {
        int idx = -1;
        int min_remaining_BT = INT_MAX;

        for (int i = 0; i < n; i++) {
            // Searches for shortest remaining BT that has already arrived and is not completed
            if (p[i].AT <= currentTime && p[i].done == 0 && p[i].remaining_BT < min_remaining_BT) {  
            idx = i;
            }
        }

        if (idx != -1) {
            if (prev != idx) {
                p[idx].ST = currentTime; // Process starts or resumes
            }

            p[idx].remaining_BT--; // 1 unit has been executed 
            currentTime++; 

            if (p[idx].remaining_BT == 0) { // Process is complete
                p[idx].FT = currentTime;
                p[idx].TT = p[idx].FT - p[idx].AT;
                p[idx].WT = p[idx].TT - p[idx].BT;
                total_TT += p[idx].TT;
                total_WT += p[idx].WT;
                p[idx].done = 1; // Mark process as completed
                completed++;
            }

            prev = idx; // Update the previously executing process
        } else {
            currentTime++; // No process is ready, move time forward
        }
    }

    avg_TT = (float)total_TT / n;
    avg_WT = (float)total_WT / n;

    printf("\nProcess\tAT\tBT\tFT\tTT\tWT\n\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].FT, p[i].TT, p[i].WT);
    }

    printf("Average Turnaround Time = %.2f\n", avg_TT);
    printf("Average Waiting Time = %.2f\n", avg_WT);

    return 0;
}

/*
OUTPUT-

Enter the number of processes: 4
Enter arrival time of process 1: 0
Enter burst time of process 1: 8

Enter arrival time of process 2: 1
Enter burst time of process 2: 4

Enter arrival time of process 3: 2
Enter burst time of process 3: 9

Enter arrival time of process 4: 3
Enter burst time of process 4: 5


Process AT      BT      FT      TT      WT

1       0       8       17      17      9
2       1       4       5       4       0
3       2       9       26      24      15
4       3       5       10      7       2
Average Turnaround Time = 13.00
Average Waiting Time = 6.50
*/