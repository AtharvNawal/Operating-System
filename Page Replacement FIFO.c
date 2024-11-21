#include <stdio.h>

void fifo(int ref[], int n, int frames) {
    int frame[frames], page_faults = 0, index = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    printf("\nFIFO Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            frame[index] = ref[i];
            index = (index + 1) % frames;
            page_faults++;
        }
        printf("Page %d: ", ref[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (FIFO): %d\n", page_faults);
}

int main() {
    int n, frames;
    printf("Enter number of pages in the reference string: ");
    scanf("%d", &n);
    int ref[n];
    printf("Enter the reference string: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &ref[i]);
    }
    printf("Enter number of frames: ");
    scanf("%d", &frames);

    fifo(ref, n, frames);

    return 0;
}