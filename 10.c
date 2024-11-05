//parent.c

// parent.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

int main() {
    int pipe1[2], pipe2[2];
    char input[BUFFER_SIZE];
    char response[BUFFER_SIZE];
    pid_t pid;

    // Create two pipes for communication
    if (pipe(pipe1) == -1 || pipe(pipe2) == -1) {
        perror("Pipe creation failed");
        return 1;
    }

    pid = fork();  // Create a child process
    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid == 0) {  // Child Process
        // Redirect pipes for stdin and stdout
        dup2(pipe1[0], STDIN_FILENO);  // Child reads from pipe1
        dup2(pipe2[1], STDOUT_FILENO); // Child writes to pipe2

        // Close unused pipe ends
        close(pipe1[1]);
        close(pipe2[0]);

        // Execute child program
        execlp("./child", "./child", NULL);
        perror("Exec failed");
        exit(1);

    } else {  // Parent Process
        // Close unused pipe ends
        close(pipe1[0]);
        close(pipe2[1]);

        // Get input from the user
        printf("Enter a message: ");
        fgets(input, BUFFER_SIZE, stdin);

        // Send input to Child Process
        write(pipe1[1], input, strlen(input) + 1);
        close(pipe1[1]);  // Close write end of pipe1

        // Read the response from Child Process
        read(pipe2[0], response, BUFFER_SIZE);
        close(pipe2[0]);  // Close read end of pipe2

        // Display the response
        printf("Received from Child: %s\n", response);

        wait(NULL);  // Wait for child process to finish
    }

    return 0;
}


//child.c
// child.c
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 100

int main() {
    char message[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    // Read input from Parent Process through stdin (redirected from pipe1)
    read(STDIN_FILENO, message, BUFFER_SIZE);

    // Process the input (add a message to it)
    snprintf(response, sizeof(response), "Child received: %s", message);

    // Send the response back to Parent Process through stdout (redirected to pipe2)
    write(STDOUT_FILENO, response, strlen(response) + 1);

    return 0;
}
