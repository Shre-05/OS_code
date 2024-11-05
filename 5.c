#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define SIZE 5  // Size of the buffer

int buffer[SIZE];
int items = 0;  // Number of items in the buffer

// Semaphores and Mutex
sem_t empty;   // Tracks empty slots in the buffer
sem_t full;    // Tracks filled slots in the buffer
pthread_mutex_t lock;  // Mutex for critical section

// Producer function
void* producer(void* arg) {
    int item = 1;  // Start producing items from 1
    while (1) {
        sem_wait(&empty);  // Wait if buffer is full
        pthread_mutex_lock(&lock);  // Lock critical section

        // Add item to the buffer
        buffer[items] = item;
        items++;
        printf("Producer produced: %d\n", item);
        item++;  // Increment item for next production

        pthread_mutex_unlock(&lock);  // Unlock critical section
        sem_post(&full);  // Signal that buffer has a new item

        sleep(1);  // Simulate production time
    }
}

// Consumer function
void* consumer(void* arg) {
    int item;
    while (1) {
        sem_wait(&full);  // Wait if buffer is empty
        pthread_mutex_lock(&lock);  // Lock critical section

        // Remove item from the buffer
        item = buffer[items - 1];
        items--;
        printf("Consumer consumed: %d\n", item);

        pthread_mutex_unlock(&lock);  // Unlock critical section
        sem_post(&empty);  // Signal that buffer has space

        sleep(1);  // Simulate consumption time
    }
}

int main() {
    pthread_t prod_thread, cons_thread;

    // Initialize semaphores and mutex
    sem_init(&empty, 0, SIZE);  // Buffer starts as empty
    sem_init(&full, 0, 0);  // No items initially
    pthread_mutex_init(&lock, NULL);

    // Create producer and consumer threads
    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    // Join threads (they run infinitely in this example)
    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);


    return 0;
}
