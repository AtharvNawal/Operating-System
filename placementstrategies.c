/*Enter the number of memory blocks: 5
Enter the size of each memory block:
Block 1: 100
Block 2: 500
Block 3: 200
Block 4: 300
Block 5: 600

Enter the number of processes: 4
Enter the size of each process:
Process 1: 212
Process 2: 417
Process 3: 112
Process 4: 426*/

#include <stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }
    printf("\nFirst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to block %d\n", i+1, allocation[i]+1);
        else
            printf("Process %d not allocated\n", i+1);
    }
}

void bestFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        int bestIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (bestIdx == -1 || blockSize[j] < blockSize[bestIdx]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            blockSize[bestIdx] -= processSize[i];
        }
    }
    printf("\nBest Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to block %d\n", i+1, allocation[i]+1);
        else
            printf("Process %d not allocated\n", i+1);
    }
}

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }
        if (worstIdx != -1) {
            allocation[i] = worstIdx;
            blockSize[worstIdx] -= processSize[i];
        }
    }
    printf("\nWorst Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to block %d\n", i+1, allocation[i]+1);
        else
            printf("Process %d not allocated\n", i+1);
    }
}

void nextFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    int lastAllocated = 0;
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        int j = lastAllocated;
        do {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                lastAllocated = j;
                break;
            }
            j = (j + 1) % m;
        } while (j != lastAllocated);
    }
    printf("\nNext Fit Allocation:\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("Process %d allocated to block %d\n", i+1, allocation[i]+1);
        else
            printf("Process %d not allocated\n", i+1);
    }
}

int main() {
    int m, n;
    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    int blockSize[m];
    printf("Enter the size of each memory block:\n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i+1);
        scanf("%d", &blockSize[i]);
    }
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);
    int processSize[n];
    printf("Enter the size of each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i+1);
        scanf("%d", &processSize[i]);
    }
    int blockSizeCopy1[m], blockSizeCopy2[m], blockSizeCopy3[m], blockSizeCopy4[m];
    for (int i = 0; i < m; i++) {
        blockSizeCopy1[i] = blockSize[i];
        blockSizeCopy2[i] = blockSize[i];
        blockSizeCopy3[i] = blockSize[i];
        blockSizeCopy4[i] = blockSize[i];
    }
    firstFit(blockSizeCopy1, m, processSize, n);
    bestFit(blockSizeCopy2, m, processSize, n);
    worstFit(blockSizeCopy3, m, processSize, n);
    nextFit(blockSizeCopy4, m, processSize, n);
    return 0;
}
