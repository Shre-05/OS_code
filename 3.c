
Parent -
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
void bubbleSort(int arr[], int n) 
{
    int i, j, temp;
    for (i = 0; i < n-1; i++) 
    {
        for (j = 0; j < n-i-1; j++) 
        {
            if (arr[j] > arr[j+1]) 
            {
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}
int main() 
{
    int n, i;
    printf("Enter the number of integers to be sorted: ");
    scanf("%d", &n);
    int arr[n];

    printf("Enter the integers to be sorted: ");
    for (i = 0; i < n; i++) 
    {
        scanf("%d", &arr[i]);
    }
    pid_t pid = fork();

    if (pid < 0) 
    {
        printf("Fork failed!\n");
        return 1;
    } 
    else if (pid == 0) 
    {
        char *args[n+2];
        args[0] = "./child";
        for (i = 0; i < n; i++) 
        {
            char *arg = (char *)malloc(20);
            sprintf(arg, "%d", arr[i]);
            args[i+1] = arg;
        }
        args[n+1] = NULL;
        execve(args[0], args, NULL);
        perror("execve failed");
        return 1;
    } 
    else 
    {
        printf("Parent process (PID: %d) sorting the integers...\n", getpid());
        bubbleSort(arr, n);
        printf("Parent process (PID: %d) sorted integers: ", getpid());
        for (i = 0; i < n; i++) 
        {
        printf("%d ", arr[i]);
        }
    printf("\n");
    wait(NULL);
    }
    return 0;
}

Child -
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[]) 
{
    int n = argc - 1;
    int arr[n];
    for (int i = 0; i < n; i++) 
    {
       arr[i] = atoi(argv[i+1]);
    }
    printf("Child process (PID: %d) displaying integers in reverse order: ", getpid());
    for (int i = n-1; i >= 0; i--) 
    {
      printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}