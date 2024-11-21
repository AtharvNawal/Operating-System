#include <stdio.h>
#include <stdbool.h>
#define MAX 100

int req[MAX][MAX];
int alloc[MAX][MAX];
int avail[MAX];
int work[MAX];
bool finish[MAX];
int n, r;

void input() {
    int i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the number of resources: ");
    scanf("%d", &r);

    printf("Enter the allocation matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    printf("Enter the request matrix:\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < r; j++) {
            scanf("%d", &req[i][j]);
        }
    }

    printf("Enter the available resources: ");
    for (j = 0; j < r; j++) {
        scanf("%d", &avail[j]);
    }
}

void show_matrix() {
    int i, j;
    printf("Process\t Allocation\t Request\t Available\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t ", i + 1);
        for (j = 0; j < r; j++) {
            printf("%d ", alloc[i][j]);
        }
        printf("\t\t");
        for (j = 0; j < r; j++) {
            printf("%d ", req[i][j]);
        }
        if (i == 0) {
            printf("\t\t");
            for (j = 0; j < r; j++) {
                printf("%d ", avail[j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void cal() {
    int i, j;
    int executed = 0;
    int executionOrder[MAX];

    for (j = 0; j < r; j++) {
        work[j] = avail[j];
    }

    for (i = 0; i < n; i++) {
        finish[i] = false;
    }

    printf("\nInitial State of the system:\n");
    show_matrix();

    while (executed < n) {
        bool found = false;

        for (i = 0; i < n; i++) {
            if (!finish[i]) {
                bool canProceed = true;

                for (j = 0; j < r; j++) {
                    if (req[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    printf("Process P%d is executing.\n", i + 1);
                    for (j = 0; j < r; j++) {
                        work[j] += alloc[i][j];
                        alloc[i][j] = 0;
                        req[i][j] = 0;
                    }

                    for (j = 0; j < r; j++) {
                        avail[j] = work[j];
                    }

                    finish[i] = true;
                    executionOrder[executed] = i + 1;
                    executed++;
                    found = true;

                    printf("\nState of the system after process P%d execution:\n", i + 1);
                    show_matrix();
                }
            }
        }

        if (!found) {
            printf("System is in deadlock.\n");
            return;
        }
    }

    printf("\nSystem is in a safe state.\nExecution order of processes: ");
    for (i = 0; i < executed; i++) {
        printf("P%d ", executionOrder[i]);
    }
    printf("\n");
}

int main() {
    input();
    cal();
    return 0;
}