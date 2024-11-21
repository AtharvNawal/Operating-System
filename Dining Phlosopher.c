#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

sem_t forks[NUM_PHILOSOPHERS]; 

void* philosopher(void* num) {
    int id = *(int*)num;

    while (1) {
        
        printf("Philosopher %d is thinking.\n", id);
        sleep(1); 

        sem_wait(&forks[id]); 
        printf("Philosopher %d picked up left fork %d.\n", id, id);
        
        sem_wait(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d picked up right fork %d.\n", id, (id + 1) % NUM_PHILOSOPHERS);

        printf("Philosopher %d is eating.\n", id);
        sleep(1); 

        sem_post(&forks[(id + 1) % NUM_PHILOSOPHERS]);
        printf("Philosopher %d put down right fork %d.\n", id, (id + 1) % NUM_PHILOSOPHERS);

        sem_post(&forks[id]);
        printf("Philosopher %d put down left fork %d.\n", id, id);
    }
    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&forks[i], 0, 1);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&forks[i]);
    }

    return 0;
}