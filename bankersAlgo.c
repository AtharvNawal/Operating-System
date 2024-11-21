//Bankers algo - manage resources in a way to avoid deadlocks
// All systems in safe state 
#include <stdio.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int main() {
    int n, m, i, j, k;
    int allocation[MAX_PROCESSES][MAX_RESOURCES], //resources currently allocated to each process
        max[MAX_PROCESSES][MAX_RESOURCES],  //maximum demand
        available[MAX_RESOURCES];  //available number of resources of each type
    int need[MAX_PROCESSES][MAX_RESOURCES];  //more resources each process needs to complete its task
    int completed[MAX_PROCESSES] = {0}, safe_sequence[MAX_PROCESSES];
    int count = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);

    printf("Enter the allocation matrix:\n");  // how many resources of each type are currently allocated to each process
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the max matrix:\n");  // maximum demand of each process for resources
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resources: ");  // how many resources of each type are currently available.
    for (i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    for (i = 0; i < n; i++) { 
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];  //resources of each type process i required to finish
        }
    }

    // Banker's Algorithm
    while (count < n) {
        int found = 0;
        for (i = 0; i < n; i++) {
            if (completed[i] == 0) {  // If process i is not yet completed
                int can_allocate = 1;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > available[j]) {  // need[i][j] <= available[j] added to safe sequence
                        can_allocate = 0;
                        break;
                    }
                }

                if (can_allocate) {
                    for (k = 0; k < m; k++) {
                        available[k] += allocation[i][k];
                    }
                    safe_sequence[count++] = i;
                    completed[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("The system is in an unsafe state.\n");  // at any iteration, no process can be executed
            return 0;
        }
    }

    printf("The system is in a safe state.\n");   // process can execute without leading to deadlock
    printf("Safe sequence: ");
    for (i = 0; i < n; i++) {
        printf("P%d ", safe_sequence[i]);
    }
    printf("\n");

    return 0;
}

/*
OUTPUT

Enter the number of processes: 5
Enter the number of resources: 3
Enter the allocation matrix:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
Enter the max matrix:
7 5 3                    
3 2 2
9 0 2
2 2 2
4 3 3
Enter the available resources: 3 3 2
The system is in a safe state.
Safe sequence: P1 P3 P4 P0 P2
*/