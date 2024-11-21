/*Enter the size of disk: 200
Enter the number of requests: 8
Enter the request sequence:
87
160
40
140
36
72
66
15
Enter the initial head position: 60*/
// minimize seek time - 
#include <stdio.h>
#include <stdlib.h>
#define MAX 100

void FCFS(int request[], int n, int head);
void SSTF(int request[], int n, int head);
void SCAN(int request[], int n, int head, int disk_size);
void CSCAN(int request[], int n, int head, int disk_size);

int main() {
    int n, head, disk_size, choice;
    int request[MAX];

    printf("Enter the size of disk: ");
    scanf("%d", &disk_size);
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    printf("Enter the request sequence:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request[i]);
    }
    printf("Enter the initial head position: ");
    scanf("%d", &head);
    printf("\nDisk Scheduling Algorithms:\n");
    printf("1. FCFS\n2. SSTF\n3. SCAN\n4. C-SCAN\nEnter your choice: ");
    scanf("%d", &choice);

    switch(choice) {
        case 1: FCFS(request, n, head); break;
        case 2: SSTF(request, n, head); break;
        case 3: SCAN(request, n, head, disk_size); break;
        case 4: CSCAN(request, n, head, disk_size); break;
        default: printf("Invalid choice!\n");
    }
    return 0;
}

void FCFS(int request[], int n, int head) {
    int seek_time = 0;
    printf("\nFCFS Disk Scheduling\n");
    for (int i = 0; i < n; i++) {
        seek_time += abs(request[i] - head);
        printf("Move from %d to %d with seek %d\n", head, request[i], abs(request[i] - head));
        head = request[i];
    }
    printf("Total Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);
}

void SSTF(int request[], int n, int head) {
    int seek_time = 0, done[MAX] = {0}, count = 0, min, diff, index;
    printf("\nSSTF Disk Scheduling\n");
    while (count < n) {
        min = 1e9;
        for (int i = 0; i < n; i++) {
            if (!done[i]) {
                diff = abs(request[i] - head);
                if (diff < min) {
                    min = diff;
                    index = i;
                }
            }
        }
        seek_time += min;
        printf("Move from %d to %d with seek %d\n", head, request[index], min);
        head = request[index];
        done[index] = 1;
        count++;
    }
    printf("Total Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);
}

void SCAN(int request[], int n, int head, int disk_size) {
    int seek_time = 0, i;
    int sorted_requests[MAX + 2];
    int sorted_n = n + 1;
    for (i = 0; i < n; i++) {
        sorted_requests[i] = request[i];
    }
    sorted_requests[n] = 0;
    for (i = 0; i < sorted_n - 1; i++) {
        for (int j = i + 1; j < sorted_n; j++) {
            if (sorted_requests[i] > sorted_requests[j]) {
                int temp = sorted_requests[i];
                sorted_requests[i] = sorted_requests[j];
                sorted_requests[j] = temp;
            }
        }
    }
    int head_index = 0;
    for (i = 0; i < sorted_n; i++) {
        if (sorted_requests[i] >= head) {
            head_index = i;
            break;
        }
    }
    for (i = head_index; i < sorted_n; i++) {
        seek_time += abs(sorted_requests[i] - head);
        printf("Move from %d to %d with seek %d\n", head, sorted_requests[i], abs(sorted_requests[i] - head));
        head = sorted_requests[i];
    }
    for (i = head_index - 1; i >= 0; i--) {
        seek_time += abs(sorted_requests[i] - head);
        printf("Move from %d to %d with seek %d\n", head, sorted_requests[i], abs(sorted_requests[i] - head));
        head = sorted_requests[i];
    }
    printf("Total Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);
}

void CSCAN(int request[], int n, int head, int disk_size) {
    int seek_time = 0, i;
    int sorted_requests[MAX + 2];
    int sorted_n = n + 2;
    for (i = 0; i < n; i++) {
        sorted_requests[i] = request[i];
    }
    sorted_requests[n] = 0;
    sorted_requests[n + 1] = disk_size - 1;
    for (i = 0; i < sorted_n - 1; i++) {
        for (int j = i + 1; j < sorted_n; j++) {
            if (sorted_requests[i] > sorted_requests[j]) {
                int temp = sorted_requests[i];
                sorted_requests[i] = sorted_requests[j];
                sorted_requests[j] = temp;
            }
        }
    }
    int head_index = 0;
    for (i = 0; i < sorted_n; i++) {
        if (sorted_requests[i] >= head) {
            head_index = i;
            break;
        }
    }
    for (i = head_index; i < sorted_n; i++) {
        seek_time += abs(sorted_requests[i] - head);
        printf("Move from %d to %d with seek %d\n", head, sorted_requests[i], abs(sorted_requests[i] - head));
        head = sorted_requests[i];
    }
    head = 0;
    seek_time += (disk_size - 1);
    printf("Move from %d to %d with seek %d\n", disk_size - 1, head, disk_size - 1);
    for (i = 0; i < head_index; i++) {
        seek_time += abs(sorted_requests[i] - head);
        printf("Move from %d to %d with seek %d\n", head, sorted_requests[i], abs(sorted_requests[i] - head));
        head = sorted_requests[i];
    }
    printf("Total Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);
}
