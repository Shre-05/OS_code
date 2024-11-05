Server.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of the shared memory segment

int main() {
    // Generate a unique key
    key_t key = ftok("shmfile", 65);
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }
    
    // Create a shared memory segment
    int shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }
    
    // Attach the shared memory segment
    char *message = (char*) shmat(shmid, NULL, 0);
    if (message == (char*) -1) {
        perror("shmat failed");
        return 1;
    }

    // Write a message to the shared memory
    strcpy(message, "Hello from Server!");

    // Detach the shared memory segment
    shmdt(message);

    return 0;
}


Reciever.c

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define SHM_SIZE 1024  // Size of the shared memory segment

int main() {
    // Generate the same unique key
    key_t key = ftok("shmfile", 65);
    if (key == -1) {
        perror("ftok failed");
        return 1;
    }
    
    // Access the shared memory segment
    int shmid = shmget(key, SHM_SIZE, 0666);
    if (shmid == -1) {
        perror("shmget failed");
        return 1;
    }
    
    // Attach the shared memory segment
    char *message = (char*) shmat(shmid, NULL, 0);
    if (message == (char*) -1) {
        perror("shmat failed");
        return 1;
    }

    // Read and print the message
    printf("Message: %s\n", message);

    // Detach the shared memory segment
    shmdt(message);

    // Optional: Remove the shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl failed");
    }

    return 0;
}
