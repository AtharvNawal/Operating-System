// Non- preemptive - Shortest job first (SJF) scheduling      [cannot be interrupted]
// Selects the process with the shortest burst time (BT)
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process {
    int pid;    // Process ID (unique identifier for each process)
    int AT;     // Arrival Time (time at which the process arrives in the ready queue)
    int BT;     // Burst Time (time the process needs for execution)
    int ST;     // Start Time (time at which the process starts execution)
    int FT;     // Finish Time (time at which the process completes execution)
    int TT;     // Turnaround Time (total time the process spends in the system: TT = FT - AT)
    int WT;     // Waiting Time (time spent waiting in the ready queue: WT = TT - BT)
    int done;   // Flag to check if the process is completed (0 = not completed, 1 = completed)
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

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++) {
        printf("Enter arrival time of process %d: ", i+1);
        scanf("%d", &p[i].AT);
        printf("Enter burst time of process %d: ", i+1);
        scanf("%d", &p[i].BT);
        p[i].pid = i+1;
        p[i].done = 0; // Marked all process not completed
        printf("\n");
    }

    while(completed < n) {
        int idx = -1;
        int min_BT = INT_MAX;

        // shortest BT
        for(int i = 0; i < n; i++) {
            if(p[i].AT <= currentTime && p[i].done == 0 && p[i].BT < min_BT) {  // BT among the processes that have arrived (AT <= currentTime) and are not completed (done == 0).
                min_BT = p[i].BT;
                idx = i;   // idx - index of the process with the smallest BT
            }
        }

        if(idx != -1) {
            p[idx].ST = currentTime;
            p[idx].FT = p[idx].ST + p[idx].BT;
            p[idx].TT = p[idx].FT - p[idx].AT;
            p[idx].WT = p[idx].TT - p[idx].BT;
            currentTime = p[idx].FT;
            
            p[idx].done = 1; // Mark process as completed
            total_TT = total_TT + p[idx].TT;
            total_WT = total_WT + p[idx].WT;
            completed++;
        } else {
            currentTime++; // If no process has arrived, increment time
        }
    }

    avg_TT = (float) total_TT / n;
    avg_WT = (float) total_WT / n;

    printf("\nProcess\tAT\tBT\tFT\tTT\tWT\n\n");

    for(int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].AT, p[i].BT, p[i].FT, p[i].TT, p[i].WT);
    }

    printf("Average Turnaround Time = %.2f\n", avg_TT);
    printf("Average Waiting Time = %.2f\n", avg_WT);

    return 0;
}