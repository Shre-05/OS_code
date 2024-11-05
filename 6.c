#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

int readers = 0;  // Number of active readers
sem_t resource;  // Semaphore for resource access control
pthread_mutex_t reader_lock;  // Mutex to protect readers count

// Reader function
void* reader(void* arg) {
    while (1) {
        pthread_mutex_lock(&reader_lock);  // Lock to update readers count

        readers++;
        if (readers == 1) {
            sem_wait(&resource);  // First reader locks the resource
        }

        pthread_mutex_unlock(&reader_lock);  // Unlock readers count

        // Critical section (reading)
        printf("Reader %ld is reading\n", (long)arg);
        sleep(1);  // Simulate reading time

        pthread_mutex_lock(&reader_lock);  // Lock to update readers count

        readers--;
        if (readers == 0) {
            sem_post(&resource);  // Last reader unlocks the resource
        }

        pthread_mutex_unlock(&reader_lock);  // Unlock readers count

        sleep(1);  // Simulate time between reads
    }
}

// Writer function
void* writer(void* arg) {
    while (1) {
        sem_wait(&resource);  // Wait for resource to be free

        // Critical section (writing)
        printf("Writer %ld is writing\n", (long)arg);
        sleep(1);  // Simulate writing time

        sem_post(&resource);  // Release the resource

        sleep(1);  // Simulate time between writes
    }
}

int main() {
    pthread_t reader_threads[3], writer_threads[2];

    // Initialize semaphore and mutex
    sem_init(&resource, 0, 1);  // Only one writer or multiple readers at a time
    pthread_mutex_init(&reader_lock, NULL);

    // Create reader threads
    for (long i = 0; i < 3; i++) {
        pthread_create(&reader_threads[i], NULL, reader, (void*)i);
    }

    // Create writer threads
    for (long i = 0; i < 2; i++) {
        pthread_create(&writer_threads[i], NULL, writer, (void*)i);
    }

    // Join threads (they run infinitely in this example)
    for (int i = 0; i < 3; i++) {
        pthread_join(reader_threads[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(writer_threads[i], NULL);
    }

    return 0;
}
