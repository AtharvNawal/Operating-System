#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE];  
int in = 0; 
int out = 0; 
int pcount = 0;  // Produced item count
int ccount = 0;  // Consumed item count

sem_t mutex;  // Semaphore to ensure mutual exclusion
sem_t full;   // Semaphore to count full slots in the buffer
sem_t empty;  // Semaphore to count empty slots in the buffer

void *producer(void *arg) {
    int item = 1;  

    while (pcount < MAX_ITEMS) {
        sem_wait(&empty);  // Wait if buffer is full
        sem_wait(&mutex);  // Lock the buffer access

        buffer[in] = item;  // Add item to the buffer
        printf("Produced: %d\n", item);
        item++;
        in = (in + 1) % BUFFER_SIZE;  // Update index for next production
        pcount++; 

        sem_post(&mutex);  // Unlock buffer access
        sem_post(&full);   // Signal that buffer now has one more full slot
    }

    pthread_exit(NULL); 
}

void *consumer(void *arg) {
    while (ccount < MAX_ITEMS) {
        sem_wait(&full);   // Wait if buffer is empty
        sem_wait(&mutex);  // Lock buffer access

        int item = buffer[out];  // Remove item from the buffer
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;  // Update index for next consumption
        ccount++; 

        sem_post(&mutex);  // Unlock buffer access
        sem_post(&empty);  // Signal that buffer has one more empty slot
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producerThread, consumerThread;

    // Initialize semaphores
    sem_init(&mutex, 0, 1);       // Mutex with initial value 1 for mutual exclusion
    sem_init(&full, 0, 0);        // Initially, buffer is empty, so full slots = 0
    sem_init(&empty, 0, BUFFER_SIZE);  // Initially, buffer has all slots empty

    // Create producer and consumer threads
    pthread_create(&producerThread, NULL, producer, NULL);
    pthread_create(&consumerThread, NULL, consumer, NULL);

    // Wait for both threads to finish
    pthread_join(producerThread, NULL);
    pthread_join(consumerThread, NULL);

    // Destroy the semaphores
    sem_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);

    return 0;
}