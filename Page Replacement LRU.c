#include <stdio.h>

void lru(int ref[], int n, int frames) {
    int frame[frames], page_faults = 0, time[frames], least, found;
    for (int i = 0; i < frames; i++) frame[i] = -1;
    for (int i = 0; i < frames; i++) time[i] = -1;
    printf("\nLRU Page Replacement:\n");
    for (int i = 0; i < n; i++) {
        found = 0;
        for (int j = 0; j < frames; j++) {
            if (frame[j] == ref[i]) {
                found = 1;
                time[j] = i;
                break;
            }
        }
        if (!found) {
            least = 0;
            for (int j = 1; j < frames; j++) {
                if (time[j] < time[least]) least = j;
            }
            frame[least] = ref[i];
            time[least] = i;
            page_faults++;
        }
        printf("Page %d: ", ref[i]);
        for (int j = 0; j < frames; j++) {
            if (frame[j] != -1) printf("%d ", frame[j]);
            else printf("- ");
        }
        printf("\n");
    }
    printf("Total Page Faults (LRU): %d\n", page_faults);
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

    lru(ref, n, frames);

    return 0;
}