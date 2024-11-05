#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void selectionSort(int arr[], int n)
{
    for (int i = 0; i < n - 1; i++) 
    {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) 
        {
            if (arr[j] < arr[min_idx]) 
            {
                min_idx = j;
            }
        }
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;
    }
}

int main() {
    int n, i;

    // Accept integers from the user
    printf("Enter number of integers: ");
    scanf("%d", &n);
    int *arr = (int *)malloc(n * sizeof(int));
    int *childArr = (int *)malloc(n * sizeof(int));

    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
        childArr[i] = arr[i]; // Copy to child array
    }

    pid_t pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("Fork failed");
        free(arr);
        free(childArr);
        return 1;
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) sorting using selection sort...\n", getpid());
        selectionSort(childArr, n);
        printf("Child sorted array: ");
        for (i = 0; i < n; i++) {
            printf("%d ", childArr[i]);
        }
        printf("\n");

        // Exit child process
        exit(0);
    } 
    else 
    {
        // Parent process
        printf("Parent process (PID: %d) sorting using bubble sort...\n", getpid());
        bubbleSort(arr, n);
        printf("Parent sorted array: ");
        for (i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");

        // Here, we intentionally do not call wait to create a zombie state
        // Uncomment the line below to avoid creating a zombie state
        // wait(NULL);

        // Simulating orphan state by exiting the parent process before the child
        printf("Parent process exiting, child may become orphan...\n");
        free(arr);
        free(childArr);
        exit(0);
    }

    // Clean up (not reached because of exit)
    free(arr);
    free(childArr);
    return 0;
}

