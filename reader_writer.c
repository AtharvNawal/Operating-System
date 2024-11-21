#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

int data = 0;             
int read_count = 0;

sem_t wrt;                
pthread_mutex_t mutex;     


void* writer(void* arg) {
    sem_wait(&wrt);        
    
    data++;                
    printf("Writer is writing data: %d\n", data);

    sem_post(&wrt);        

    return NULL;
}

void* reader(void* arg) {
  
    pthread_mutex_lock(&mutex); 
    read_count++;
    if (read_count == 1) {
        sem_wait(&wrt);    
     }
    pthread_mutex_unlock(&mutex);

    printf("Reader is reading data: %d\n", data);

    pthread_mutex_lock(&mutex); 
    read_count--;
    if (read_count == 0) {
        sem_post(&wrt);  
    }
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main() {
    pthread_t readers[5], writers[5];

    sem_init(&wrt, 0, 1);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, NULL);
        pthread_create(&writers[i], NULL, writer, NULL);
    }
    
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&wrt);
    pthread_mutex_destroy(&mutex);

    return 0;
}