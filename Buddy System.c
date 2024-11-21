#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    int first;
    int second;
} Pair;

int size;


Pair* free_list[100000];
int free_list_count[100000];

int mp[100000];

void initialize(int sz) {
    int n = ceil(log(sz) / log(2));
    size = n + 1;

    for (int i = 0; i <= n; i++) {
        free_list[i] = NULL;
        free_list_count[i] = 0;
    }

    free_list[n] = (Pair *)malloc(sizeof(Pair));
    free_list[n][0].first = 0;
    free_list[n][0].second = sz - 1;
    free_list_count[n] = 1;
}

void allocate(int sz) {
    int n = ceil(log(sz) / log(2));


    if (free_list_count[n] > 0) {
        Pair temp = free_list[n][0];

        for (int i = 1; i < free_list_count[n]; i++) {
            free_list[n][i - 1] = free_list[n][i];
        }
        free_list_count[n]--;

        printf("Memory from %d to %d allocated\n", temp.first, temp.second);


        mp[temp.first] = temp.second - temp.first + 1;
    }
    else {
        int i;
        for (i = n + 1; i < size; i++) {
            if (free_list_count[i] > 0)
                break;
        }

        if (i == size) {
            printf("Sorry, failed to allocate memory\n");
            return;
        }

        for (; i > n; i--) {
            Pair temp = free_list[i][0];
            for (int j = 1; j < free_list_count[i]; j++) {
                free_list[i][j - 1] = free_list[i][j];
            }
            free_list_count[i]--;


            Pair pair1 = { temp.first, temp.first + (temp.second - temp.first) / 2 };
            Pair pair2 = { temp.first + (temp.second - temp.first + 1) / 2, temp.second };

            free_list[i - 1] = (Pair *)realloc(free_list[i - 1], (free_list_count[i - 1] + 2) * sizeof(Pair));
            free_list[i - 1][free_list_count[i - 1]] = pair1;
            free_list[i - 1][free_list_count[i - 1] + 1] = pair2;
            free_list_count[i - 1] += 2;
        }

        Pair temp = free_list[n][0];

        for (int i = 1; i < free_list_count[n]; i++) {
            free_list[n][i - 1] = free_list[n][i];
        }
        free_list_count[n]--;

        printf("Memory from %d to %d allocated\n", temp.first, temp.second);
        mp[temp.first] = temp.second - temp.first + 1;
    }
}

int main() {
    initialize(128);
    int choice,size;
    while(1){
            printf("Enter 1 for allocation and 2 for exit\n");
            scanf("%d",&choice);
            switch(choice){
                case 1:
                printf("Enter size: ");
                scanf("%d",&size);
                allocate(size);
                break;

                case 2:
                exit(1);
                default:
                printf("invalid");
                }
    }
    // Test memory allocation
   /* allocate(32);
    allocate(7);
    allocate(64);
    allocate(56);
*/
    return 0;
}